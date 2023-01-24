import json
import subprocess
from .i2c.light import turnOn, turnOff
from django.http import JsonResponse, HttpResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt


#After review of v.1.2 of chatgpt

def index(request):
    video_url = "video/"
    return render(request, 'controller/index.html', {'video_url': video_url})

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

@csrf_exempt
def toggle_light(request):
    try:
        payload = json.loads(request.body.decode())
        if(payload["light"] == "on"):
            turnOn()
        else:
            turnOff()
        response = JsonResponse({"success": "true"})
    except Exception as e:
        response = JsonResponse({"error": str(e)})
        response.status_code = 500
        return response

def video_stream(request):
    pipeline = subprocess.Popen(["gst-launch-1.0", "udpsrc", "port=9000", "caps='application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264'", "!", "rtph264depay", "!", "avdec_h264", "!", "videoconvert", "!", "xvimagesink"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    response = HttpResponse(pipeline.stdout, content_type='multipart/x-mixed-replace; boundary=frame')
    return response
