$(document).ready(() =>
{
    //set up uploading button
    $("#uploadButton").click(function()
    {
        AjaxRequest("./svc/devices/program", "POST", $("#code").val(), "JSON", HandleStatus, ErrorHandler);
    });

});

//ajax status response handler
function HandleStatus(ajaxData, ajaxStatus)
{
    $("#status").html(`${ajaxData["status"]}`);
}

//generic error handler
function ErrorHandler(requestor, textStatus, errorThrown)
{
    let errorString = `Status: ${textStatus} </br> Error: ${errorThrown}`;
    
    console.log(errorString);
    $("#status").html(errorString);
}