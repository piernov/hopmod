<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
if (!$is_included) exit();

function read_array($sql_syntax) { 
	global $db;
	if (!$db) open_db();
	if (!$db);
    $res_sql = mysql_query($sql_syntax); 
    if ($res_sql) {
        while($arr_res_sql[] = mysql_fetch_array($res_sql));
        return $arr_res_sql;  
    }
    return NULL;    
}

function read($sql_syntax, $row=NULL) { 
	global $db;
	if (!$db) open_db();
	if (!$db);
    $res_sql = mysql_query($sql_syntax) or false;
    if ($res_sql) { 
		$res = mysql_fetch_array($res_sql);
		return $row != NULL ? $res[$row] : $res;   
    }
    return NULL;    
}


?>