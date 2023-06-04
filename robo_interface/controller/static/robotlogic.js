document.addEventListener("keydown", keyDownHandler, false);

const keys = { w:87, e:69, t:84, y:89, i:73, o:79, a:65, s:83, d:68, g:71, h:72, k:75, l:76, b:66, n:78, comma:188, period:190, five:53, six:54, nine:57, zero:48 };

let rightPressed = false;
let leftPressed = false;
let upPressed = false;
let downPressed = false;
let moving = 0;
let auger = 0;
let tilt = 0;
let auto = 0;
let count = 0;

function keyDownHandler(event) {
    switch(event.keyCode) {
        case keys.d:
            send_command("movement", "right");
            break;
        case keys.a:
            send_command("movement", "left");
            break;
        case keys.s:
            send_command("movement", "backward");
            break;
        case keys.w:
            send_command("movement", "forward");
            break;
        case keys.t:
            send_command("auger", "clockwise");
            break;
        case keys.g:
            send_command("auger", "counterclockwise");
            break;
        case keys.y:
            send_command("auger", "forward");
            break;
        case keys.h:
            send_command("auger", "backward");
            break;
        case keys.b:
            send_command("auger", "stopspin");
            break;
        case keys.n:
            send_command("auger", "stopmove")
            break;
        case keys.i:
            send_command("tilt", "bodyforward");
            break;
        case keys.k:
            send_command("tilt", "bodybackward");
            break;
        case keys.o:
            send_command("tilt", "augerforward");
            break;
        case keys.l:
            send_command("tilt", "augerbackward");
            break;
        case keys.comma:
            send_command("tilt", "bodystop");
            break;
        case keys.period:
            send_command("tilt", "augerstop");
            break;
        default:
            break;

    }
    //if (auto != event.keyCode) {
    //    if (event.keyCode === keys.five) {
    //        send_command("auto", "enabledrive");
    //        auto = event.keyCode;
    //    }
    //    else if (event.keyCode === keys.six) {
    //        send_command("auto", "disabledrive");
    //        auto = event.keyCode;
    //    }
    //    else if (event.keyCode === keys.nine) {
    //        send_command("auto", "enabledig");
    //        auto = event.keyCode;
    //    }
    //    else if (event.keyCode === keys.zero) {
    //        send_command("auto", "disabledig");
    //        auto = event.keyCode;
    //    }
    //}
}
  
function send_command(type, command) {

    let data = new dataObj();

    data.number = ++count;
    data.type = type;
    data.command = command;
    if (type == "movement") {
        data.speed = document.getElementById("speed").value;
    }

    let newRow = $('<tr>').append(
        $('<td>').text(count),
        $('<td>').text(type),
        $('<td>').text(command),
        $('<td>').text('Pending')
    );
      
    $('#commands tbody').append(newRow);

    let table = document.getElementById("table_container");
    table.scrollTop = table.scrollHeight;

    $.ajax({
        url: '/controller/send_command/',
        type: 'POST',
        data: JSON.stringify(data),
        success: successful_response,
        error: error_response,
    });
}

function successful_response(response) {
    let status = "Executed";
    let number = response.number;

    let matchingRow = $('#commands tbody tr').filter(function() {
      return $(this).find('td:first-child').text() == number;
    });
    matchingRow.find('td:last-child').text(status);
}

function error_response(response) {
    let status = response.responseJSON.error;
    let number = response.responseJSON.number;

    let matchingRow = $('#commands tbody tr').filter(function() {
      return $(this).find('td:first-child').text() == number;
    });
    matchingRow.find('td:last-child').text(status);
}

function dataObj() {
    this.type;
    this.speed;
}