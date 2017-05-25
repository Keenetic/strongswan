/*
 * Copyright (C) 2005 Andreas Steffen
 * Hochschule fuer Technik Rapperswil, Switzerland
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

#ifndef _KEYWORDS_H_
#define _KEYWORDS_H_

typedef enum kw_token_t kw_token_t;
typedef struct kw_entry_t kw_entry_t;

enum kw_token_t {
	/* config setup keywords */
	KW_CHARONDEBUG,
	KW_UNIQUEIDS,
	KW_CACHECRLS,
	KW_STRICTCRLPOLICY,
	KW_PKCS11_DEPRECATED,
	KW_SETUP_DEPRECATED,

#define KW_SETUP_FIRST  KW_CHARONDEBUG
#define KW_SETUP_LAST   KW_SETUP_DEPRECATED

	/* conn section keywords */
	KW_CONN_NAME,
	KW_CONN_SETUP,
	KW_KEYEXCHANGE,
	KW_TYPE,
	KW_COMPRESS,
	KW_INSTALLPOLICY,
	KW_AGGRESSIVE,
	KW_AUTHBY,
	KW_EAP_IDENTITY,
	KW_AAA_IDENTITY,
	KW_MOBIKE,
	KW_FORCEENCAPS,
	KW_FRAGMENTATION,
	KW_IKEDSCP,
	KW_IKELIFETIME,
	KW_KEYLIFE,
	KW_REKEYMARGIN,
	KW_LIFEBYTES,
	KW_MARGINBYTES,
	KW_LIFEPACKETS,
	KW_MARGINPACKETS,
	KW_KEYINGTRIES,
	KW_REKEYFUZZ,
	KW_REKEY,
	KW_REAUTH,
	KW_IKE,
	KW_ESP,
	KW_AH,
	KW_DPDDELAY,
	KW_DPDTIMEOUT,
	KW_DPDACTION,
	KW_CLOSEACTION,
	KW_SHA256_96,
	KW_NO_REAUTH_PASSIVE,
	KW_INACTIVITY,
	KW_MODECONFIG,
	KW_XAUTH,
	KW_XAUTH_IDENTITY,
	KW_MEDIATION,
	KW_MEDIATED_BY,
	KW_ME_PEERID,
	KW_REQID,
	KW_REPLAY_WINDOW,
	KW_MARK,
	KW_MARK_IN,
	KW_MARK_OUT,
	KW_TFC,
	KW_PFS_DEPRECATED,
	KW_CONN_DEPRECATED,

#define KW_CONN_FIRST   KW_CONN_SETUP
#define KW_CONN_LAST    KW_CONN_DEPRECATED

	/* ca section keywords */
	KW_CA_NAME,
	KW_CA_SETUP,
	KW_CACERT,
	KW_CRLURI,
	KW_CRLURI2,
	KW_OCSPURI,
	KW_OCSPURI2,
	KW_CERTURIBASE,
	KW_CA_DEPRECATED,

#define KW_CA_FIRST     KW_CA_SETUP
#define KW_CA_LAST      KW_CA_DEPRECATED

	/* end keywords */
	KW_HOST,
	KW_IKEPORT,
	KW_SUBNET,
	KW_PROTOPORT,
	KW_SOURCEIP,
	KW_DNS,
	KW_FIREWALL,
	KW_HOSTACCESS,
	KW_ALLOWANY,
	KW_UPDOWN,
	KW_AUTH1,
	KW_AUTH2,
	KW_ID,
	KW_ID2,
	KW_SIGKEY,
	KW_CERT,
	KW_CERT2,
	KW_CERTPOLICY,
	KW_SENDCERT,
	KW_CA,
	KW_CA2,
	KW_GROUPS,
	KW_GROUPS2,
	KW_END_DEPRECATED,

#define KW_END_FIRST    KW_HOST
#define KW_END_LAST     KW_END_DEPRECATED

	/* left end keywords */
	KW_LEFT,
	KW_LEFTIKEPORT,
	KW_LEFTSUBNET,
	KW_LEFTPROTOPORT,
	KW_LEFTSOURCEIP,
	KW_LEFTDNS,
	KW_LEFTFIREWALL,
	KW_LEFTHOSTACCESS,
	KW_LEFTALLOWANY,
	KW_LEFTUPDOWN,
	KW_LEFTAUTH,
	KW_LEFTAUTH2,
	KW_LEFTID,
	KW_LEFTID2,
	KW_LEFTSIGKEY,
	KW_LEFTCERT,
	KW_LEFTCERT2,
	KW_LEFTCERTPOLICY,
	KW_LEFTSENDCERT,
	KW_LEFTCA,
	KW_LEFTCA2,
	KW_LEFTGROUPS,
	KW_LEFTGROUPS2,
	KW_LEFT_DEPRECATED,

#define KW_LEFT_FIRST   KW_LEFT
#define KW_LEFT_LAST    KW_LEFT_DEPRECATED

	/* right end keywords */
	KW_RIGHT,
	KW_RIGHTIKEPORT,
	KW_RIGHTSUBNET,
	KW_RIGHTPROTOPORT,
	KW_RIGHTSOURCEIP,
	KW_RIGHTDNS,
	KW_RIGHTFIREWALL,
	KW_RIGHTHOSTACCESS,
	KW_RIGHTALLOWANY,
	KW_RIGHTUPDOWN,
	KW_RIGHTAUTH,
	KW_RIGHTAUTH2,
	KW_RIGHTID,
	KW_RIGHTID2,
	KW_RIGHTSIGKEY,
	KW_RIGHTCERT,
	KW_RIGHTCERT2,
	KW_RIGHTCERTPOLICY,
	KW_RIGHTSENDCERT,
	KW_RIGHTCA,
	KW_RIGHTCA2,
	KW_RIGHTGROUPS,
	KW_RIGHTGROUPS2,
	KW_RIGHT_DEPRECATED,

#define KW_RIGHT_FIRST  KW_RIGHT
#define KW_RIGHT_LAST   KW_RIGHT_DEPRECATED

	/* general section keywords */
	KW_ALSO,
	KW_AUTO,

};

struct kw_entry_t {
	char *name;
	kw_token_t token;
};

#ifndef IN_GPERF_GENERATED_FILE
const kw_entry_t *in_word_set(register const char*, register unsigned);
#endif

#endif /* _KEYWORDS_H_ */
