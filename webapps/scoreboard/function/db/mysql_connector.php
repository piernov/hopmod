<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
if (!$is_included) exit();

function open_db() {
	global $mysql, $db;
    $db = @mysql_connect($mysql["host"].':'.$mysql["port"], $mysql["user"], $mysql["pass"]) or false;
    @mysql_select_db($mysql["db"]) or die("unable to select mysql database");
	return true;
}

?>