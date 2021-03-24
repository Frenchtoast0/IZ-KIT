<?php
//************************************************
// File: deviceFunctions.php
// Description: collection of device functions
//              to interface with db
//************************************************
require_once "../../inc/db.php"; //connect to db

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
//$wire - program connection info
//return - successfulness of create
function UploadProgram($wire)
{
    $data = array(); //json data value
    $status = false; //json success value

    //get circuit name
    $name = $wire["Name"];

    //setup circuit on sql end
    $query = "INSERT INTO Circuits (Name) VALUES ('$name')";
    SQLi_NonQuery($query);
    $circuitID = SQLi_InsertID();

    //get inputs
    foreach($wire["Inputs"] as $input)
    {
        $id = $input["ID"];
        $sign = $input["Sign"];
        $value = $input["Value"]; 
	
	    error_log(join($input,','));
	    error_log($sign); 
        //sql insert input
        $query = "INSERT INTO Input (DevID, Sign, OnVal) VALUES ('$id', '$sign', '$value')";
        SQLi_NonQuery($query);
        $inputID = SQLi_InsertID();

        //insert connection to circuit
        $query = "INSERT INTO CircuitToInput (InID, CrID) VALUES ('$inputID', '$circuitID')";
        SQLi_NonQuery($query);
    }

    //get outputs
    foreach($wire["Outputs"] as $output)
    {
        $id = $output["ID"];
        $value = $output["Value"]; 

        //sql insert
        $query = "INSERT INTO Output (DevID, SetVal) VALUES ('$id', '$value')";
        SQLi_NonQuery($query);
        $outputID = SQLi_InsertID();

        //insert connection to circuit
        $query = "INSERT INTO CircuitToOutput (OtID, CrID) VALUES ('$outputID', '$circuitID')";
        SQLi_NonQuery($query);
    }

    //package and send function values
    $response["data"] = $data;
    $response["status"] = true;
    return $response;
}

//returns a list of the devices in the db
//return - json list of device state table
function GetDevices()
{
    $data = array();

    //get connected devices
    $query = "SELECT ID,Val,IO,Dsc,Admin FROM Stats WHERE not Val = 'Disconnected'";
    if ($result = SQLi_Query($query))
    {
        while ($row = $result->fetch_assoc())
        {
            $data[] = $row;
        }
    }

    return $data;
}

?>