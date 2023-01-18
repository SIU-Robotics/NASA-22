from django.urls import path

from . import views

urlpatterns = [
	path('test_page/', views.test_page, name='test_page'),
	path('test/', views.test, name='test'),
	path('toggle_light/', views.toggle_light, name='toggle_light'),
]

