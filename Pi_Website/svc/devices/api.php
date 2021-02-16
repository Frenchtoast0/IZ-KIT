<?php
require_once "../rest.api.php";  // include our base abstract class
require_once "../../functions/deviceFunctions.php"; //connect to device functionality

session_start(); //allow reading of session variable

class MyAPI extends API {

  // Since we don't allow CORS, we don't need to check Key Tokens
  // We will ensure that the user has logged in using our SESSION authentication
  // Constructor - use to verify our authentication, uses _response
  public function __construct($request, $origin) {
    parent::__construct($request);

    // Uncomment for authentication verification with your session
    //if (!isset($_SESSION["userID"]))
    //  return $this->_response("Get Lost", 403);
  }

  //register device endpoint
  protected function register(){
    $resp["method"] = $this->method;
    $resp["request"] = $this->request;
    $resp["putfile"] = $this->file;
    $resp["verb"] = $this->verb;
    $resp["args"] = $this->args;

    if ($this->method == "POST")
    {
      $r["data"] = "connected";
      $r["status"] = "success";

      return RegisterDevice($this->request);
    } 
  }

  //receive device state info endpoint
  protected function update(){
    $resp["method"] = $this->method;
    $resp["request"] = $this->request;
    $resp["putfile"] = $this->file;
    $resp["verb"] = $this->verb;
    $resp["args"] = $this->args;

    if ($this->method == "POST")
    {
      return UpdateDevice($this->request);
    } 
  }
}

// Executable API Call
// The actual functionality block here
try {
  // Construct instance of our derived handler here
  $API = new MyAPI($_REQUEST['request'], $_SERVER['HTTP_ORIGIN']);
  // invoke our dynamic method, should find the endpoint requested.
  echo $API->processAPI();
} catch (Exception $e) { // OOPs - Houston, we have a problem
  echo json_encode(Array('error' => $e->getMessage()));
}