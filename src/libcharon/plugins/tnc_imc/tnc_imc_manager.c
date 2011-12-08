/*
 * Copyright (C) 2006 Mike McCauley
 * Copyright (C) 2010-2011 Andreas Steffen
 * HSR Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "tnc_imc_manager.h"
#include "tnc_imc.h"

#include <tncifimc.h>

#include <utils/linked_list.h>
#include <debug.h>

typedef struct private_tnc_imc_manager_t private_tnc_imc_manager_t;

/**
 * Private data of an imc_manager_t object.
 */
struct private_tnc_imc_manager_t {

	/**
	 * Public members of imc_manager_t.
	 */
	imc_manager_t public;

	/**
	 * Linked list of IMCs
	 */
	linked_list_t *imcs;

	/**
	 * Next IMC ID to be assigned
	 */
	TNC_IMCID next_imc_id;
};

METHOD(imc_manager_t, add, bool,
	private_tnc_imc_manager_t *this, imc_t *imc)
{
	TNC_Version version;

	/* Initialize the module */
	imc->set_id(imc, this->next_imc_id);
	if (imc->initialize(imc->get_id(imc), TNC_IFIMC_VERSION_1,
			TNC_IFIMC_VERSION_1, &version) != TNC_RESULT_SUCCESS)
	{
		DBG1(DBG_TNC, "IMC \"%s\" failed to initialize", imc->get_name(imc));
		return FALSE;
	}
	this->imcs->insert_last(this->imcs, imc);
	this->next_imc_id++;

	if (imc->provide_bind_function(imc->get_id(imc), TNC_TNCC_BindFunction)
			!= TNC_RESULT_SUCCESS)
	{
		DBG1(DBG_TNC, "IMC \"%s\" failed to obtain bind function",
					   imc->get_name(imc));
		this->imcs->remove_last(this->imcs, (void**)&imc);
		return FALSE;
	}

	return TRUE;
}

METHOD(imc_manager_t, remove_, imc_t*,
	private_tnc_imc_manager_t *this, TNC_IMCID id)
{
	enumerator_t *enumerator;
	imc_t *imc, *removed_imc = NULL;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (id == imc->get_id(imc))
		{
			this->imcs->remove_at(this->imcs, enumerator);
			removed_imc = imc;
			break;
		}
	}
	enumerator->destroy(enumerator);

	return removed_imc;
}

METHOD(imc_manager_t, load, bool,
	private_tnc_imc_manager_t *this, char *name, char *path)
{
	imc_t *imc;

	imc = tnc_imc_create(name, path);
	if (!imc)
	{
		free(name);
		free(path);
		return FALSE;
	}
	if (!add(this, imc))
	{
		if (imc->terminate &&
			imc->terminate(imc->get_id(imc)) != TNC_RESULT_SUCCESS)
		{
			DBG1(DBG_TNC, "IMC \"%s\" not terminated successfully",
						   imc->get_name(imc));
		}
		imc->destroy(imc);
		return FALSE;
	}
	DBG1(DBG_TNC, "IMC %u \"%s\" loaded from '%s'", imc->get_id(imc), name, path);
	return TRUE;
}

METHOD(imc_manager_t, is_registered, bool,
	private_tnc_imc_manager_t *this, TNC_IMCID id)
{
	enumerator_t *enumerator;
	imc_t *imc;
	bool found = FALSE;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (imc->has_id(imc, id))
		{
			found = TRUE;
			break;
		}
	}
	enumerator->destroy(enumerator);

	return found;
}

METHOD(imc_manager_t, reserve_id, bool,
	private_tnc_imc_manager_t *this, TNC_IMCID id, TNC_UInt32 *new_id)
{
	enumerator_t *enumerator;
	imc_t *imc;
	bool found = FALSE;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (imc->get_id(imc))
		{
			imc->add_id(imc, this->next_imc_id++);
			found = TRUE;
			break;
		}
	}
	enumerator->destroy(enumerator);

	return found;
}

METHOD(imc_manager_t, get_preferred_language, char*,
	private_tnc_imc_manager_t *this)
{
	return lib->settings->get_str(lib->settings,
					"charon.plugins.tnc-imc.preferred_language", "en");
}

METHOD(imc_manager_t, notify_connection_change, void,
	private_tnc_imc_manager_t *this, TNC_ConnectionID id,
									 TNC_ConnectionState state)
{
	enumerator_t *enumerator;
	imc_t *imc;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (imc->notify_connection_change)
		{
			imc->notify_connection_change(imc->get_id(imc), id, state);
		}
	}
	enumerator->destroy(enumerator);
}

METHOD(imc_manager_t, begin_handshake, void,
	private_tnc_imc_manager_t *this, TNC_ConnectionID id)
{
	enumerator_t *enumerator;
	imc_t *imc;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		imc->begin_handshake(imc->get_id(imc), id);
	}
	enumerator->destroy(enumerator);
}

METHOD(imc_manager_t, set_message_types, TNC_Result,
	private_tnc_imc_manager_t *this, TNC_IMCID id,
									 TNC_MessageTypeList supported_types,
									 TNC_UInt32 type_count)
{
	enumerator_t *enumerator;
	imc_t *imc;
	TNC_Result result = TNC_RESULT_FATAL;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (id == imc->get_id(imc))
		{
			imc->set_message_types(imc, supported_types, type_count);
			result = TNC_RESULT_SUCCESS;
			break;
		}
	}
	enumerator->destroy(enumerator);
	return result;
}

METHOD(imc_manager_t, set_message_types_long, TNC_Result,
	private_tnc_imc_manager_t *this, TNC_IMCID id,
									 TNC_VendorIDList supported_vids,
									 TNC_MessageSubtypeList supported_subtypes,
									 TNC_UInt32 type_count)
{
	enumerator_t *enumerator;
	imc_t *imc;
	TNC_Result result = TNC_RESULT_FATAL;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (id == imc->get_id(imc))
		{
			imc->set_message_types_long(imc, supported_vids, supported_subtypes,
										type_count);
			result = TNC_RESULT_SUCCESS;
			break;
		}
	}
	enumerator->destroy(enumerator);
	return result;
}

METHOD(imc_manager_t, receive_message, void,
	private_tnc_imc_manager_t *this, TNC_ConnectionID connection_id,
									 bool excl,
									 TNC_BufferReference msg,
									 TNC_UInt32 msg_len,
									 TNC_VendorID msg_vid,
									 TNC_MessageSubtype msg_subtype,
									 TNC_UInt32 src_imv_id,
									 TNC_UInt32 dst_imc_id)
{
	bool type_supported = FALSE;
	TNC_MessageType	msg_type;
	TNC_UInt32 msg_flags;
	enumerator_t *enumerator;
	imc_t *imc;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (imc->type_supported(imc, msg_vid, msg_subtype) &&
		   (!excl || (excl && imc->has_id(imc, dst_imc_id)) ))
		{
			if (imc->receive_message_long && src_imv_id)
			{
				type_supported = TRUE;
				msg_flags = excl ? TNC_MESSAGE_FLAGS_EXCLUSIVE : 0;
				imc->receive_message_long(imc->get_id(imc), connection_id,
								msg_flags, msg, msg_len, msg_vid, msg_subtype,
								src_imv_id, dst_imc_id);

			}
			else if (imc->receive_message && msg_vid <= TNC_VENDORID_ANY &&
					 msg_subtype <= TNC_SUBTYPE_ANY)
			{
				type_supported = TRUE;
				msg_type = (msg_vid << 8) | msg_subtype;
				imc->receive_message(imc->get_id(imc), connection_id,
									 msg, msg_len, msg_type);
			}
		}
	}
	enumerator->destroy(enumerator);
	if (!type_supported)
	{
		DBG2(DBG_TNC, "message type 0x%06x/0x%08x not supported by any IMC",
			 msg_vid, msg_subtype);
	}
}

METHOD(imc_manager_t, batch_ending, void,
	private_tnc_imc_manager_t *this, TNC_ConnectionID id)
{
	enumerator_t *enumerator;
	imc_t *imc;

	enumerator = this->imcs->create_enumerator(this->imcs);
	while (enumerator->enumerate(enumerator, &imc))
	{
		if (imc->batch_ending)
		{
			imc->batch_ending(imc->get_id(imc), id);
		}
	}
	enumerator->destroy(enumerator);
}

METHOD(imc_manager_t, destroy, void,
	private_tnc_imc_manager_t *this)
{
	imc_t *imc;

	while (this->imcs->remove_last(this->imcs, (void**)&imc) == SUCCESS)
	{
		if (imc->terminate &&
			imc->terminate(imc->get_id(imc)) != TNC_RESULT_SUCCESS)
		{
			DBG1(DBG_TNC, "IMC \"%s\" not terminated successfully",
						   imc->get_name(imc));
		}
		imc->destroy(imc);
	}
	this->imcs->destroy(this->imcs);
	free(this);
}

/**
 * Described in header.
 */
imc_manager_t* tnc_imc_manager_create(void)
{
	private_tnc_imc_manager_t *this;

	INIT(this,
		.public = {
			.add = _add,
			.remove = _remove_, /* avoid name conflict with stdio.h */
			.load = _load,
			.is_registered = _is_registered,
			.reserve_id = _reserve_id,
			.get_preferred_language = _get_preferred_language,
			.notify_connection_change = _notify_connection_change,
			.begin_handshake = _begin_handshake,
			.set_message_types = _set_message_types,
			.set_message_types_long = _set_message_types_long,
			.receive_message = _receive_message,
			.batch_ending = _batch_ending,
			.destroy = _destroy,
		},
		.imcs = linked_list_create(),
		.next_imc_id = 1,
	);

	return &this->public;
}
