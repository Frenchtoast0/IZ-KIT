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
    <main>
        <section class="space-top-little">
            <h1>Admin Panel</h1>

            <div id="DeviceCards" class="container">
                <template>
                    <div class="card text-dark" style="width: 300px;">
                        <img class="card-img-top" src="">
                        <div class="card-body">
                            <h5 class="card-title">Device ID</h5>
                            <p class="card-text">Device description</p>
                            <ul class="list-group">
                                <li class="list-group-item">
                                    <label for="curValue">Current Value:</label>
                                    <input type="text" readonly="true" id="curValue">
                                </li>
                                <li class="list-group-item">
                                    <label for="lock">Admin Lock</label>
                                    <input type="checkbox" id="lock">
                                </li>
                                <li class="list-group-item">
                                    <label for="newValue">New Value:</label>
                                    <input type="text" id="newValue">
                                    <button class="btn btn-primary" id="Enter">Enter</button>
                                </li>
                            </ul>
                        </div>
                    </div>
                </template>
            </div>

            <label id="status"></label>
            
            <a href="./index.php">Back</a>

            <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
        </section>
    </main>
</body>
</html>