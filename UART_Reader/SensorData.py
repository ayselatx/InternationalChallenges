class SensorData:
    def __init__(self, temperature, humidity, pressure, rssi, snr):
        self.temperature = temperature
        self.humidity = humidity
        self.pressure = pressure
        self.rssi = rssi
        self.snr = snr

    def __repr__(self):
        return f"SensorData(Temperature={self.temperature}, Humidity={self.humidity}, Pressure={self.pressure}, RSSI={self.rssi}, SNR={self.snr})"
