<?php
//************************************************
// File: deviceFunctions.php
// Description: collection of device functions
//              to interface with db
//************************************************
/*
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
*/

//uploads a new program to the devices
//$postData - program text string
//return - successfulness of create
function UploadProgram($postData)
{
    $data = array(); //json data value
    $status = false; //json success value

    $code = json_decode($postData);

    //loop through wire blocks
    foreach($code as $key=>$value)
    {
        //debug, send out kvp pairs
        $data[$key] = $value;
    }

    //package and send function values
    $response["data"] = $data;
    $response["status"] = $status;
    return $response;
}

//sends an admin command to the devices
//$postData - program text string
//return - successfulness of send
function SendAdmin($postData)
{
    $data = array(); //json data value
    $status = false; //json success value

    $code = json_decode($postData);

    //debug, simple return
    $data = $code;

    //package and send function values
    $response["data"] = $data;
    $response["status"] = $status;
    return $response;
}

?>