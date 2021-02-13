<?php
//************************************************
// File: userFunctions.php
// Description: collection of user functions
//              to interface with db
//************************************************

//register user in db
//$postData - POST data in
//return - successfulness of register
function RegisterUser($postData)
{
    $data = array(); //json data value
    $status = false; //json success value

    //place actual code here

    //package and send function values
    $response["data"] = $data;
    $response["status"] = $status;
    return $response;
}

?>