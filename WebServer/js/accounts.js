$(document).ready(() => {
    GetUsers();
});

//display data into table
function ProcessData(data)
{
    let table = $("#accountsTable").find("tbody");

    table.empty();

    for (let tag in data["data"])
    {
        let tr = $(document.createElement("tr"));

        //td placeholder
        let td = $(document.createElement("td"));

        //setup delete button
        let button = $(document.createElement("button"));
        button.prop("type", "button");
        button.val(data["data"][tag]["ID"]);
        button.html("Delete");
        button.addClass("DeleteBtn btn btn-danger");

        td.append(button);
        tr.append(td);

        for (let innerTag in data["data"][tag])
        {
            td = $(document.createElement("td"));
            td.html(data["data"][tag][innerTag].toString());

            tr.append(td);
        }
        
        table.append(tr);
    };

    //setup delete click handlers
    $(".DeleteBtn").click(function(){
        DeleteUser(this);
    })
}

//get users from db
function GetUsers()
{
    AjaxRequest("./svc/users/manage", "GET", {}, "json", ShowUsers, ErrorHandler);
}

//tell server to delete specified user
function DeleteUser(obj)
{
    let sendData = {};
    sendData["userID"] = $(obj).val();

    AjaxRequest("./svc/users/manage", "POST", sendData, "json", HandleStatus, ErrorHandler);
}

//display users from db
function ShowUsers(ajaxData, ajaxStatus)
{
    if ($("#status").html() != "")
        $("#status").append("<br>");

    $("#status").append("Retrieved: " + ajaxData["status"]);

    ProcessData(ajaxData);
}

//ajax status response handler
function HandleStatus(ajaxData, ajaxStatus)
{
    $("#status").empty();

    //update users
    GetUsers();

    $("#status").append("Update:" + ajaxData["status"]);
}

//generic error handler
function ErrorHandler(requestor, textStatus, errorThrown)
{
    let errorString = `Status: ${textStatus} | Error: ${errorThrown}`;
    
    console.log(errorString);
    $("#status").html(errorString);
}