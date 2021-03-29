$(document).ready(() =>
{
    //set up uploading button
    $("#uploadButton").click(function()
    {
        UploadCode();
    });

    //allow special code help
    $("#code").keydown(function(e)
    {
        CodeHelp(this, e);
    });

});

//makes coding easier
//allows tabbing, easy creation of semicolons, etc.
function CodeHelp(textarea, e)
{
    //tab was pressed
    if (e.keyCode == 9)
    {
        //get caret position (and any selection)
        let start = textarea.selectionStart;
        let end = textarea.selectionEnd;

        //get textarea properties
        let t = $(textarea);
        let v = t.val();

        //value = text before select + tab + text after select
        t.val(
            v.substring(0, start) 
            + "\t"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 1;

        //prevent focus from changing
        e.preventDefault();
    }
    //open semicolon was pressed
    else if (e.keyCode == 219 && e.shiftKey && textarea.selectionStart == textarea.selectionEnd) 
    {
        //get caret position (and any selection)
        let start = textarea.selectionStart;
        let end = textarea.selectionEnd;

        //get textarea properties
        let t = $(textarea);
        let v = t.val();

        //value = text before select + } + text after select
        t.val(
            v.substring(0, start) 
            + "{\r\t\r}"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 3;

        //prevent duplicate opening semicolons
        e.preventDefault();
    }
    //quotes were added
    else if (e.keyCode == 222 && e.shiftKey && textarea.selectionStart == textarea.selectionEnd) 
    {
        //get caret position (and any selection)
        let start = textarea.selectionStart;
        let end = textarea.selectionEnd;

        //get textarea properties
        let t = $(textarea);
        let v = t.val();

        //value = text before select + } + text after select
        t.val(
            v.substring(0, start) 
            + "\"\""
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 1;

        //prevent duplicate opening semicolons
        e.preventDefault();
    }
    //enter pressed and last char is colon or comma
    else if (e.keyCode == 13 && ($(textarea).val()[textarea.selectionStart-1] == ":" || $(textarea).val()[textarea.selectionStart-1] == ",")&& textarea.selectionStart == textarea.selectionEnd) 
    {
        //get caret position (and any selection)
        let start = textarea.selectionStart;
        let end = textarea.selectionEnd;

        //get textarea properties
        let t = $(textarea);
        let v = t.val();

        //value = text before select + } + text after select
        t.val(
            v.substring(0, start) 
            + "\r\t\t"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 3;

        //prevent duplicate opening semicolons
        e.preventDefault();
    }
    //enter pressed and last 2 chars are ## -> special function, creates code outline
    else if (e.keyCode == 13 && ($(textarea).val()[textarea.selectionStart-1] == "#" && $(textarea).val()[textarea.selectionStart-2] == "#")&& textarea.selectionStart == textarea.selectionEnd) 
    {
        //get caret position (and any selection)
        let start = textarea.selectionStart;
        let end = textarea.selectionEnd;

        //get textarea properties
        let t = $(textarea);
        let v = t.val();

        //value = text before select + } + text after select
        t.val(
            v.substring(0, start-2) 
            + "{\r"
            + "\tmeta:\r\t\tname=\"\"\r\tinputs:\r\toutputs:"
            + "\r}"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 15;

        //prevent enter from actually firing
        e.preventDefault();
    }
    //else alert(e.keyCode);
}

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