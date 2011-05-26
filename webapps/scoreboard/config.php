<?php
if (!$is_included) exit();

$config['db']  = "../../stats.db";

$mysql["host"] = "localhost";
$mysql["port"] = "";
$mysql["user"] = "user";
$mysql["pass"] = "pass";
$mysql["db"]   = "database";

$config['use_mysql'] = 0; // 1: use mysql 0: use sqlite

$config['res_per_page'] = 25; // results per page

$config['geoip_db_path'] = "db/geoip/GeoIP.dat";

$config['show_kpg']     = 1;
$config['show_country'] = 1;
$config['table_width']  = 1050;

$config['exclude_names'] = array("unnamed" => "", "bot" => "0.0.0.0");

?>