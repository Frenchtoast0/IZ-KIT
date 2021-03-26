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
    <script src="./js/admin.js"></script>
    <script src="./js/ajax.js"></script>
    <title>IZ-Kit Program</title>
</head>
<body class="text-center text-white bg-dark">
    <main>
        <section class="space-top-little">
            <h1>Admin Panel <button class="btn btn-primary" id="refresh"><img height="32" width="32" src="./img/refresh.png"></button></h1>
            <br/>
            

            <div class="container">
                <table id="deviceTable" class="table table-bordered">
                    <thead>
                        <tr>
                            <td scope="col">Device ID</td>
                            <td scope="col">Current State</td>
                            <td scope="col">I/O</td>
                            <td scope="col">Description</td>
                            <td scope="col">Admin Lock</td>
                            <td scope="col">Change State</td>
                        </tr>
                    </thead>
                    <tbody>
                    </tbody>
                </table>
            </div> 

            <label id="status"></label>
            <br>
            
            <a href="./index.php">Back</a>

            <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
        </section>
    </main>
</body>
</html>