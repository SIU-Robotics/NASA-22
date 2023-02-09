from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/', views.livefe, name='live_camera'),
	path('send_command/', views.robot_control, name='control_robot'),
	# path('test/', views.test, name='test'),
	# path('test_page/', views.test_page, name='test_page')
]

