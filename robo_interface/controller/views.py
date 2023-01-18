import json
from .i2c.light import turnOn, turnOff
from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt


#After review of v.1.2 of chatgpt

def index(request):
    return render(request, 'controller/index.html')

def test_page(request):
    return render(request, 'controller/test_page.html')

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