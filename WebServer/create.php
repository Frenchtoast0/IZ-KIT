<?php
    require_once "./functions/userFunctions.php";

    //default values
    $responseParams["response"] = "default";
    $responseParams["status"] = "";

    //user submitted form to make account
    if (isset($_POST["submit"]) && $_POST["submit"] == "Create")
    {
        $createParams = array();

        //set create values after sanitization
        $createParams["username"] = strip_tags($_POST["username"]);
        $createParams["password"] = strip_tags($_POST["password"]);
        $createParams["password2"] = strip_tags($_POST["password2"]);
        $createParams["serial"] = strip_tags($_POST["serial"]);
        $createParams["response"] = "";
        $createParams["status"] = false;

        //validate and create user
        $responseParams = CreateUser($createParams);
    }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <link rel="stylesheet" href="./css/style.css">
    <title>IZ-Kit Create Account</title>
</head>
<body class="text-center text-white bg-dark">
    <?php
        if ($responseParams["status"] == "error")
            echo "<div class=\"alert alert-danger\"><strong>Error: </strong>" . $responseParams["response"] . "</div>";
        elseif ($responseParams["status"] == "success")
            echo "<div class=\"alert alert-success\"><strong>Success: </strong>" . $responseParams["response"] . "</div>";
    ?>
    <section class="space-top container">
        <h1>Create an Account</h1>
        <form class="mx-auto" method="POST" action="./create.php">
            <input class="form-control" type="text" name="username" placeholder="Username" required>
            <input class="form-control up-a-bit" type="password" name="password" placeholder="Password" required>
            <input class="form-control up-a-bit" type="password" name="password2" placeholder="Retype password" required>
            <div>
                <input class="form-control up-a-bit" type="text" name="serial" placeholder="Serial number" required>
                <span class="form-text">The serial number is found in your IZ KIT.</span>
            </div>
            <button type="submit" class="btn btn-md btn-primary mt-1" name="submit" value="Create">Create</button>
        </form>

        <a href="./index.php">Back</a>
        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>
</html>