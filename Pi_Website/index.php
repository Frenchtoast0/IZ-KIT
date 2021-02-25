<?php
    session_start();

    if (!isset($_SESSION["username"]))
    {
        header("location: login.php");
        die();
    }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IZ-Kit Management Interface</title>
</head>
<body>
You have logged in successfully.
    <a href="./program.php">Program Page</a>
    <form method="POST" action="./login.php">
        <button type="submit" name="submit" value="Logout">Logout</button>
    </form>
</body>
</html>