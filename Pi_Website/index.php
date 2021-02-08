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
    <main class="space-top">
        <section id="MainBox">
            <h1>Welcome to the IZ-Kit Management Interface</h1>
            <h5 class="fw-normal">Please login or <a href="./create.php">create an account</a>:</h5>
            <form class="mx-auto">
                <input class="form-control" type="text" placeholder="Username" required>
                <input class="form-control up-a-bit" type="password" placeholder="Password" required>
                <button type="submit" class="btn btn-md btn-primary mt-1">Login</button>
            </form>
            <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
        </section>
    </main>
</body>
</html>