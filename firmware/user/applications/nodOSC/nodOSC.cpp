// This #include statement was automatically added by the Particle IDE.
#include <simple-OSC.h>
#include "armaFilter.h"
#include "HeadPosition.h"
#include <Adafruit_LSM303_U.h>
#include <Adafruit_Sensor.h>
#include "math.h"


UDP udp;

unsigned int outPort = 7400;


IPAddress outIp(192,168,0,100);

//IPAddress outIp(192,168,1,79);

ArmaFilter armaFilter;
ArmaFilter smoothingFilter;

float smoothDirection = 0.0f;
float heading = 0.0f;

double zeroDirection = 0.0f;

int buttonPin = D3;
int ledPin = D5;
int statusLed = D7;
bool firstLoopFlag = true;

const float Pi = 3.14159;
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void displayAccelSensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayMagSensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  //waitUntil(Particle.connected);
  udp.begin(0);
  armaFilter.setup(300.0f, 400.0f);
  smoothingFilter.setup(100.0f, 200.0f);

  /* Initialise the sensor */
  if((!accel.begin()) || (!mag.begin()))
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  /* Display some basic information on this sensor */
  displayAccelSensorDetails();
  displayMagSensorDetails();

    pinMode( buttonPin , INPUT_PULLUP); // sets pin as input

    pinMode( statusLed , OUTPUT );
    pinMode( ledPin , OUTPUT ); // sets pin as output
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t eventAccel;
  sensors_event_t eventMag;
  accel.getEvent(&eventAccel);
  mag.getEvent(&eventMag);



  double direction = (atan2(eventMag.magnetic.y, eventMag.magnetic.x) * 180.0)/ Pi;
  direction = smoothingFilter.process(float(direction));

    if (direction < 0.0f) {direction += 360.0f;}

   if (firstLoopFlag == true)
  {
      digitalWrite( ledPin, HIGH);
      digitalWrite( statusLed, HIGH);
      zeroDirection = direction;
      firstLoopFlag = false;
  }



//   zeroDirection = armaFilter.process(float(direction));

  //heading = direction - smoothDirection;

  heading = -(zeroDirection - direction);
  if (heading > 180.0f) {heading -= 360.0f;}

   zeroDirection = armaFilter.process(float(direction));

  //int buttonState = digitalRead( buttonPin );
  //float mappedHeading = map(float(heading),0)
  //buffer = String(heading);

  /* Display the results (acceleration is measured in m/s^2) */
 /*
  Particle.variable("accelx",double(eventAccel.acceleration.x));
  delay(100);
  Particle.variable("accely",double(eventAccel.acceleration.y));
  delay(100);
  Particle.variable("accelz",double(eventAccel.acceleration.z));
  delay(100);
  Particle.variable("heading", heading);
  delay(100);
  Particle.publish("heading", String(heading), PRIVATE);
  delay(100);
  */

  //OSCMessage outMessage("/rawHeading");
  //outMessage.addFloat(float(direction));
  //outMessage.send(udp,outIp,outPort);

  //Serial.printf
  Serial.print  ("Direction:       "); Serial.println(float(direction));
  Serial.print  ("Heading:       "); Serial.println(float(heading));
  //Serial.print  ("Zero:       "); Serial.println(float(zeroDirection));

  OSCMessage outMessageCentred("yaw");
  outMessageCentred.addFloat(float(heading));
  outMessageCentred.send(udp,outIp,outPort);

  //OSCMessage outMessageSmooth("/smoothedHeading");
  //outMessageSmooth.addFloat(float(smoothDirection));
  //outMessageSmooth.send(udp,outIp,outPort);

//     if( buttonState == LOW )
//   {
//       zeroDirection = direction;
//     // turn the LED On
//     digitalWrite( ledPin, HIGH);
//   }else{
//     // otherwise
//     // turn the LED Off
//     digitalWrite( ledPin, LOW);

//   }

//  if(Udp.sendPacket(buffer, sizeof(buffer), remoteIP, sendPort) < 0)
//  {
//      Particle.publish("NFG");
//  }
  delay(100);
}
