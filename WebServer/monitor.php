<?php
    #TODO add refresh page copy admin pannel
    #todo add padding to 
    session_start();
    $expr = "/(?<=PID:\s)\d+/mi";
    $PIDs = array();
    $output = shell_exec('tail /home/izkit/scripts/testing/output.log');
    if (!isset($_SESSION["username"]))
    {
        header("location: login.php");
        die();
    }

    if(isset($_GET['submit']))
    {
       /*
        #clear log.... 
        error_log("made it here");
        preg_match_all($expr,$output,$PIDs);
        error_log(implode(',',$PIDs));
        $PIDs = $PIDs[0][count($PIDs[0])-1];
        error_log($PIDs);
        error_log('kill '.$PIDs);
        //Clearing log
        shell_exec('> /home/izkit/scripts/testing/output.log');
        //killServer
        if($PIDs)
            shell_exec('kill '.$PIDs);
        //running server
        shell_exec('nohup python3 /home/izkit/scripts/testing/Server2.py &');
    */
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
        <pre id="server" class="form-control no-focus-border mt-1 mx-auto" readonly="true" autofocus="true">
            <?php
             echo "\n$output";
            ?>
        </pre>
<!--
        <form method="get">
            <input  type="submit" name="submit" value="Restart Server">
        </form>
-->
        <a href="./index.php">Back</a>

        <p class="text-muted mt-3">&copy; IZ-Kit 2021</p>
    </section>
</body>

</html>