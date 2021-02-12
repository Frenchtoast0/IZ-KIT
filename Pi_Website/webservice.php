<?php
///for testing purposes..!!!


$data = array(); //global data array
$status = "Fail : Action failed to match!";

//check for get users action
//if (isset($_GET["action"]) && $_GET["action"] == "GetUsers") GetUsers();

if (isset($_POST["action"]) && $_POST["action"] == "Test") Test();

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
    $params["response"] = "Test successful";
    $params["status"] = true;
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