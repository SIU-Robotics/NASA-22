from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/', views.livefe, name='live_camera'),
	path('toggle_light/', views.toggle_light, name='toggle_light'),
	path('test/', views.test, name='test'),
	path('test_page/', views.test_page, name='test_page')
]

