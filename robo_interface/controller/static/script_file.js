$("#test_button").click(send_data);

function send_data() {

    let num_obj = new NumberObject();

    num_obj.n1 = document.getElementById("val1").value;
    num_obj.n2 = document.getElementById("val2").value;

    $.ajax({
        url: '/controller/test/',
        type: 'POST',
        data: JSON.stringify(num_obj),
        success: successful_response,
        error: error_response,
    });
}

function successful_response(data) {
    $("#answer").html(data.answer);
}

function error_response(error_json) {
    alert(error_json.responseJSON.error);
}

function NumberObject() {
    this.n1 = 0;
    this.n2 = 0;
}