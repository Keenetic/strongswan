DROP TABLE IF EXISTS identities;
CREATE TABLE identities (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL,
  data BLOB NOT NULL,
  UNIQUE (type, data)
);

DROP TABLE IF EXISTS child_configs;
CREATE TABLE child_configs (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  lifetime INTEGER NOT NULL DEFAULT '1200',
  rekeytime INTEGER NOT NULL DEFAULT '1020',
  jitter INTEGER NOT NULL DEFAULT '180',
  updown TEXT DEFAULT NULL,
  hostaccess INTEGER NOT NULL DEFAULT '0',
  mode INTEGER NOT NULL DEFAULT '1',
  dpd_action INTEGER NOT NULL DEFAULT '0',
  close_action INTEGER NOT NULL DEFAULT '0',
  ipcomp INTEGER NOT NULL DEFAULT '0'
);
DROP INDEX IF EXISTS child_configs_name;
CREATE INDEX child_configs_name ON child_configs (
  name
);

DROP TABLE IF EXISTS child_config_traffic_selector;
CREATE TABLE child_config_traffic_selector (
  child_cfg INTEGER NOT NULL,
  traffic_selector INTEGER NOT NULL,
  kind INTEGER NOT NULL
);
DROP INDEX IF EXISTS child_config_traffic_selector;
CREATE INDEX child_config_traffic_selector_all ON child_config_traffic_selector (
  child_cfg, traffic_selector
);

DROP TABLE IF EXISTS ike_configs;
CREATE TABLE ike_configs (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  certreq INTEGER NOT NULL DEFAULT '1',
  force_encap INTEGER NOT NULL DEFAULT '0',
  local TEXT NOT NULL,
  remote TEXT NOT NULL
);

DROP TABLE IF EXISTS peer_configs;
CREATE TABLE peer_configs (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  ike_version INTEGER NOT NULL DEFAULT '2',
  ike_cfg INTEGER NOT NULL,
  local_id TEXT NOT NULL,
  remote_id TEXT NOT NULL,
  cert_policy INTEGER NOT NULL DEFAULT '1',
  uniqueid INTEGER NOT NULL DEFAULT '0',
  auth_method INTEGER NOT NULL DEFAULT '1',
  eap_type INTEGER NOT NULL DEFAULT '0',
  eap_vendor INTEGER NOT NULL DEFAULT '0',
  keyingtries INTEGER NOT NULL DEFAULT '1',
  rekeytime INTEGER NOT NULL DEFAULT '0',
  reauthtime INTEGER NOT NULL DEFAULT '3600',
  jitter INTEGER NOT NULL DEFAULT '180',
  overtime INTEGER NOT NULL DEFAULT '300',
  mobike INTEGER NOT NULL DEFAULT '1',
  dpd_delay INTEGER NOT NULL DEFAULT '120',
  virtual TEXT DEFAULT NULL,
  pool TEXT DEFAULT NULL,
  mediation INTEGER NOT NULL DEFAULT '0',
  mediated_by INTEGER NOT NULL DEFAULT '0',
  peer_id INTEGER NOT NULL DEFAULT '0'
);
DROP INDEX IF EXISTS peer_configs_name;
CREATE INDEX peer_configs_name ON peer_configs (
  name
);

DROP TABLE IF EXISTS peer_config_child_config;
CREATE TABLE peer_config_child_config (
  peer_cfg INTEGER NOT NULL,
  child_cfg INTEGER NOT NULL,
  PRIMARY KEY (peer_cfg, child_cfg)
);

DROP TABLE IF EXISTS traffic_selectors;
CREATE TABLE traffic_selectors (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL DEFAULT '7',
  protocol INTEGER NOT NULL DEFAULT '0',
  start_addr BLOB DEFAULT NULL,
  end_addr BLOB DEFAULT NULL,
  start_port INTEGER NOT NULL DEFAULT '0',
  end_port INTEGER NOT NULL DEFAULT '65535'
);

DROP TABLE IF EXISTS certificates;
CREATE TABLE certificates (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL,
  keytype INTEGER NOT NULL,
  data BLOB NOT NULL
);

DROP TABLE IF EXISTS certificate_identity;
CREATE TABLE certificate_identity (
  certificate INTEGER NOT NULL,
  identity INTEGER NOT NULL,
  PRIMARY KEY (certificate, identity)
);

DROP TABLE IF EXISTS private_keys;
CREATE TABLE private_keys (
  id INTEGER NOT NULL  PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL,
  data BLOB NOT NULL
);

DROP TABLE IF EXISTS private_key_identity;
CREATE TABLE private_key_identity (
  private_key INTEGER NOT NULL,
  identity INTEGER NOT NULL,
  PRIMARY KEY (private_key, identity)
);

DROP TABLE IF EXISTS shared_secrets;
CREATE TABLE shared_secrets (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  type INTEGER NOT NULL,
  data BLOB NOT NULL
);

DROP TABLE IF EXISTS shared_secret_identity;
CREATE TABLE shared_secret_identity (
  shared_secret INTEGER NOT NULL,
  identity INTEGER NOT NULL,
  PRIMARY KEY (shared_secret, identity)
);

DROP TABLE IF EXISTS pools;
CREATE TABLE pools (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  start BLOB NOT NULL,
  end BLOB NOT NULL,
  next BLOB NOT NULL,
  timeout INTEGER DEFAULT NULL,
  UNIQUE (name)
);
DROP INDEX IF EXISTS pools_name;
CREATE INDEX pools_name ON pools (
  name
);

DROP TABLE IF EXISTS leases;
CREATE TABLE leases (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  pool INTEGER NOT NULL,
  address BLOB NOT NULL,
  identity INTEGER NOT NULL,
  acquired INTEGER NOT NULL,
  released INTEGER DEFAULT NULL
);
DROP INDEX IF EXISTS leases_pool;
CREATE INDEX leases_pool ON leases (
  pool
);
DROP INDEX IF EXISTS leases_identity;
CREATE INDEX leases_identity ON leases (
  identity
);
DROP INDEX IF EXISTS leases_released;
CREATE INDEX leases_released ON leases (
  released
);

DROP TABLE IF EXISTS ike_sas;
CREATE TABLE ike_sas (
  local_spi BLOB NOT NULL PRIMARY KEY,
  remote_spi BLOB NOT NULL,
  id INTEGER NOT NULL,
  initiator INTEGER NOT NULL,
  local_id_type INTEGER NOT NULL,
  local_id_data BLOB NOT NULL,
  remote_id_type INTEGER NOT NULL,
  remote_id_data BLOB NOT NULL,
  host_family INTEGER NOT NULL,
  local_host_data BLOB NOT NULL,
  remote_host_data BLOB NOT NULL,
  created INTEGER NOT NULL DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS logs;
CREATE TABLE logs (
  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  local_spi BLOB NOT NULL,
  signal INTEGER NOT NULL,
  level INTEGER NOT NULL,
  msg TEXT NOT NULL,
  time INTEGER NOT NULL DEFAULT CURRENT_TIMESTAMP
);

/* Identities */

INSERT INTO identities (
  type, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=strongSwan Root CA */
  9, X'3045310B300906035504061302434831193017060355040A13104C696E7578207374726F6E675377616E311B3019060355040313127374726F6E675377616E20526F6F74204341'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* keyid of 'C=CH, O=Linux strongSwan, CN=strongSwan Root CA' */
  202, X'ae096b87b44886d3b820978623dabd0eae22ebbc'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* dave@strongswan.org */
  3, X'64617665407374726f6e677377616e2e6f7267'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* keyid of 'C=CH, O=Linux strongSwan, CN=dave@strongswan.org' */
  202, X'f651b7ea33148cc5a76a622f1c1eb16c6bbdea25'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* moon.strongswan.org */
  2, X'6d6f6f6e2e7374726f6e677377616e2e6f7267'
 );

/* Certificates */

INSERT INTO certificates (
   type, keytype, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=strongSwan Root CA */
  1, 1, X'308203b53082029da003020102020100300d06092a864886f70d01010405003045310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e311b3019060355040313127374726f6e675377616e20526f6f74204341301e170d3034303931303131303134355a170d3134303930383131303134355a3045310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e311b3019060355040313127374726f6e675377616e20526f6f7420434130820122300d06092a864886f70d01010105000382010f003082010a0282010100bff25f62ea3d566e58b3c87a49caf3ac61cfa96377734d842db3f8fd6ea023f7b0132e66265012317386729c6d7c427a8d9f167be138e8ebae2b12b95933baef36a315c3ddf224cee4bb9bd578135d0467382629621ff96b8d45f6e002e5083662dce181805c140b3f2ce93f83aee3c861cff610a39f0189cb3a3c7cb9bf7e2a09544e2170efaa18fdd4ff20fa94be176d7fecff821f68d17152041d9b46f0cfcfc1e4cf43de5d3f3a587763afe9267f53b11699b3264fc55c5189f5682871166cb98307950569641fa30ffb50de134fed2f973cef1a392827862bc4ddaa97bbb01442e293c41070d07224d4be47ae2753eb2bed4bc1da91c68ec780c4620f0f0203010001a381af3081ac300f0603551d130101ff040530030101ff300b0603551d0f040403020106301d0603551d0e041604145da7dd700651327ee7b66db3b5e5e060ea2e4def306d0603551d230466306480145da7dd700651327ee7b66db3b5e5e060ea2e4defa149a4473045310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e311b3019060355040313127374726f6e675377616e20526f6f74204341820100300d06092a864886f70d010104050003820101009ad74e3e60592dfb9b21c78628bd76b63090c1720c74bf94753cad6fddadc9c776eb39d3bfaa52136bf528840078386308fcf79503bd3d1ad6c15ac38e10c846bff7888a03cfe7fa0e644b522b2af5aedf0bbc508dc48330a180757772771095059b2be148f58dc0c753b59e9d6bfb02e9b685a928a284531b187313fd2b835bc9ea27d0020739a8d485e88bdede9a45cde6d28ed553b0e8e92dabf877bed59abf9d151f15e4f2d00b5e6e49fcb665293d2296697926c2954dae367542ef6e98053e76d2728732f6ce69f284f0b856aa6c2823a9ee29b280a66f50828f9b5cf27f84feca3c31c24897db156c7a833768ab306f51286457a51f09dd53bbb4190f'
);

INSERT INTO certificates (
   type, keytype, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=dave@strongswan.org */
  1, 1, X'308204223082030aa003020102020108300d06092a864886f70d01010405003045310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e311b3019060355040313127374726f6e675377616e20526f6f74204341301e170d3034303931303131323635315a170d3039303930393131323635315a305b310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e31133011060355040b130a4163636f756e74696e67311c301a0603550403141364617665407374726f6e677377616e2e6f726730820122300d06092a864886f70d01010105000382010f003082010a0282010100c66c299463a8a78abef5ffa45679b7a070b5139834b146aa5138d0f1d8845412e112e4429ceeab23473e395e8aa38b2c024118d85b7ddf504118eabedf9c793bd02c949d6799cabeefe03ff62e304ddec98313afd966bcf13f1fb1a619548a060e17fbede205225b574e679adc9f11bdf9e36b48bea058d360d62b8445f9524db98757a4d59865363c675d28667a5dfa967dd03eea23a2dbea32ab0e9a1f8bb885f5e12723113843a12dd00552fcd4f548b31174aab2610e4a8752f6fca95494584db65cc7bd1ef50ee0d8c8211efb5063a995801cc0c1a903042b7ff7c94094a0de5d7390a8f72a01949cd958c6f2012692bd5dba6f30b09c3c0b69622864450203010001a38201053082010130090603551d1304023000300b0603551d0f0404030203a8301d0603551d0e04160414de90b5d11c6c643c7450d36af8886ca31938fb72306d0603551d230466306480145da7dd700651327ee7b66db3b5e5e060ea2e4defa149a4473045310b300906035504061302434831193017060355040a13104c696e7578207374726f6e675377616e311b3019060355040313127374726f6e675377616e20526f6f74204341820100301e0603551d1104173015811364617665407374726f6e677377616e2e6f726730390603551d1f04323030302ea02ca02a8628687474703a2f2f63726c2e7374726f6e677377616e2e6f72672f7374726f6e677377616e2e63726c300d06092a864886f70d0101040500038201010027a2d727384d2d2432f2f15875fa7693db3af1c7d5317cc21e1658f0843a918875d22c301b08e9c05a8aa3f02f6b8ae6705bb508988210f494fd19d92db786db21c1b6e6b18c0b7baa3fbd427da033fd2c08659daf9bc26dd99cf348c1ec139a9b8c32110199eaea08913f6b3a3d5b0c3d2a6f1f7e2c45b13452858949db416493f96dbf93e2173d81f99bc937b0c0c9e3874f4a90626a571295502ff5cf553dcdbdd7d4673dcbecc8ebbfc3e3ac0ce8a75120d6aa3dd2b6e9a61114cfbf0cba137c5934eddb32cfb96dd02fbf8adc903afa5f8d5959fce7a94fdd9e5a7a3816e35126e50fe7f818887bd2b2365b6b3a86d36a86849e9582d193e6a20b513988'
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  1, 1
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  1, 2
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  2, 3
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  2, 4
);

/* Private Keys */

INSERT INTO private_keys (
   type, data
) VALUES ( /* key of 'C=CH, O=Linux strongSwan, CN=dave@strongswan.org' */
  1, X'308204a40201000282010100c66c299463a8a78abef5ffa45679b7a070b5139834b146aa5138d0f1d8845412e112e4429ceeab23473e395e8aa38b2c024118d85b7ddf504118eabedf9c793bd02c949d6799cabeefe03ff62e304ddec98313afd966bcf13f1fb1a619548a060e17fbede205225b574e679adc9f11bdf9e36b48bea058d360d62b8445f9524db98757a4d59865363c675d28667a5dfa967dd03eea23a2dbea32ab0e9a1f8bb885f5e12723113843a12dd00552fcd4f548b31174aab2610e4a8752f6fca95494584db65cc7bd1ef50ee0d8c8211efb5063a995801cc0c1a903042b7ff7c94094a0de5d7390a8f72a01949cd958c6f2012692bd5dba6f30b09c3c0b696228644502030100010282010100903fb9caa2d8cd5454974a0e12bfd1fad5750e95ac58e462954194c4fcfed690130844e1186d7a04df9a20e2d62f26d20ba17f8a6a990b6bb0a788a0d2b7527b654fc38adaf2372eaffc7b036178c4639e63a84042f02993c8ac25ddf6b43ad34413b396b0a5c2e05c8c274db1ee025bf5fa9ad7fb9d5e75ed044606974835c7fbc39ae84b80acaae9e9624e6fe8ac0ca318ad8a7d1c6ed3a79261464e6ebdb9c02ef20cb1c206c58718d542ed9cb1428c5c3cebbd58dc25598bbdd9924c75fdfeac881949e5f10a7dd4dc25800bdb4bd479ca0bfb706f25847361b2d2565a412813273691b4a3a5a814dce52cdbe25d626e6c9e000ecd6a75cac275187e265102818100e596d3ee25cd98563b12bf718c0ce7e7a823ae8c84f1021552b6b0bf220b7e012861510ab49d612fe7ba05a202edf4927201af0f33f4137481811f884fc46723f94db8ed69b283376f3141ad7e6f0f52afee60e537111c5bd94642564981a822e54edb6797521fb5870c772993ff517ea9c24adcd9dc502f1364d26a3f05ec4f02818100dd3f81e8a4f463488db2b048f2ef208c1c98ee136636b6449cbd3424c93ab25916908823a1ef3a23b4798c77f92a3e29b9469f8014c6b862e23ab5fe6000f9552de01f72c0a1fcc731b0867a3bf1d27596fc9da6ecd74931ce120b1687d2a67b4e4fb32b7fb750b46645aa38ab011a4d5fedd53d20e5ae3a4a5551b6cc5f5d2b02818100ba744b9954ca2bb59c341596398f21a7593de13bed9b6d7db3b6fac3befa6652ba608e588b6664cf6afa00291b07f5601986948d5c3c14b0c19c03e7c82051433dec890b06941b4ca1d8f6e5d7908a7934b7fba92b9791d86614513b9266e20db4fcdde2bb59ceb6b5fec1a7dab1b7958e786424082a8c542f03ea7eaec038b1028180055e2312b7ddce02d69d3d35a7df3154f4e4a8f2038ad44539e0454197383b5779faabb2e19ce236378cb361bdc3ce9a488a74183168d8d45d54bb519e96a775ef94fe6e544a19cde360bb02802dcfc356946e66bc5c44c456918d7f507045e5bbf2a710291b13742cff07b03445e49377fe572c127e4009ddffcfe9b56fa2dd02818040d41f525d885c951dca35924f46e4e7f4e43f4ea2e670230deb674884f5b8599a368b1647dd87523c4fdb62661f6543edecc9ce48d4a7b8b2a29de21fd438a9cf4823b92c85180b390c4f8dfbc196628d349fed1edd32cba5c063e2739d2153d3677d4815e55b8b4e9d0989b32cf0060de2ded4cd59edf6a4364cb55aff9276'
);

INSERT INTO private_key_identity (
  private_key, identity
) VALUES (
  1, 3
);

INSERT INTO private_key_identity (
  private_key, identity
) VALUES (
  1, 4
);

/* Configurations */

INSERT INTO ike_configs (
  local, remote
) VALUES (
  'PH_IP_DAVE', 'PH_IP_MOON'
);

INSERT INTO peer_configs (
  name, ike_cfg, local_id, remote_id
) VALUES (
  'home', 1, 3, 5
);

INSERT INTO child_configs (
  name, updown
) VALUES (
  'home', 'ipsec _updown iptables'
);

INSERT INTO peer_config_child_config (
  peer_cfg, child_cfg
) VALUES (
  1, 1
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES ( /* 10.1.0.0/16 */
  7, X'0a010000', X'0a01ffff'
);

INSERT INTO traffic_selectors (
  type
) VALUES ( /* dynamic/32 */
  7
);

INSERT INTO child_config_traffic_selector (
  child_cfg, traffic_selector, kind
) VALUES (
  1, 1, 1
);

INSERT INTO child_config_traffic_selector (
	child_cfg, traffic_selector, kind
) VALUES (
  1, 2, 2
);

