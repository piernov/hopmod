<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
$is_included = true;
$include_directory = dirname(__FILE__);

if(!ini_get('safe_mode')) {
    /*
        well, a lot results need a lot space in the memory,
        if showall is given, then all results need to be fetched, 
        and if the memory limit is set below 256 MB, then it can 
        happen (on very big databases) that a 
        size of x bytes exhausted (tried to allocate y bytes)
        error appears.
    */
    ini_set('memory_limit', '256M'); 
}

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