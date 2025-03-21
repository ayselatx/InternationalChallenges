from django.db import models

class SensorData(models.Model):
    temperature = models.FloatField()
    humidity = models.FloatField()
    pressure = models.FloatField()
    RSSI = models.FloatField()
    SNR = models.FloatField()
    timestamp = models.DateTimeField(auto_now_add=True)
