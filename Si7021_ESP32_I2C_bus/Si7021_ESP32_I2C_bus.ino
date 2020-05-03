#include <Wire.h>

const int ADDR = 0x40;
const int COMM = 0xE3;
int X0,X1,Y0,Y1,Y2,Y3;
double X,Y,X_out,Y_out1,Y_out2;

TwoWire I2Cone = TwoWire(0);
//TwoWire I2Ctwo = TwoWire(1);

void setup() 
{
  I2Cone.begin(21,22,100000); // SDA pin 21, SCL pin 22, 100kHz frequency
  //I2Ctwo.begin(16,17,400000);  SDA pin 16, SCL pin 17, 400kHz frequency
}

void loop() 
{

  I2Cone.beginTransmission(ADDR);
  I2Cone.write(COMM);
  I2Cone.endTransmission();
  /**Read data of temperature**/
  I2Cone.requestFrom(ADDR,2);
  if(I2Cone.available()<=2);{
    X0 = I2Cone.read();
    X1 = I2Cone.read();
    X0 = X0<<8;
    X_out = X0+X1;
  }
 
  /**Calculate and display temperature**/
  X=(175.72*X_out)/65536;
  X=X-46.85;
  Serial.print(X);
  Serial.print("C");
  Serial.print("\t");
}
