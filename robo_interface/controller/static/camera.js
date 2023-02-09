let enabled = false;

$("#camera_btn").click(open_camera);

function open_camera() {
    if (enabled) {
        location.reload()
    }
    else {
        enabled = true;
        document.getElementById("video").innerHTML = "<img id='camera_img' src='/controller/camera/' alt='Camera cannot be displayed (in use?)'>"
    }

}