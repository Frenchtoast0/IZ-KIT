<?php
    require_once "./functions/userFunctions.php";

    session_start();

    //default values
    $responseParams["status"] = true;

    //user submitted form as logout
    if (isset($_POST["submit"]) && $_POST["submit"] == "Logout")
    {
        //destroy session
        session_unset();
        session_destroy();

        //waterfall effect to refresh
        header("location: index.php");
    }
    //user submitted form as login
    elseif (isset($_POST["submit"]) && $_POST["submit"] == "Login")
    {
        $loginParams = array();

        //set login values after sanitization
        $loginParams["username"] = filter_var($_POST["username"], FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_HIGH);
        $loginParams["password"] = filter_var($_POST["password"], FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_HIGH);
        $loginParams["response"] = "";
        $loginParams["status"] = false;

        //validate credentials
        $responseParams = ValidateUser($loginParams);

        //successful validation
        if ($responseParams["status"])
        {
            header("location: index.php");
            die();
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <link rel="stylesheet" href="./css/style.css">
    <title>IZ-Kit Control</title>
</head>
<body class="text-center text-white bg-dark">
    <?php
        if ($responseParams["status"] == false)
            echo "<div class=\"alert alert-danger\"><strong>Error: </strong>" . $responseParams["response"] . "</div>";
    ?>
    <section id="" class="space-top container-sm">
        <h1>Welcome to the IZ-Kit Management Interface</h1>
        <h5 class="fw-normal">Please login or <a href="./create.php">create an account</a>:</h5>
        <form class="mx-auto" method="POST" action="login.php">
            <input class="form-control" type="text" name="username" placeholder="Username" required>
            <input class="form-control up-a-bit" type="password" name="password" placeholder="Password" required>
            <button type="submit" class="btn btn-md btn-primary mt-1" name="submit" value="Login">Login</button>
        </form>  
        </div>
        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>
</html>