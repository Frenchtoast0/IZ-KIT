<?php 
//creating a socket object that meets the specs in params
if(!$sock = socket_create(AF_INET,SOCK_STREAM,0)){
    /*
        this error code is repeated ALOT
        essentally its like mysqli were you can check the error 
        you get a error code and then you can print it as a stirng
    */
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);
    
    //kills/stops the php
    die("Cant Create [$errorCode] $errorMsg \n");
}
echo "Socket made\n";

//binding source address
//now we are taking our socket obj and "gluing" it to said ip address and port
if(!socket_bind($sock,"192.168.0.20",8080)){
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);
    die("Cant Bind [$errorCode] $errorMsg \n");
}
echo "Socket Bind OK\n";

//listneting
/*
so this sets our bound sock obj to listen for devices that want to connect to it 
the next param is neat, its the total number of connections that will be queded up for later
meaning we can use this to service/quickly go through all deivces that want ot connect
this will most likely require some async tho, more experimentation required
*/
if(!socket_listen($sock,10)){
    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);
    die("Cant listen [$errorCode] $errorMsg \n");
}

echo "Listening\n";
echo "Waiting for incoming connections... \n";

//this accpets a connection found and returns a new socket obj that represnets there connection
$client = socket_accept($sock); //THIS IS A BLOCKING FUNCTION so it will wait here till its done

//display information about the client who is connected
if(socket_getpeername($client , $address , $port))//note these vars are passed by reffrence its wierd but its cool
{
    echo "Client $address : $port is now connected\n";
}

//sending data
$msg = "Ground control to major tom\n";
//number bytes are very precious/need to be watched when doing this ie strlen($msg)
if(!socket_send($client,$msg,strlen($msg),0)){

    $errorCode = socket_last_error();
    $errorMsg = socket_strerror($errorCode);
    die("Cant Send [$errorCode] $errorMsg \n");
}
echo "DATA SENT\n";

//we are now communicating
//Now receive reply from server
$buff = "didnt get anything";
//going back to line 53 we need to make sure we know how many bytes we are getting from the client
$len = strlen("for here im sitting in a tin can far above the world\n planet earth is blue\n");

//this just reads x bytes from connected socket and throws it into $buff
//note from my knowalge there is no way to loop through recivced data untill its empty
if(socket_recv( $client , $buff ,$len , MSG_WAITALL ) === FALSE)
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
    die("Could not receive data: [$errorcode] $errormsg \n");
}

//print the received message
echo $buff;

//closeing off connection with client
socket_close($client);
//closing listner as well, note we could probably go back to line 43 at this point and deal with the next person in que
socket_close($sock);

?>
