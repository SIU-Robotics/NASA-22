import json
import threading
# from .i2c.light import turnOn, turnOff
from django.http import JsonResponse, HttpResponse, StreamingHttpResponse
from django.shortcuts import render
from django.views.decorators import gzip
from django.views.decorators.csrf import csrf_exempt
from .camera import *


#After review of v.1.2 of chatgpt

@gzip.gzip_page
def livefe(request):
    try:
        cam = VideoCamera()
        response = StreamingHttpResponse(gen(cam), content_type="multipart/x-mixed-replace;boundary=frame")
        response['Cache-Control'] = 'no-cache'
        t = threading.Thread(target=close_camera, args=(cam,response,))
        t.start()
    except Exception as e:
        with open('static/controller/cam_in_use.png', 'rb') as f:
            image_data = f.read()
        response = HttpResponse(image_data, content_type='image/png')
    return response

def index(request, *args, **kwargs):
    return render(request, 'controller/index.html')

@csrf_exempt
def test(request):
    try:
        payload = json.loads(request.body.decode())
        answer = float(payload.get("n1")) + float(payload.get("n2"))
        response = JsonResponse({"answer": answer})
        return response
    except Exception as e:
        response = JsonResponse({"error": str(e)})
        response.status_code = 500
        return response

# @csrf_exempt
# def toggle_light(request):
#     try:
#         payload = json.loads(request.body.decode())
#         if(payload["light"] == "on"):
#             turnOn()
#         else:
#             turnOff()
#         response = JsonResponse({"success": "true"})
#     except Exception as e:
#         response = JsonResponse({"error": str(e)})
#         response.status_code = 500
#         return response

