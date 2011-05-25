<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
if (!$is_included) exit();

function open_db() {
	global $config, $db;
	$db = @new SQLite3($config['db']);
	return $db != NULL;
}

?>