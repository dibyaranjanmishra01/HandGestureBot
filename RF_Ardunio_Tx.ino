#include <VirtualWire.h>
#include <Wire.h>

#define ADDR 0x68

void setup() 
{
  vw_set_tx_pin(12);//set pin 12 as data pin for transmission
  vw_setup(2000);// transmission rate in bits/sec

  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(ADDR);       // Start communication with MPU6050 // ADDR=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true); 
}

void loop()
{
    Wire.beginTransmission(ADDR);
    Wire.write(0x3B); // Start with register 0x3B 
    Wire.endTransmission(false);
    Wire.requestFrom(ADDR, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    float AccX = (Wire.read() << 8 | Wire.read()) / 16384.0*9.8; // X-axis value in Newtons
    float AccY = (Wire.read() << 8 | Wire.read()) / 16384.0*9.8; // Y-axis value in Newtons
    float AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0*9.8; // Z-axis value in Newtons
    
    int pitch = -(atan2(AccX, sqrt(AccY*AccY + AccZ*AccZ))*180.0)/M_PI;
    int roll = (atan2(AccY, AccZ)*180.0)/M_PI;
    
    String output = String(pitch)+","+String(roll); //converting the data in string of form pitch,roll for transmission
    vw_send((uint8_t *)output,strlen(output)); // send data
    vw_wait_tx(); // wait for transmitter to become idle
}
