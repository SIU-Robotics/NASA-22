$("#move_btn").click(move);

function move() {

    let data = new dataObj()

    data.type = "movement";
    data.direction = "forward";
    data.speed = 100;

    $.ajax({
        url: '/controller/send_command/',
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
    this.type;
    this.speed;
}