$("#camera_btn").click(open_camera);

function open_camera() {

    document.getElementById("camera_btn").outerHTML = "<img src='/controller/camera/'>"

}