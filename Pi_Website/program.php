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
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <link rel="stylesheet" href="./css/style.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="./js/program.js"></script>
    <script src="./js/ajax.js"></script>
    <title>IZ-Kit Program</title>
</head>
<body class="text-center text-white bg-dark">
    <section class="space-top-little container">
        <h1>Program the IZ-Kit Controller</h1>
        
        <button type="button" id="saveButton" class="btn btn-md btn-primary">Save Program</button>
        <button type="button" id="loadButton" class="btn btn-md btn-warning">Load Program</button>
        <textarea id="code" class="form-control no-focus-border mt-1 mx-auto" autofocus="true"></textarea>
        <button type="button" id="uploadButton" class="btn btn-lg btn-success mt-1">Upload</button>
        
        <br>
        <label id="status" class="mt-1"></label>
        <br>
        <a href="./index.php">Back</a>

        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>
</html>