from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/', views.live_feed_1, name='live_camera_1'),
	path('rear_camera/', views.live_feed_2, name='live_camera_2'),
	path('send_command/', views.robot_control, name='control_robot'),
]

