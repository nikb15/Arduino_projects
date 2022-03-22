#include  <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(5, 6); // RX | TX

int current_state=100;
int new_state=100;
Adafruit_MPU6050 mpu;
double curr_x=0;
double curr_y=0;
void setup(void) {
  Serial.begin(115200);
  BTserial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /*1 = right
   * 2= left
   * 3 =up
   * 4 =down 
   */
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  Serial.println("");
  delay(100);

  

  if(a.acceleration.y>4.25  && a.acceleration.y<8.50  )
  {
      //Changes to right 
      current_state= 1;
      if(new_state!=current_state)
      {
                new_state=current_state;
                Serial.println("** CHAINGE IN THE STATE : 1");
                Serial.println("** Turring right");
                delay(100);
      }
  }
  else if(a.acceleration.y<-4.0 && a.acceleration.y>-9.50   )
  {
      //Changes to right 
      current_state= 2;
      if(new_state!=current_state)
      {
                new_state=current_state;
                Serial.println("** CHAINGE IN THE STATE : 2");
                Serial.println("** Turring left");
                delay(100);
      }
  }

  else if(a.acceleration.x<-5.00 && a.acceleration.x>-9.00  )
  {
      //Changes to right 
      current_state= 4;
      if(new_state!=current_state)
      {
                new_state=current_state;
                Serial.println("** CHAINGE IN THE STATE : 4");
                Serial.println("** Turring down");
                delay(100); 
      }
  }

  else if(a.acceleration.x<4.50&&a.acceleration.x>-1.75  )
  {
      //Changes to right 
      current_state= 3;
      if(new_state!=current_state)
      {
                new_state=current_state;
                Serial.println("** CHAINGE IN THE STATE : 3");
                Serial.println("** Turring up");
                delay(100);
      }
  }

  BTserial.write(new_state);
}

//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
