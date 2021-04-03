<?php
//************************************************
// File: userFunctions.php
// Description: collection of user functions
//              to interface with db without REST
//************************************************
require_once "./inc/db.php";

//enable access to the session
session_start();

//adds a new user to the db
//$params - values to make user with
//*NOTE: "error" or "success", no true/false
function CreateUser($params)
{
    //first check if serial number is alright
    if (file_get_contents('./serialNum.txt') != $params["serial"]) //serial must match entire file
    {
        $params["response"] = "Incorrect serial number!";
        $params["status"] = "error";
    }
    //check for errors
    elseif (strlen($params["username"]) < 3)
    {
        $params["response"] = "Username must be at least 3 characters long!";
        $params["status"] = "error";
    }
    elseif (strlen($params["password"]) < 8)
    {
        $params["response"] = "Password must be at least 8 characters long!";
        $params["status"] = "error";
    }
    elseif ($params["password"] != $params["password2"])
    {
        $params["response"] = "Passwords do not match!";
        $params["status"] = "error";
    }
    elseif (preg_match('/[\'^£$%&*()}{@#~?><>,|=_+¬-]/', $params["username"]))
    {
        $params["response"] = "Username may not contain special characters!";
        $params["status"] = "error";
    }
    elseif (preg_match('/[\'^()}{><>|=]/', $params["password"]))
    {
        $params["response"] = "Username may not contain these special characters: '/[\'^()}{><>|=]/'";
        $params["status"] = "error";
    }
    //valid inputs
    else
    {
        $uname = $params["username"];
        $pword = password_hash($params["password"], PASSWORD_DEFAULT);
    
        $checkQuery = "SELECT * FROM Users WHERE Username = '$uname'";
        
        //make sure user doesn't exist already
        if (SQLi_NonQuery($checkQuery) <= 0)
        {
            //query to add user
            $query = "INSERT INTO Users (Username, Password) VALUES (\"$uname\", \"$pword\")";

            $rows = SQLi_NonQuery($query);

            //successfully inputted
            if ($rows == 1)
            {
                $params["response"] = "User successfully created!";
                $params["status"] = "success";
            }
            else
            {
                global $mysqli;
                $params["response"] = "User creation failed!";
                error_log("Error: " . $mysqli->error);
                $params["status"] = "error";
            }
        }
        else
        {
            $params["response"] = "User already exists"; 
            $params["status"] = "error";
        }
    }
    return $params;
}

//validates user credentials and logs them in
//$params - user credentials
function ValidateUser($params)
{
    $query = "SELECT ID, Username, password FROM Users WHERE Username = '{$params["username"]}'";

    $result = null; //login query result
    $row = null;    //login query result row

    //user found
    if ($result = SQLi_Query($query))
    {
        $row = $result->fetch_assoc(); //get returned row

        //check what kind of result found
        switch ($result->num_rows)
        {
            //successful login
            case 1:
                if (password_verify($params["password"], ($row["password"])))
                {
                    $_SESSION["username"] = $row["Username"];
                    $_SESSION["userID"] = $row["ID"];

                    $params["response"] = "Successfully authenticated!";
                    $params["status"] = true;
                }
                else
                {
                    $params["response"] = "Incorrect password!";
                    $params["status"] = false;
                }
                break;
            //more than one user with same username
            case 2:
                $params["response"] = "User \"{$params["username"]}\" has duplicates!";
                $params["status"] = false;

                break;
            //no user with that username
            case 0:
            case -1:
                $params["response"] = "User \"{$params["username"]}\" does not exist!";
                $params["status"] = false;
                break;
        }
    }
    else
    {
        $params["response"] = "DB query failed!";
        $params["status"] = false;
    }

    //send back updated parameters
    return $params;
}
?>