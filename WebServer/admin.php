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
    <title>IZ-Kit Admin</title>
</head>
<body class="text-center text-white bg-dark">
    <section class="space-top-little">
        <h1>Admin Panel <button class="btn btn-primary" id="refresh"><img height="32" width="32" src="./img/refresh.png"></button></h1>

        <div class="container">
            <table id="deviceTable" class="table-responsive mx-auto tableStyle">
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

        <!--modal trigger -->
        <button class="btn btn-danger mt-1" id="eraseButton" data-toggle="modal" data-target="#confirmDelete">
            Clear Programs
        </button>

        <br>
        <label id="status" class="mt-1"></label>
        
        <br>
        <a href="./index.php">Back</a>

        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>

        <!-- modal dialogue modified from Bootstrap documentation-->
        <div class="modal fade" id="confirmDelete" tabindex="-1" role="dialog">
        <div class="modal-dialog" role="document">
            <div class="modal-content text-dark">
                <div class="modal-header">
                    <h5 class="modal-title">Are you sure you want to delete?</h5>
                    <button type="button" class="close btn" data-dismiss="modal">
                    <span class="text-lg"><h3>&times;</h3></span>
                    </button>
                </div>
                <div class="modal-body">
                    <p>This action cannot be reversed, it will delete all the circuit programs from the database.</p>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                    <button type="button" class="btn btn-danger" id="deleteButton" data-dismiss="modal">Confirm Delete</button>
                </div>
            </div>
    </section>
</body>

<!-- Bootstrap scripts: Popper.js, then Bootstrap JS -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
</html>