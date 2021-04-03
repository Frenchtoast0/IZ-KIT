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
    <script src="./js/accounts.js"></script>
    <script src="./js/ajax.js"></script>
    <title>IZ-Kit Accounts</title>
</head>
<body class="text-center text-white bg-dark">
    <section class="space-top-little">
        <h1>Accounts Manager</button></h1>

        <div class="container">
            <table id="accountsTable" class="table-responsive mx-auto tableStyle">
                <thead>
                    <tr>
                        <td scope="col">Op</td>
                        <td scope="col">UserID</td>
                        <td scope="col">Username</td>
                    </tr>
                </thead>
                <tbody>
                </tbody>
            </table>
        </div> 

        <br>
        <label id="status" class="mt-1"></label>
            
        <br>
        <a href="./index.php">Back</a>

        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>

</html>