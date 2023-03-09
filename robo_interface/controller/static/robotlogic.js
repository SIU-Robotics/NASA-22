$(".move_btn").click(move);

document.addEventListener("keydown", keyDownHandler, false);
document.addEventListener("keyup", keyUpHandler, false);

const keys = { left: 37, up: 38, right: 39, down: 40 };

let rightPressed = false;
let leftPressed = false;
let upPressed = false;
let downPressed = false;
let moving = false;

function keyDownHandler(event) {
    if(moving) return;
    if (event.keyCode === keys.right) {
        move("right");
        console.log("MOVE RIGHT");
        moving = true;
    } else if (event.keyCode === keys.left) {
        move("left");
        console.log("MOVE LEFT");
        moving = true;
    }
    if (event.keyCode === keys.down) {
        move("backward");
        console.log("MOVE BACK");
        moving = true;
    } else if (event.keyCode === keys.up) {
        move("forward");
        console.log("MOVE FORWARD");
        moving = true;
    }
}

function keyUpHandler(event) {
    if ([37, 38, 39, 40].includes(event.keyCode)) {
        move("stop");
        console.log("STOP")
        moving = false;
    }
}
  
  
function move(command) {

    let data = new dataObj();

    data.type = "movement";
    data.direction = command;
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