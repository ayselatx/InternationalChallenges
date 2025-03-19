import serial
import re
import SensorData
import dbContext

class Reader:
    
    def __init__(self):
        self.ser = serial.Serial('COM12', 115200, timeout=1)
        
    def read(self) -> SensorData.SensorData:
        if self.ser.is_open:
            try:
                while(True):
                    data: list = self.ser.readlines()
                    if data:
                        if data[0] == b'Received packet\r\n':
                            data.pop(0)
                            encoded_data = [d.decode("utf-8", errors="ignore") for d in data]
                            print(encoded_data)
                            parsed_data = self.parse_list_to_sensor_data(encoded_data)
                            print(parsed_data)
                            self.ser.reset_input_buffer()
                            return parsed_data
            except Exception as e:
                print("Error reading from serial port: ", e)
                return ""
        else:
            print("Serial port is not open!")
            return ""
    
    def parse_list_to_sensor_data(self, data: list[str]) -> SensorData:
        temperature = re.sub(r"[^\d.-]", "", data[0])
        humidity = re.sub(r"[^\d.-]", "", data[1])
        pressure = re.sub(r"[^\d.-]", "", data[2])
        rssi = re.sub(r"[^\d.-]", "", data[3])
        snr = re.sub(r"[^\d.-]", "", data[4])
        return SensorData.SensorData(temperature, humidity, pressure, rssi, snr)
     
    def close(self):
        self.ser.close()
        
        
if __name__ == "__main__":
    # Instances creation
    reader = Reader()
    dbConn = dbContext.dbContext()
    # Reading data from serial and saving it to db
    while True:
        data: SensorData.SensorData = reader.read()
        dbConn.SaveData(data)