<?php
//mysqli Database Utility File

$mysqli = null;             //db connection object
$mysqli_status = "";        //global status variable

//attempt connection and populate mysqli connection object
//executed once per page request
function SQLi_Connect()
{
    global $mysqli, $mysqli_status;

    $mysqli = new mysqli("localhost", "izkit_dbuser", "DBpassword!$", "izkit_db");

    //connection failed, exit with error code
    if ($mysqli -> connect_error)
    {
        $mysqli_status = "Connect Error ({$mysqli->connect_errno}) {$mysqli->connect_error}";
        die(); //exit after closing outstanding things
    }
}

//queries db, binds resultset to result object
function SQLi_Query($query)
{
    global $mysqli, $mysqli_status;

    //db not connected
    if ($mysqli == null)
    {
        $mysqli_status = "No mysqli connection!";
        return false;
    }

    //execution failed
    if (!($result = $mysqli->query($query)))
    {
        $mysqli_status = "mySqliQuery:Error ({$mysqli->errno}) {$mysqli->error}";
        return false;
    }
    
    $mysqli_status = "SQL query successful!";

    //return resultset
    return $result;
}

//queries db, returns TRUE/FALSE rather than results
function SQLi_NonQuery($query)
{
    global $mysqli, $mysqli_status;

    //db not connected
    if ($mysqli == null)
    {
        $mysqli_status = "No mysqli connection!";
        return 0;
    }

    //execution failed
    if (!($result = $mysqli->query($query)))
    {
        $mysqli_status = "mySqliQuery:Error ({$mysqli->errno}) {$mysqli->error}";
        return -1;
    }

    $mysqli_status = "SQL query successful! {$mysqli->affected_rows} rows affected.";

    //return result count
    return $mysqli->affected_rows;
}

SQLi_Connect(); //connect on every page this is added to

?>