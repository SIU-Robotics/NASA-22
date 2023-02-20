from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/', views.live_feed, name='live_camera'),
	path('send_command/', views.robot_control, name='control_robot'),
]

