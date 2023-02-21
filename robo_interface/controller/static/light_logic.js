$(".move_btn").click(move);

function move(information_test) {

    let data = new dataObj();

    data.type = "movement";
    data.direction = information_test.target.id;
    data.speed = document.getElementById("speed");

    $.ajax({
        url: '/controller/send_command/',
        type: 'POST',
        data: JSON.stringify(data),
        success: successful_response,
        error: error_response,
    });
}

function successful_response(data) {
    
}

function error_response(error_json) {
    alert("Error:" + error_json.responseJSON.error);
}

function dataObj() {
    this.type;
    this.speed;
}