<?php 
if(!$sock = socket_create(AF_INET,SOCK_STREAM,0)){
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);

    die("Cant Create [$errorCode] $errorMsg \n");
}
echo "Socket made\n";

//binding source address
if(!socket_bind($sock,"192.168.0.20",8080)){
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);

    die("Cant Bind [$errorCode] $errorMsg \n");
}
echo "Socket Bind OK\n";

//listneting
if(!socket_listen($sock,10)){
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);

    die("Cant listen [$errorCode] $errorMsg \n");
}
echo "Listening\n";
echo "Waiting for incoming connections... \n";
$client = socket_accept($sock);
//display information about the client who is connected
if(socket_getpeername($client , $address , $port))
{
    echo "Client $address : $port is now connected\n";
}

$msg = "Ground control to major tom\n";
//sending data
if(!socket_send($client,$msg,strlen($msg),0)){

    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);

    die("Cant Send [$errorCode] $errorMsg \n");
}
echo "DATA SENT\n";

//we are now communicating
//Now receive reply from server
$buff = "didnt get anything";
$len = strlen("for here im sitting in a tin can far above the world\n planet earth is blue\n");
if(socket_recv ( $client , $buff ,$len , MSG_WAITALL ) === FALSE)
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);

    die("Could not receive data: [$errorcode] $errormsg \n");
}

//print the received message
echo $buff;



//closeing off stuff
socket_close($client);
socket_close($sock);
?>
