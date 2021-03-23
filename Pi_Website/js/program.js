$(document).ready(() =>
{
    //set up uploading button
    $("#uploadButton").click(function()
    {
        UploadCode();
    });

});

//ajax status response handler
function HandleStatus(ajaxData, ajaxStatus)
{
    $("#status").html(`${ajaxData["data"]}`);
}

//generic error handler
function ErrorHandler(requestor, textStatus, errorThrown)
{
    let errorString = `Status: ${textStatus} </br> Error: ${errorThrown}`;
    
    console.log(errorString);
    $("#status").html(errorString);
}

//parses and uploads code file
function UploadCode()
{
    let data = {}; //data to ajax to server

    let code = $("#code").val();

    //remove whitespace
    code = code.replace(/[\n \t\r]/mg, "");

    /*
    Note, will need to account for multiple wires
    */

    //get circuit name
    data["Name"] = code.match(/(?<=name=")[a-z0-9]*/gmi)[0];

    //get inputs/outputs
    let inputList = code.match(/(?<=inputs:)[a-z*\-0-9="<>,]*(?=outputs)/gmi);
    let outputList = code.match(/(?<=outputs:)[a-z*\-0-9="<>,]*(?=})/gmi);

    //break apart input strings
    data["Inputs"] = [];
    let inputs = inputList[0].split(",");
    for (let i = 0; i < inputs.length; i++)
    {
        let it = {};
        it["ID"] = inputs[i].match(/[a-z\-0-9]*(?=[<=>][<=>])/gmi)[0];
        it["Sign"] = inputs[i].match(/[=><]=/gmi)[0];

        if (it["Sign"] == "<=") it["Sign"] = "\<=";

        it["Value"] = inputs[i].match(/(?<=")[a-z0-9]*(?=")/gmi)[0];

        data["Inputs"].push(it);
    }
    

    //break apart output strings
    data["Outputs"] = [];
    let outputs = outputList[0].split(",");
    for (let i = 0; i < outputs.length; i++)
    {
        let o = {};
        o["ID"] = outputs[i].match(/[a-z\-0-9]*(?==)/gmi)[0];
        o["Value"] = outputs[i].match(/(?<=")[a-z0-9]*(?=")/gmi)[0];

        data["Outputs"].push(o);
    }

    //send code away
    AjaxRequest("./svc/devices/program", "POST", data, "json", HandleStatus, ErrorHandler);
}