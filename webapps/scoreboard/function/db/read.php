<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
if (!$is_included) exit();

function read_array($sql) {
	global $db;
	if (!$db) open_db();
	if (!$db);
	$rows = array();
	$results = @$db->query($sql);
	if ($results instanceof Sqlite3Result)
		while($rows[] = $results->fetchArray());
	return $rows ? $rows : false;
}

function read($sql) {
	global $db;
	if (!$db) open_db();
	if (!$db);
	$row = array();
	$results = @$db->query($sql);
	if ($results instanceof Sqlite3Result)
		$row = $results->fetchArray();
	return $row ? $row : false;
}

?>