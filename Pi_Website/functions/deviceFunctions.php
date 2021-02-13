<?php
//************************************************
// File: deviceFunctions.php
// Description: collection of device functions
//              to interface with db
//************************************************

//register device in db
//$postData - POST data in
//return - successfullnes of register
function RegisterDevice($postData)
{
    $data = array(); //json data value
    $status = false; //json success value


    //DEBUG stuff -> replace with actual
    $data[] = $postData["id"];
    $data[] = $postData["state"];
    $status = "successfully added device";


    //package and send function values
    $response["data"] = $data;
    $response["status"] = $status;
    return $response;
}

//update device state in db
//$postData - POST data in
//return - successfulness of update
function UpdateDevice($postData)
{
    $data = array(); //json data value
    $status = false; //json success value

    //DEBUG stuff -> replace with actual
    $data[] = $postData["id"];
    $data[] = $postData["state"];
    $status = "successfully updated device state";

    //package and send function values
    $response["data"] = $data;
    $response["status"] = $status;
    return $response;
}

?>