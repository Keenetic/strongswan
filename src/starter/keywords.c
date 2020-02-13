/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: /usr/bin/gperf -m 10 -C -G -D -t  */
/* Computed positions: -k'2-3,6,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif


/*
 * Copyright (C) 2005 Andreas Steffen
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

#include <string.h>

#define IN_GPERF_GENERATED_FILE
#include "keywords.h"

struct kw_entry {
    char *name;
    kw_token_t token;
};

#define TOTAL_KEYWORDS 143
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 17
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 267
/* maximum key range = 259, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register size_t len)
{
  static const unsigned short asso_values[] =
    {
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268,  43,
      129, 268, 268, 268,   5, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268,  82, 268,  31,   3,  83,
       50,   5,   4,   1,  79,   1, 268, 121,  62,  61,
       33,  51,  41,   2,  22,   1,  25, 103,   7,   1,
      268,   8,   2, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268, 268, 268, 268, 268,
      268, 268, 268, 268, 268, 268
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

static const struct kw_entry wordlist[] =
  {
    {"pfs",               KW_PFS_DEPRECATED},
    {"rightgroups",       KW_RIGHTGROUPS},
    {"aggressive",        KW_AGGRESSIVE},
    {"lifetime",          KW_KEYLIFE},
    {"rightsigkey",       KW_RIGHTSIGKEY},
    {"lifebytes",         KW_LIFEBYTES},
    {"keyingtries",       KW_KEYINGTRIES},
    {"leftsigkey",        KW_LEFTSIGKEY},
    {"keylife",           KW_KEYLIFE},
    {"leftrsasigkey",     KW_LEFTSIGKEY},
    {"right",             KW_RIGHT},
    {"leftcertpolicy",    KW_LEFTCERTPOLICY},
    {"left",              KW_LEFT},
    {"rightsubnet",       KW_RIGHTSUBNET},
    {"rightikeport",      KW_RIGHTIKEPORT},
    {"rightsendcert",     KW_RIGHTSENDCERT},
    {"leftgroups",        KW_LEFTGROUPS},
    {"rightrsasigkey",    KW_RIGHTSIGKEY},
    {"leftcert",          KW_LEFTCERT},
    {"lifepackets",       KW_LIFEPACKETS},
    {"uniqueids",         KW_UNIQUEIDS},
    {"leftdns",           KW_LEFTDNS},
    {"leftsendcert",      KW_LEFTSENDCERT},
    {"rightsubnetwithin", KW_RIGHTSUBNET},
    {"rightallowany",     KW_RIGHTALLOWANY},
    {"keep_alive",        KW_SETUP_DEPRECATED},
    {"rightsourceip",     KW_RIGHTSOURCEIP},
    {"type",              KW_TYPE},
    {"rightid",           KW_RIGHTID},
    {"rightdns",          KW_RIGHTDNS},
    {"reqid",             KW_REQID},
    {"certuribase",       KW_CERTURIBASE},
    {"leftnexthop",       KW_LEFT_DEPRECATED},
    {"replay_window",     KW_REPLAY_WINDOW},
    {"leftprotoport",     KW_LEFTPROTOPORT},
    {"mobike",	           KW_MOBIKE},
    {"interfaces",        KW_SETUP_DEPRECATED},
    {"virtual_private",   KW_SETUP_DEPRECATED},
    {"lefthostaccess",    KW_LEFTHOSTACCESS},
    {"leftca",            KW_LEFTCA},
    {"rightfirewall",     KW_RIGHTFIREWALL},
    {"rightprotoport",    KW_RIGHTPROTOPORT},
    {"inactivity",        KW_INACTIVITY},
    {"leftfirewall",      KW_LEFTFIREWALL},
    {"esp",               KW_ESP},
    {"rightnexthop",      KW_RIGHT_DEPRECATED},
    {"forceencaps",       KW_FORCEENCAPS},
    {"leftallowany",      KW_LEFTALLOWANY},
    {"crluri",            KW_CRLURI},
    {"leftupdown",        KW_LEFTUPDOWN},
    {"mark_in",           KW_MARK_IN},
    {"strictcrlpolicy",   KW_STRICTCRLPOLICY},
    {"righthostaccess",   KW_RIGHTHOSTACCESS},
    {"marginbytes",       KW_MARGINBYTES},
    {"mediated_by",       KW_MEDIATED_BY},
    {"marginpackets",     KW_MARGINPACKETS},
    {"margintime",        KW_REKEYMARGIN},
    {"fragmentation",     KW_FRAGMENTATION},
    {"pfsgroup",          KW_PFS_DEPRECATED},
    {"rightcertpolicy",   KW_RIGHTCERTPOLICY},
    {"hidetos",           KW_SETUP_DEPRECATED},
    {"keyexchange",       KW_KEYEXCHANGE},
    {"leftsourceip",      KW_LEFTSOURCEIP},
    {"ocspuri",           KW_OCSPURI},
    {"leftid",            KW_LEFTID},
    {"eap",               KW_CONN_DEPRECATED},
    {"installpolicy",     KW_INSTALLPOLICY},
    {"also",              KW_ALSO},
    {"rightcert",         KW_RIGHTCERT},
    {"rightauth",         KW_RIGHTAUTH},
    {"mediation",         KW_MEDIATION},
    {"rightca",           KW_RIGHTCA},
    {"klipsdebug",        KW_SETUP_DEPRECATED},
    {"ldapbase",          KW_CA_DEPRECATED},
    {"compress",          KW_COMPRESS},
    {"overridemtu",       KW_SETUP_DEPRECATED},
    {"sha256_96",         KW_SHA256_96},
    {"aaa_identity",      KW_AAA_IDENTITY},
    {"ike",               KW_IKE},
    {"crluri1",           KW_CRLURI},
    {"mark_out",          KW_MARK_OUT},
    {"rekey",             KW_REKEY},
    {"rightid2",          KW_RIGHTID2},
    {"rekeyfuzz",         KW_REKEYFUZZ},
    {"eap_identity",      KW_EAP_IDENTITY},
    {"rightgroups2",      KW_RIGHTGROUPS2},
    {"ikelifetime",       KW_IKELIFETIME},
    {"leftsubnet",        KW_LEFTSUBNET},
    {"rightupdown",       KW_RIGHTUPDOWN},
    {"authby",            KW_AUTHBY},
    {"me_peerid",         KW_ME_PEERID},
    {"leftcert2",         KW_LEFTCERT2},
    {"nat_traversal",     KW_SETUP_DEPRECATED},
    {"charondebug",       KW_CHARONDEBUG},
    {"ocspuri1",          KW_OCSPURI},
    {"dpdaction",         KW_DPDACTION},
    {"ah",                KW_AH},
    {"leftsubnetwithin",  KW_LEFTSUBNET},
    {"modeconfig",        KW_MODECONFIG},
    {"ldaphost",          KW_CA_DEPRECATED},
    {"leftikeport",       KW_LEFTIKEPORT},
    {"crlcheckinterval",  KW_SETUP_DEPRECATED},
    {"dpddelay",          KW_DPDDELAY},
    {"cacert",            KW_CACERT},
    {"leftgroups2",       KW_LEFTGROUPS2},
    {"rightauth2",        KW_RIGHTAUTH2},
    {"tfc",               KW_TFC},
    {"postpluto",         KW_SETUP_DEPRECATED},
    {"force_keepalive",   KW_SETUP_DEPRECATED},
    {"leftca2",           KW_LEFTCA2},
    {"packetdefault",     KW_SETUP_DEPRECATED},
    {"mark",              KW_MARK},
    {"charonstart",       KW_SETUP_DEPRECATED},
    {"plutostderrlog",    KW_SETUP_DEPRECATED},
    {"auto",              KW_AUTO},
    {"fragicmp",          KW_SETUP_DEPRECATED},
    {"no_reauth_passive", KW_NO_REAUTH_PASSIVE},
    {"dpdtimeout",        KW_DPDTIMEOUT},
    {"closeaction",       KW_CLOSEACTION},
    {"prepluto",          KW_SETUP_DEPRECATED},
    {"dumpdir",           KW_SETUP_DEPRECATED},
    {"leftid2",           KW_LEFTID2},
    {"nocrsend",          KW_SETUP_DEPRECATED},
    {"leftauth",          KW_LEFTAUTH},
    {"reauth",            KW_REAUTH},
    {"plutostart",        KW_SETUP_DEPRECATED},
    {"if_id_out",         KW_IF_ID_OUT},
    {"cachecrls",         KW_CACHECRLS},
    {"if_id_in",          KW_IF_ID_IN},
    {"xauth",             KW_XAUTH},
    {"crluri2",           KW_CRLURI2},
    {"rightca2",          KW_RIGHTCA2},
    {"rightcert2",        KW_RIGHTCERT2},
    {"plutodebug",        KW_SETUP_DEPRECATED},
    {"rekeymargin",       KW_REKEYMARGIN},
    {"xauth_identity",    KW_XAUTH_IDENTITY},
    {"ocspuri2",          KW_OCSPURI2},
    {"leftauth2",         KW_LEFTAUTH2},
    {"ikedscp",           KW_IKEDSCP,},
    {"pkcs11initargs",    KW_PKCS11_DEPRECATED},
    {"pkcs11module",      KW_PKCS11_DEPRECATED},
    {"pkcs11proxy",       KW_PKCS11_DEPRECATED},
    {"pkcs11keepstate",   KW_PKCS11_DEPRECATED}
  };

static const short lookup[] =
  {
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,
     -1,  -1,  -1,  -1,  -1,   1,  -1,  -1,   2,   3,
     -1,  -1,   4,   5,  -1,  -1,   6,  -1,   7,   8,
     -1,   9,  10,  -1,  -1,  -1,  11,  -1,  12,  13,
     14,  15,  16,  -1,  -1,  -1,  17,  18,  19,  20,
     21,  22,  -1,  23,  24,  -1,  25,  26,  27,  -1,
     28,  29,  30,  -1,  -1,  31,  32,  -1,  33,  34,
     35,  -1,  -1,  36,  37,  38,  -1,  39,  -1,  -1,
     -1,  40,  41,  42,  43,  -1,  44,  -1,  45,  -1,
     46,  47,  48,  49,  50,  51,  -1,  52,  53,  54,
     55,  56,  -1,  -1,  57,  58,  -1,  -1,  59,  -1,
     60,  -1,  61,  62,  63,  64,  65,  66,  67,  68,
     -1,  69,  70,  71,  72,  73,  74,  75,  -1,  76,
     -1,  -1,  77,  -1,  78,  79,  -1,  80,  -1,  81,
     82,  83,  84,  -1,  85,  -1,  86,  87,  -1,  88,
     89,  90,  91,  92,  -1,  93,  -1,  94,  95,  -1,
     96,  97,  -1,  98,  -1,  99, 100, 101,  -1, 102,
    103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
     -1, 113,  -1, 114,  -1, 115, 116, 117, 118, 119,
     -1,  -1,  -1,  -1, 120, 121,  -1, 122,  -1, 123,
    124, 125, 126,  -1,  -1,  -1,  -1, 127,  -1, 128,
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 129,  -1,
     -1, 130, 131,  -1, 132,  -1, 133,  -1,  -1,  -1,
     -1, 134,  -1,  -1,  -1,  -1,  -1,  -1, 135,  -1,
     -1,  -1,  -1, 136,  -1,  -1,  -1,  -1,  -1,  -1,
    137,  -1,  -1,  -1,  -1,  -1,  -1, 138,  -1,  -1,
     -1,  -1, 139,  -1, 140,  -1, 141, 142
  };

const struct kw_entry *
in_word_set (register const char *str, register size_t len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
