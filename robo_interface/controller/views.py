import json
from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt


#After review of v.1.2 of chatgpt

def index(request):
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