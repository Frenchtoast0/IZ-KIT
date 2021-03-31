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

    //enable saving and uploading code files
    $("#saveButton").click(function()
    {
        SaveFile($("#code").val());
    });
    $("#loadButton").click(function()
    {
        LoadFile();
    });

});

//saves code file to user's folder
function SaveFile(code)
{
    let sendData = {};
    sendData["code"] = code;

    //tell server to save
    AjaxRequest("./svc/users/saveProgram", "POST", sendData, "json", HandleStatus, ErrorHandler);
}

//load's user's previously saved file
function LoadFile()
{
    AjaxRequest("./svc/users/loadProgram", "GET", {}, "json", AddCode, ErrorHandler);
}

//changes code in code box
function AddCode(ajaxData, ajaxStatus)
{
    if (ajaxData["code"] != "") $("#code").val(ajaxData["code"]);
    $("#status").html(ajaxData["status"]);
}

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
            + "    "
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 4;

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
            + "{\r    \r}"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 6;

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
            + "\r        "
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 9;

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
            + "    meta:\r        name=\"\"\r    inputs:\r    outputs:"
            + "\r}"
            + v.substring(end)
        );

        //move caret to correct position
        textarea.selectionStart = textarea.selectionEnd = start + 24;

        //prevent enter from actually firing
        e.preventDefault();
    }
    //else alert(e.keyCode);
}

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

//parses and uploads code file
function UploadCode()
{
    let code = $("#code").val();

    //check if a wire was added
    if (code.length < 1)
    {
        $("#status").html("Error: empty code file");
        return;
    }

    //remove whitespace
    code = code.replace(/[\n \t\r]/gm, "");

    //split code into multiple wires
    wires = code.match(/{[^}]*}/gm);

    //check if a wire was added
    if (wires == null || wires.length < 1)
    {
        $("#status").html("Error: no circuits in code");
        return;
    }

    //loop through wires
    for (let i = 0; i < wires.length; i++)
    {
        let data = {}; //data to ajax to server

        try{
            //get circuit name
            data["Name"] = wires[i].match(/(?<=name=")[a-z0-9]*/gmi)[0];

            //get inputs/outputs
            let inputList = wires[i].match(/(?<=inputs:)[a-z*\-0-9="<>,]*(?=outputs)/gmi);
            let outputList = wires[i].match(/(?<=outputs:)[a-z*\-0-9="<>,]*(?=})/gmi);

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
        }
        catch (error)
        {
            //code failed parsing
            $("#status").html("Error: code failed parsing");
            return;
        }

        //send code away
        AjaxRequest("./svc/devices/program", "POST", data, "json", HandleStatus, ErrorHandler);
    } 
}