<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
$is_included = true;
$include_directory = dirname(__FILE__);


include $include_directory."/config.php";
include $include_directory."/function/db/connector.php";
include $include_directory."/function/db/read.php";
include $include_directory."/function/functions.php";
include $include_directory."/function/geoip/geoip.php";

?>