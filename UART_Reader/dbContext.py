import sqlite3
import SensorData

class dbContext:
    def __init__(self):
        self.conn = sqlite3.connect('sensorData.db')
        self.cursor = self.conn.cursor()

    def query(self, query):
        self.cursor.execute(query)
        return self.cursor.fetchall()

    def execute(self, query):
        self.cursor.execute(query)
        self.conn.commit()

    def close(self):
        self.conn.close()
        
    def SaveData(self, data: SensorData.SensorData):
        query = f"INSERT INTO SensorData (Temperature, Humidity, Pressure, RSSI, SNR) VALUES ({data.temperature}, {data.humidity}, {data.pressure}, {data.rssi}, {data.snr})"
        self.execute(query)