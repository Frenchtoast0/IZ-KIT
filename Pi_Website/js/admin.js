$(document).ready(() =>
{
    //initially load the devices
    LoadDevices();

    //setup refresh button
    $("#refresh").click(function(){
        $("#status").html("");
        LoadDevices();
    })

    $("#deleteButton").click(function()
    {
        ClearPrograms();
    });
});

//tell server to return devices
function LoadDevices()
{
    AjaxRequest("./svc/devices/adminLoad", "GET", {}, "json", DisplayDevices, ErrorHandler);
}

//delete all programs in db
function ClearPrograms()
{
    AjaxRequest("./svc/devices/deleteCircuits", "DELETE", {}, "json", DisplayStatus, ErrorHandler);
}

//generic error handler
function ErrorHandler(requestor, textStatus, errorThrown)
{
    let errorString = `Status: ${textStatus} </br> Error: ${errorThrown}`;
    
    console.log(errorString);
    $("#status").html(errorString);
}

//add devices to table
function DisplayDevices(data)
{
    let table = $("#deviceTable").find("tbody");

    table.empty();

    //loop through all rows
    for (let i = 0; i < data.length; i++)
    {
        let tr = $(document.createElement("tr")); //row holder

        //add php given fields
        for (let tag in data[i])
        {
            let td = $(document.createElement("td")); //data holder

            //special case for admin check
            if (tag == "Admin")
            {
                let check = $(document.createElement("input"));
                check.prop("type", "checkbox");
                
                //set checkbox state
                if (data[i][tag] == 0) check.prop("checked", false);
                else check.prop("checked", true);

                //give it unique id
                check.prop("id", "check_" + data[i]["ID"]);

                //set up check events
                check.click(function()
                {
                    Checked(this);
                });

                $(td).append(check);
            }
            else if (tag == "IO")
            {
                if (data[i][tag] == 1) td.html("INPUT");
                else td.html("OUTPUT");
            }
            else
            {
                td.html(data[i][tag]);
            }

            tr.append(td);
        }
        
        //add change value stuff
        let td = $(document.createElement("td"));
        let input = $(document.createElement("input"));
        input.prop("type", "text");
        input.prop("id", "value_" + data[i]["ID"]);
        td.append(input);
        td.append(" "); //add spacing between
        let button = $(document.createElement("button"));
        button.html("Save");
        button.prop("id", "button_" + data[i]["ID"]);
        button.click(function()
        {
            StateChange(this);
        });
        td.append(button);
        tr.append(td);

        table.append(tr);
    }
}

//a checkbox was changed
function Checked(checkbox)
{
    let sendData = {};
    sendData["ID"] = checkbox.id.replace("check_", "");
    
    //determine checked value
    if (checkbox.checked) sendData["checked"] = "ON";
    else sendData["checked"] = "OFF";

    AjaxRequest("./svc/devices/adminLock", "POST", sendData, "json", DisplayStatus, ErrorHandler);
}

//button was pressed to change state
function StateChange(button)
{
    let id = button.id.replace("button_", "");
    let val = $("#value_" + id).val();
    
    //invalid state
    if (val.length < 1)
    {
        $("#status").html(`Error: state of ${id} can't be nothing`);
        return;
    }

    let sendData = {};
    sendData["ID"] = id;
    sendData["value"] = val;

    AjaxRequest("./svc/devices/adminStateChange", "POST", sendData, "json", DisplayStatus, ErrorHandler);
}

//give a status message
function DisplayStatus(ajaxData, ajaxStatus)
{
    $("#status").html(ajaxData["status"]);

    //refresh device table
    LoadDevices();
}