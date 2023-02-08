from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/', views.livefe, name='live_camera')
]

