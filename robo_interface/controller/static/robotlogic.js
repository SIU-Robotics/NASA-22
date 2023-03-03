$(".move_btn").click(move);

function move(information_test) {

    let data = new dataObj();

    data.type = "movement";
    data.direction = information_test.target.id;
    data.speed = document.getElementById("speed_box").value;

    $.ajax({
        url: '/controller/send_command/',
        type: 'POST',
        data: JSON.stringify(data),
        success: successful_response,
        error: error_response,
    });
}

document.addEventListener('keypress', keypressed)

document.onkeydown = keypressed;

function keypressed(event){
    var name = event.key;
    var code = event.code;
    // Alert the key name and key code on keydown
    console.log(`Key pressed ${name} \r\n Key code value: ${code}`);
    console.log("0x" + name.charCodeAt(0).toString(16));

    // $.ajax({
    //     url: '/controller/send_command/',
    //     type: 'POST',
    //     data: JSON.stringify(code),
    //     success: successful_response,
    //     error: error_response,
    // })
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