$("#light_button").click(toggle_light);

function toggle_light() {

    let status;

    if ($("#radio_on").is(":checked")) {
        status = "on";
    }
    else {
        status = "off";
    }

    $.ajax({
        url: '/controller/toggle_light/',
        type: 'POST',
        data: {"light": status},
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
