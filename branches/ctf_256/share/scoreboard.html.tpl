<html>
<head>
<title>@title scoreboard</title>
<style type="text/css">
body,table
{
    font-family: Verdana,Helvetica,Arial,sans-serif;
    font-size:84%;
}
body
{
    background-color: #302c28;
    color: #EEEEEE;
    text-align:center;
}
a{color:#FFBB00;}
a:hover{color: #FF9900;}
a:visited{color:#e51d14;}
table
{
    border-collapse:collapse;
}
table td,table th{border:solid 1px  #555555;}
table th{background-color:#3f3934;}
table th{padding:15px;}
table td{padding:5px; color:#EEEEEE;}
.highlight td{color: #ffba00}
.footer
{
    margin-top:20px;
    color: #a0a0a0;
    font-size:small;
}
</style>
</head>
<body>
<h1>@title @(month (now)) Scoreboard</h1>
<table align="center" cellpadding="0" cellspacing="0">
<tr>@scoreboardgen_html_tblhdrs </tr>
@scoreboardgen_html_tbldata
</table>
<div class="footer">
<span id="cdate">This page was last updated @(date (now)).</span> | <a href="http://www.sauerbraten.org">Sauerbraten.org</a> | <a href="http://hopmod.e-topic.info">Hopmod</a>
</div>
</body>
</html>