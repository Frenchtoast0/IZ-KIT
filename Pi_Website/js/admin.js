$(document).ready(() =>
{
    //initially load the devices
    LoadDevices();

    //setup refresh button
    $("#refresh").click(function(){
        LoadDevices();
    })
});

//tell server to return devices
function LoadDevices()
{
    AjaxRequest("./svc/devices/adminLoad", "GET", {}, "json", DisplayDevices, ErrorHandler);
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
                let check = document.createElement("input");
                check.type = "checkbox";
                
                //set checkbox state
                if (data[i][tag] == 0) check.checked = false;
                else check.checked = true;

                //give it unique id
                check.id = "check" + i;

                $(td).append($(check));
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
        input.prop("id", "value" + i);
        td.append(input);
        td.append(" "); //add spacing between
        let button = $(document.createElement("button"));
        button.html("Save");
        button.prop("id", "button" + i);
        td.append(button);
        tr.append(td);

        table.append(tr);
    }
}