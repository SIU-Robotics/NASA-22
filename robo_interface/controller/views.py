import json
from .logic.i2c import I2CBridge
from django.http import JsonResponse, HttpResponse, StreamingHttpResponse
from django.shortcuts import render
from django.views.decorators import gzip
from django.views.decorators.csrf import csrf_exempt
from .logic.camera import VideoCamera, gen


#After review of v.1.2 of chatgpt

@gzip.gzip_page
def livefe(request):
    try:
        camera = VideoCamera()
        response = StreamingHttpResponse(gen(camera), content_type="multipart/x-mixed-replace;boundary=frame")
        print("before start")
        response['Cache-Control'] = 'no-cache'
        camera.response = response
        camera.start()
    except Exception as e:
        print(e)
        response = JsonResponse({"error": "true"})
        response.status_code = 500
    return response

def index(request):
    return render(request, 'controller/index.html')

@csrf_exempt
def robot_control(request):
    try:
        # load the json data
        payload = json.loads(request.body.decode())

        robot = I2CBridge()

        # check which type of command we're dealing with
        if (payload.get("movement") == "true"):
            robot.move(payload.get("direction"), payload.get("speed"))

        elif (payload.get("claw") == "true"):
            robot.grab()

        else:
            raise Exception("Unknown command")

        response = JsonResponse({"success": "true"})
    except Exception as e:
        print(e)
        response = JsonResponse({"error": str(e)})
        response.status_code = 500

    return response


###
# example code for later
#
# @csrf_exempt
# def test(request):
#     try:
#         payload = json.loads(request.body.decode())
#         answer = float(payload.get("n1")) + float(payload.get("n2"))
#         response = JsonResponse({"answer": answer})
#         return response
#     except Exception as e:
#         response = JsonResponse({"error": str(e)})
#         response.status_code = 500
#         return response
###