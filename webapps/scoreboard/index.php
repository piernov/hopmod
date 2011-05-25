<?php
/*
 * (c) 2011 by Thomas Poechtrager
 */
?>
<html>
<head>
	<title></title>
	<link href="css/style.css" rel="stylesheet" type="text/css">
	<link href="css/table.css" rel="stylesheet" type="text/css">
	<script type="text/javascript" src="js/jquery-1.5.1.min.js"></script>
	<script type="text/javascript" src="js/jquery.tablesorter.min.js"></script> 
	<script type="text/javascript">$(document).ready(function() { $("#scoreboard").tablesorter(); } );</script>
    <script language="javascript">
        if (screen.width < 1280 || screen.height < 1024) {
            alert("This page is optimized for perfect use in 1280x1024!\nYour Resolution is " + screen.width + "x" + screen.height + ".");
        }
    </script>    
</head>
<body>

<?php
include "include.main.php";

start_benchmark();

if ($_GET["gamelist"] != "") $result = get_gamelist_table($_GET["page"], $_GET["days"]);
if ($_GET["game_id"] != "") $result = get_game_table($_GET["game_id"]);

if ($result == NULL) $result = get_player_table($_GET["page"], $_GET["days"], $_GET["player"]);

close_geoip();

if (!$result) { 
	echo "Error: Unable to open Database.";
}
else {
?>
<div align="center">
<?php 
echo $result[0];
echo generate_pagelist($result[1], $_GET["page"]);
?>
</div>
<?php
}//end if

//end_benchmark();

?>
</body>
</html>