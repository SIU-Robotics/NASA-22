from django.urls import path

from . import views

urlpatterns = [
	path('', views.index, name='index'),
	path('camera/<int:index>/', views.live_feed, name='live_camera'),
]

