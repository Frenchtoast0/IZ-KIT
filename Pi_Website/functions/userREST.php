<?php
//************************************************
// File: userREST.php
// Description: collection of user functions
//              to interface with db via REST
//************************************************
require_once "../../inc/db.php"; //connect to db

//Saves sent text contents to file in user's directory
//returns - success/fail
function SaveProgram($json)
{
    $data = array(); //json response
    
    $path = "/home/izkit/Programs/". $_SESSION["userID"];
    $filename =  $path . "/code.txt";

    //make sure directory exists
    if (!is_dir($path)) mkdir($path, 0755);

    //save file
    if ($file = fopen($filename, "w"))
    {
        fwrite($file, $json["code"]);
        $data["status"] = "Successfully saved program";
        fclose($file);
    }
    else
    {
        $data["status"] = "Save failed";
    }
        
    return $data;
}

//Loads text contents from file in user's directory
//returns - text contents
function LoadProgram()
{
    $data = array(); //json response

    $filename = "/home/izkit/Programs/" . $_SESSION["userID"] . "/code.txt";

    //check if file exists
    if (!file_exists($filename))
    {
        $data["status"] = "No saved program exists";
        $data["code"] = "";
    }
    else
    {
        //open file
        if ($file = fopen($filename, "rb"))
        {
            $data["code"] = fread($file, filesize($filename));
            fclose($file);
            $data["status"] = "Successfully loaded program";
        }
        else
        {
            $data["status"] = "Load failed";
            $data["code"] = "";
        }
    }

    return $data;
}

//returns a list of users
//and a status
function GetUsers()
{
    $data = array();

    $query = "SELECT ID, Username FROM Users";

    //user found
    if ($result = SQLi_Query($query))
    {
        //add returned data to data array
        while ($row = $result->fetch_assoc())
        {
            $data["data"][] = $row;
        }

        $data["status"] = "{$result->num_rows} results found";
    }
    else
    {
        $data["status"] = "DB query failed!";
    }

    return $data;
}

//returns a list of users
//and a status
function DeleteUser($json)
{
    $data = array();

    //get userID to delete
    $uid = $json["userID"];

    if ($uid != $_SESSION["userID"])
    {
        $query = "DELETE FROM Users WHERE ID = '$uid'";

        $rows = SQLi_NonQuery($query);
    
        //return affected rows
        $data["status"] = " {$rows} record(s) deleted";

        //delete program file as well
        $path = "/home/izkit/Programs/" . $json["userID"] ;
        if (is_dir($path))
        {
            unlink($path . "/code.txt");
            rmdir($path);
        }  
    }
    else
        $data["status"] = "Error: Cannot delete yourself!";

    return $data;
}
?>