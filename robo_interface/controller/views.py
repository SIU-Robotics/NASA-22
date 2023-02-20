import json
from django.http import JsonResponse, StreamingHttpResponse
from django.shortcuts import render
from django.views.decorators import gzip
from django.views.decorators.csrf import csrf_exempt
from .logic.i2c import I2CBridge
from .logic.camera import VideoCamera, gen

# Live camera feed view
@gzip.gzip_page
def livefe(request):
    try:
        camera = VideoCamera()
        response = StreamingHttpResponse(gen(camera), content_type="multipart/x-mixed-replace;boundary=frame")
        response['Cache-Control'] = 'no-cache'
        camera.response = response
        camera.start()
    except Exception as e:
        response = JsonResponse({"error": e})
        response.status_code = 500
    return response

# View called by index page using jQuery AJAX
@csrf_exempt
def robot_control(request):
    try:
        # load the json data
        payload = json.loads(request.body.decode())

        robot = I2CBridge()
        robot.move(payload.get("direction"), int(payload.get("speed")))

        response = JsonResponse({"success": "true"})
    except Exception as e:
        print(e)
        response = JsonResponse({"error": str(e)})
        response.status_code = 500

    return response

# WIP diagnostic view
def get_status(request):
    try:
        robot = I2CBridge()
        if(robot.status() == 0):
            response = JsonResponse({"success": "true"})
    except Exception as e:
        print(e)
        response = JsonResponse({"error": str(e)})
        response.status_code = 500
    return response


def index(request):
    return render(request, 'controller/index.html')