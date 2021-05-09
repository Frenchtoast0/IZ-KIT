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

//uploads a new circuit to the device db
//$wire - circuit to parse
//return - successfulness of create
function UploadProgram($wire)
{
    global $mysqli;

    $data = array(); //JSON response object

    //get circuit name
    $name = $wire["Name"];

    //setup circuit on sql end
    $query = "INSERT INTO Circuits (Name) VALUES ('$name')";
    if (SQLi_NonQuery($query) > 0) //check for errors
    {
        $circuitID = SQLi_InsertID();
    }    
    else
    {
        $data["status"] = "Error: " . $mysqli->error;
        return $data;
    }

    //get inputs
    foreach($wire["Inputs"] as $input)
    {
        $id = $input["ID"];
        $sign = $input["Sign"];
        $value = $input["Value"]; 
	
        //sql insert input
        $query = "INSERT INTO Input (DevID, Sign, OnVal) VALUES ('$id', '$sign', '$value')";
        if (SQLi_NonQuery($query) > 0) //check for errors
        {
            $inputID = SQLi_InsertID();
        }    
        else
        {
            $data["status"] = "Error: " . $mysqli->error;
            return $data;
        } 

        //insert connection to circuit
        $query = "INSERT INTO CircuitToInput (InID, CrID) VALUES ('$inputID', '$circuitID')";
        if (SQLi_NonQuery($query) < 1) //check for errors
        {
            $data["status"] = "Error: " . $mysqli->error;
            return $data;
        }
    }

    //get outputs
    foreach($wire["Outputs"] as $output)
    {
        $id = $output["ID"];
        $value = $output["Value"]; 

        //sql insert
        $query = "INSERT INTO Output (DevID, SetVal) VALUES ('$id', '$value')";
        if (SQLi_NonQuery($query) > 0) //check for errors
        {
            $outputID = SQLi_InsertID();
        }    
        else
        {
            $data["status"] = "Error: " . $mysqli->error;
            return $data;
        } 

        //insert connection to circuit
        $query = "INSERT INTO CircuitToOutput (OtID, CrID) VALUES ('$outputID', '$circuitID')";
        if (SQLi_NonQuery($query) < 1) //check for errors
        {
            $data["status"] = "Error: " . $mysqli->error;
            return $data;
        }
    }

    //no errors
    $data["status"] = "Successfully uploaded";
    return $data;
}
/*//regex splits wire into manageable block
//returns - $wire as associative array
function ParseWire($wire)
{
    //get inputs/outputs
    preg_match_all('/(?<=inputs:).*(?=outputs)/gmi', $wire, $inputList);
    preg_match_all('/(?<=outputs:).*(?=})/gmi', $wire, $outputList);

    //break apart input strings
    $data["Inputs"] = array();
    $inputs = preg_split('/\,/', $inputList);
    for ($i = 0; $i < count($inputs); $i++)
    {
        $it = array();
        preg_match('/[a-z\-0-9]*(?=[<=>][<=>])/gmi', $inputs[$i], $val);
        $it["ID"] = $val;
        preg_match('/[=><]=/gmi', $inputs[$i], $val);
        $it["Sign"] = $val;
        preg_match('/(?<=")[a-z0-9]*(?=")/gmi', $inputs[$i], $val);
        $it["Value"] = $val;

        $data["Inputs"][] = $it;
    }
    
    //break apart output strings
    $data["Outputs"] = array();
    $outputs = preg_split("/\,/", $outputList[0]);
    for ($i = 0; $i < count($outputs); $i++)
    {
        $o = array();
        preg_match('/[a-z\-0-9]*(?==)/gmi', $outputs[$i], $val);
        $o["ID"] = $val;
        preg_match('/(?<=")[a-z0-9]*(?=")/gmi', $outputs[$i], $val);
        $o["Value"] = $val;

        $data["Outputs"][] = $o;
    }

    return $inputList[0];
}*/

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

//Locks admin value in device stats table
//returns - status
function AdminLock($postData)
{
    $data = array();

    $id = $postData["ID"];

    //determine checked value
    if ($postData["checked"] == "ON") $checked = 1;
    else $checked = 0;

    //update table
    $query = "UPDATE Stats SET Admin = $checked WHERE ID = '$id'";
    
    if (SQLi_NonQuery($query))
    {
        $data["status"] = "Updated admin lock to " . $postData["checked"] . " on " . $postData["ID"];
    }
    else
    {
        $data["status"] = "Error: admin lock change failed!";
    }
    
    return $data;
}

//Changes device state
//returns - status
function ChangeState($postData)
{
    $data = array();

    $id = $postData["ID"];
    $val = $postData["value"];

    //update table
    $query = "UPDATE Stats SET Val='$val' WHERE ID='$id'";
    
    if (SQLi_NonQuery($query))
    {
        $data["status"] = "Changed state of " . $postData["ID"] . " to " . $postData["value"];
    }
    else
    {
        $data["status"] = "Error: state change failed!";
    }
    
    return $data;
}

//Deletes all programs in db
//returns - status of delete
function DeleteCircuits()
{
    global $mysqli_status;

    $data = array();

    //clear program tables
    $query = "DELETE FROM Circuits; DELETE FROM Input; DELETE FROM Output; DELETE FROM CircuitToInput; DELETE FROM CircuitToOutput";
    if (SQLi_MultiQuery($query))
        $data["status"] = "Successfully cleared all programs!";
    else
        $data["status"] = $mysqli_status;

    return $data;
}

?>