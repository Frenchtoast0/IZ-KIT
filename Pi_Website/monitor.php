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
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <title>IZ-Kit Server Monitor</title>
    <link rel="stylesheet" href="./css/style.css">
</head>
<body class="text-center text-white bg-dark">
    <section class="space-top-little">
        <h1>Server Monitor</h1>

        <textarea id="code" class="form-control no-focus-border mt-1 mx-auto" readonly="true" autofocus="true"></textarea>
        <a href="./index.php">Back</a>

        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>

</html>