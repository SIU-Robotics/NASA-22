from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('test_page/', views.test_page, name='test_page'),
	path('test/', views.test, name='test'),
	path('toggle_light/', views.toggle_light, name='toggle_light'),
	path('video/', views.video_stream, name='video_stream')
]

