//Transmitter Code

#include <MPU6050.h>
#include <L298N.h>
//#include <nRF24L01.h>
//#include <RF24.h>
#include "Wire.h"
#include "MPU6050.h"


const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

//Pin Definition
//right
const unsigned int IN1 = 2;
const unsigned int IN2 = 3;
const unsigned int EN1 = 6;
//left
const unsigned int IN3 = 4;
const unsigned int IN4 = 5;
const unsigned int EN2 = 7;

L298N motor1(EN1, IN1, IN2);
L298N motor2(EN2, IN3, IN4);

int16_t ax, ay, az; // x-axis and y-axis values, for this application z-axis is not needed.
int16_t gx, gy, gz; // these values are not used, just declaring to pass in the function.

const byte Address[6] = "00001";
int Pot_Val_Y = 0, Pot_Val_X = 0, Up_key = 0, Dn_key = 0, Left_key = 0, Right_key = 0;
unsigned char Tx_command = 0, Speed_index = 0, Tx_Enable_Flag = 1, TX_Key_Pressed = 0;
unsigned char gati = 0, disha = 0;
unsigned char Tx_Array[2];
unsigned char Run_Stop_Mode = 0;
unsigned char Received_Command = 0;
unsigned int Run_Stop_Counter = 0;
MPU6050 accelgyro;


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  Wire.begin();
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // we are getting all 6 value from MPU6050 i.e. 3 Accelerometer values and 3 Gyro values viz. ax,ay,az,gx,gy and gz.

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  
  if ((ay <= -4000) || ((ay >= 4000)))
  {
    if ((ax >= -4000) || ((ax <= 4000)))
    {
      if ((ay <= -4000))
      {
        Tx_command = 1;                     // forward
        Speed_index = (ay + 4000) / -2000 + 1; // more the negative value more the speed. ay valu varies from -16384 to +16384 same for ax and others.
        if (Speed_index > 5)
        {
          Speed_index = 5;
        }
      }

      if ((ay >= 4000))
      {
        //Serial.print("D , ");
        Tx_command = 2;                     // Backward
        Speed_index = (ay - 4000) / 2000 + 1; // more the positive value more the speed. ay valu varies from -16384 to +16384 same for ax and others.
        if (Speed_index > 5)
        {
          Speed_index = 5;
        }
      }
    }
    else
    {
      //Serial.print("E , ");
      Tx_command = 0;
      Speed_index = 0;
    }
  }
  else if ((ax <= -4000) || ((ax >= 4000)))
  {
    //Serial.print("F , ");
    if ((ay >= -4000) || ((ay <= 4000)))
    {
      //Serial.print("G , ");
      if ((ax <= -4000))
      {
        //Serial.print("H , ");
        Tx_command = 4;                     // Right
        Speed_index = (ax + 4000) / -2000 + 1; // more the negative value more the speed. ax valu varies from -16384 to +16384 same for ay and others.
        if (Speed_index > 5)
        {
          Speed_index = 5;
        }
      }

      if ((ax >= 4000))
      {
        //Serial.print("I , ");
        Tx_command = 3;                     // Left
        //Speed_index = (ax - 4000) / 2000 + 1; // more the positive value more the speed. ax valu varies from -16384 to +16384 same for ay and others.
        if (Speed_index > 5)
        {
          Speed_index = 5;
        }
      }
    }
    else
    {
      Tx_command = 0;
      Speed_index = 0;
    }
  }
  else
  {
    Tx_command = 0;
    Speed_index = 0;
  }
  Serial.print(Tx_command);
  Serial.print(" , ");
  Received_Command = Tx_command;
 
  motor1.setSpeed(255);
  motor2.setSpeed(255);

  if (distance <= 20.00) {
    analogWrite(11,255);
    motor1.stop();
    motor2.stop();
    delay(500);
    motor1.forward();
    motor2.forward();
    delay(500);
  }
  else {
    analogWrite(11,0);
    if (Run_Stop_Mode == 0) // Stop
    {
      motor1.stop();
      motor2.stop();
      Run_Stop_Counter++;
      if (Run_Stop_Counter >= ((5 - Speed_index) * 100)) // Speed_index = 1 -> Min speed,   5 -> Max Speed.
      {
        Run_Stop_Counter = 0;
        Run_Stop_Mode = 1;
      }
    }
    else if (Run_Stop_Mode == 1) // Run
    {
      Run_Stop_Counter++;
      if (Run_Stop_Counter >= ((Speed_index) * 100)) // Speed_index = 1 -> Min speed,   5 -> Max Speed.
      {
        Run_Stop_Counter = 0;
        Run_Stop_Mode = 0;
      }

      if (Received_Command == 1)           //move forward(all motors rotate in forward direction)
      {
        motor1.forward();
        motor2.forward();
      }
      else if (Received_Command == 2)     //move reverse (all motors rotate in reverse direction)
      {
        motor1.backward();
        motor2.backward();
      }
      else if (Received_Command == 3)     //turn right (left side motors rotate in forward direction, right side motors rotates in backward direction)
      {
        motor1.backward();
        motor2.forward();
      }
      else if (Received_Command == 4)     //turn left (right side motors rotate in forward direction, left side motors rotates in backward direction)
      {
        motor1.forward();
        motor2.backward();
      }
      else if (Received_Command == 0)     //STOP (all motors stop)
      {
        motor1.stop();
        motor2.stop();
      }
      else                                  //STOP (all motors stop) , If any other command is received.
      {
        motor1.stop();
        motor2.stop();

      }
    }

  }


  delay(10);
}
