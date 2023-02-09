$("#light_button").click(toggle_light);

function toggle_light() {

    let data = new dataObj();

    if ($("#radio_on").is(":checked")) {
        data.status = "on";
    }
    else {
        data.status = "off";
    }

    $.ajax({
        url: '/controller/toggle_light/',
        type: 'POST',
        data: JSON.stringify(data),
        success: successful_response,
        error: error_response,
    });
}

function successful_response(data) {
    alert("Successfully changed the state of the light.");
}

function error_response(error_json) {
    alert("Error:" + error_json.responseJSON.error);
}

function dataObj() {
    this.status;
}