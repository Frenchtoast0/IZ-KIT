$(document).ready(() =>
{
    AjaxRequest("./svc/devices/adminLoad", "GET", {}, "json", LoadDevices, ErrorHandler);
});

function LoadDevices()
{

}