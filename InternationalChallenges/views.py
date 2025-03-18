from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from .models import SensorData
from .serializers import SensorDataSerializer
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView
from django.urls import path
from django.http import JsonResponse
import requests

def get_jwt_token(request):
    url = "http://127.0.0.1:8000/api/token/"
    data = {
        "username": "user",
        "password": "password"
    }
    response = requests.post(url, json=data)
    
    if response.status_code == 200:
        return JsonResponse(response.json())  # Return tokens to frontend
    else:
        return JsonResponse({"error": "Invalid credentials"}, status=400)


@api_view(['GET'])
@permission_classes([IsAuthenticated])  # ✅ Require authentication
def protected_view(request):
    return Response({"message": "You have access to this API!"})


@api_view(['POST'])
def receive_sensor_data(request):
    serializer = SensorDataSerializer(data=request.data)
    if serializer.is_valid():
        serializer.save()
        return Response({"message": "Data saved successfully"}, status=201)
    return Response(serializer.errors, status=400)


urlpatterns = [
    path('api/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),  # Login to get access & refresh token
    path('api/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),  # Refresh token
]
