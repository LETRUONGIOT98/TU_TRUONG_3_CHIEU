#include <Wire.h>

// MLX90393 I2C Address is 0x0C(12)
#define Addr 0x0C

void setup() 
{
  // Initialise I2C communication as MASTER 
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(57600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Write register command
  Wire.write(0x60);
  // Set AH = 0x00, BIST disabled
  Wire.write(0x00);
  // Set AL = 0x5C, Hall plate spinning rate = DEFAULT, GAIN_SEL = 5  
  Wire.write(0x5C);
  // Select address register, (0x00 << 2)
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read status byte (nếu cần)
  if(Wire.available() == 1) 
  {
    unsigned int c = Wire.read();
  }

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Write register command
  Wire.write(0x60);
  // Set AH = 0x02
  Wire.write(0x02);
  // Set AL = 0xB4, RES for magnetic measurement = 0
  Wire.write(0xB4);
  // Select address register, (0x02 << 2)
  Wire.write(0x08);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read status byte (nếu cần)
  if(Wire.available() == 1) 
  {
    unsigned int c = Wire.read();
  }
  delay(300);
}

void loop() 
{
  unsigned int data[7];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Start single measurement mode, ZYX enabled
  Wire.write(0x3E);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read status byte
  if(Wire.available() == 1) 
  {
    unsigned int c = Wire.read();
  }
  delay(100);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send read measurement command, ZYX enabled
  Wire.write(0x4E);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 7 bytes of data
  Wire.requestFrom(Addr, 7);
  // Read 7 bytes of data
  // status, xMag msb, xMag lsb, yMag msb, yMag lsb, zMag msb, zMag lsb
  if (Wire.available() == 7) // Xóa dấu ";" ở đây
  {
    for (int i = 0; i < 7; i++) {
      data[i] = Wire.read();
    }
  }

  // Convert the data
  int xMag = (data[1] << 8) | data[2];  // Chuyển đổi từ hai byte
  int yMag = (data[3] << 8) | data[4];  // Chuyển đổi từ hai byte
  int zMag = (data[5] << 8) | data[6];  // Chuyển đổi từ hai byte

  // Xuất dữ liệu ra Serial Monitor
  Serial.print(xMag);
  Serial.print(",");
  Serial.print(yMag);
  Serial.print(",");
  Serial.println(zMag);
  
  delay(100); // Đọc lại sau mỗi 500ms
}
