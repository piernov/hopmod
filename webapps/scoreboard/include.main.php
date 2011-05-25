<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
$is_included = true;
$include_directory = dirname(__FILE__);


include $include_directory."/config.php";

if ($config['use_mysql']) {
    include $include_directory."/function/db/mysql_connector.php";
    include $include_directory."/function/db/mysql_read.php";
} 
else {
    include $include_directory."/function/db/sqlite_connector.php";
    include $include_directory."/function/db/sqlite_read.php";
}

include $include_directory."/function/functions.php";
include $include_directory."/function/geoip/geoip.php";

?>