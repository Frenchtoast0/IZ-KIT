<?php
///for testing purposes..!!!


$data = array(); //global data array
$status = "Fail : Action failed to match!";

if (isset($_POST["id"]) && isset($_POST["state"])) Test1();
//if (isset($_GET["action"]) && $_GET["action"] == "test") Test();
//if (isset($_POST["action"]) && $_POST["action"] == "testX") Test();

//get user data dump from db
function GetUsers()
{
    global $data, $status;

    $params["response"] = "DB query failed!";
    $params["status"] = false;

    Done();
}

function Test()
{
    global $data, $status;

    $data = "Test successful";
    $status = true;
}

function Test1()
{
    global $data, $status;

    $data = $_POST["id"];
    $status = $_POST["state"];
}

//return processed response
function Done()
{
    global $data, $status;
    
    //create associative array
    $response["data"] = $data;
    $response["status"] = $status;

    //convert to json
    echo json_encode($response);

    die();
}

//call to service invalid, return defaults
Done();
?>