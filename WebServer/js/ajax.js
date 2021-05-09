//generates and sends an ajax request
function AjaxRequest(url, type, data, dataType, successFunction, errorFunction)
{
    //create options
    let ajaxOptions = {};
    ajaxOptions['url'] = url;
    ajaxOptions['type'] = type; //POST/GET
    ajaxOptions['data'] = data; //sendData
    ajaxOptions['dataType'] = dataType; //json, html
    ajaxOptions['success'] = successFunction;
    ajaxOptions['error'] = errorFunction;

    //send ajax
    $.ajax(ajaxOptions);
}