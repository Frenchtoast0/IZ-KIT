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
    <main class="space-top">
        <section id="MainBox">
            <h1>Create an account</h1>
            <form class="mx-auto">
                <input class="form-control" type="text" placeholder="Username" required>
                <input class="form-control up-a-bit" type="password" placeholder="Password" required>
                <div>
                    <input class="form-control up-a-bit" type="text" placeholder="Serial Number" required>
                    <span class="form-text">The serial number is found on your controller.</span>
                </div>
                <button type="submit" class="btn btn-md btn-primary mt-1">Create</button>
            </form>
            <a href="./index.php">Back</a>
            <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
        </section>
    </main>
</body>
</html>