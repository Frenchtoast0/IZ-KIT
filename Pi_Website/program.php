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
    <title>IZ-Kit Program</title>
</head>
<body class="text-center text-white bg-dark">
    <main>
        <section id="MainBox">
            <h1>Program the IZ-Kit Controller</h1>
            <form class="mx-auto">
                <textarea id="program" class="form-control"></textarea>
                <button type="submit" class="btn btn-md btn-success mt-1">Upload</button>
            </form>
            <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
        </section>
    </main>
</body>
</html>