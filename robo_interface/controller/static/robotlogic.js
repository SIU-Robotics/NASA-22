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
    if (event.keyCode === keys.e) {
        send_command("movement", "stop");
        moving = false;
    }
    if (moving != event.keyCode) {
        if (event.keyCode === keys.d) {
            send_command("movement", "right");
            moving = event.keyCode;
        }
        else if (event.keyCode === keys.a) {
            send_command("movement", "left");
            moving = event.keyCode;
        }
        else if (event.keyCode === keys.s) {
            send_command("movement", "backward");
            moving = event.keyCode;
        }
        else if (event.keyCode === keys.w) {
            send_command("movement", "forward");
            moving = event.keyCode;
        }
    }
    if (auger != event.keyCode) {
        if (event.keyCode === keys.t) {
            send_command("auger", "clockwise");
            auger = event.keyCode;
        }
        else if (event.keyCode === keys.g) {
            send_command("auger", "counterclockwise")
            auger = event.keyCode;
        }
        else if (event.keyCode === keys.y) {
            send_command("auger", "forward")
            auger = event.keyCode;
        }
        else if (event.keyCode === keys.h) {
            send_command("auger", "backward")
            auger = event.keyCode;
        }
        else if (event.keyCode === keys.b) {
            send_command("auger", "stopspin")
            auger = event.keyCode;
            
        }
        else if (event.keyCode === keys.n) {
            send_command("auger", "stopmove")
            auger = event.keyCode;
        }
    }
    if (tilt != event.keyCode) {
        if (event.keyCode === keys.i) {
            send_command("tilt", "bodyforward");
            tilt = event.keyCode;
        }
        else if (event.keyCode === keys.k) {
            send_command("tilt", "bodybackward");
            tilt = event.keyCode;
        }
        else if (event.keyCode === keys.o) {
            send_command("tilt", "augerforward");
            tilt = event.keyCode;
        }
        else if (event.keyCode === keys.l) {
            send_command("tilt", "augerbackward");
            tilt = event.keyCode;
        }
        else if (event.keyCode === keys.comma) {
            send_command("tilt", "bodystop");
            tilt = event.keyCode;
        }
        else if (event.keyCode === keys.period) {
            send_command("tilt", "augerstop");
            tilt = event.keyCode;
        }
    }
    if (auto != event.keyCode) {
        if (event.keyCode === keys.five) {
            send_command("auto", "enabledrive");
            auto = event.keyCode;
        }
        else if (event.keyCode === keys.six) {
            send_command("auto", "disabledrive");
            auto = event.keyCode;
        }
        else if (event.keyCode === keys.nine) {
            send_command("auto", "enabledig");
            auto = event.keyCode;
        }
        else if (event.keyCode === keys.zero) {
            send_command("auto", "disabledig");
            auto = event.keyCode;
        }
    }
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
