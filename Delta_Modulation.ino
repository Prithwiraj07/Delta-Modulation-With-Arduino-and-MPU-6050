#include <MPU6050.h>
#include <Wire.h>
#include <I2Cdev.h>
int delta=0,count_outside=0, count_inside=0;
int prev_val=0,curr_val=0;

MPU6050 mpu;
int16_t ax,ay,az;
int16_t gx,gy,gz;
int val1=0,val2=0,val3=2;
int preVal1,preVal2,gyro_error=0;
float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];
float Gyro_raw_error_x, Gyro_raw_error_y;
int16_t Gyr_rawX, Gyr_rawY, Gyr_rawZ;
float Gyro_angle_x, Gyro_angle_y;
float elapsedTime,timePrev;
int i;
float rad_to_deg = 180/3.141592654;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "Connected" : "Not Connected");
  
  if(gyro_error==0)
  {
    for(int i=0; i<200; i++)
    {
      mpu.getMotion6(&ax , &ay, &az, &gx, &gy, &gz);
   
      /*---X---*/
      Gyro_raw_error_x = Gyro_raw_error_x + (gx/131.0); 
      /*---Y---*/
      Gyro_raw_error_y = Gyro_raw_error_y + (gy/131.0);
      if(i==199)
      {
        Gyro_raw_error_x = Gyro_raw_error_x/200;
        Gyro_raw_error_y = Gyro_raw_error_y/200;
        gyro_error=1;
      }
    }
  }
}

void loop() {
  mpu.getMotion6(&ax , &ay, &az, &gx, &gy, &gz);
  curr_val=map(ax,-17000,17000,0,8000);
  Serial.println("Current_Value: ");
  Serial.println(curr_val);
  
  if(delta<curr_val&&(count_outside-count_inside)>5){
    delta=delta+100;
    count_inside=count_outside;
    prev_val=curr_val;
    }

  if(delta>curr_val&&(count_outside-count_inside)>5){
    delta=delta-100;
    count_inside=count_outside;
    prev_val=curr_val;
    }
    Serial.print("Delta: ");
    Serial.println(delta);
  
  count_outside++;
}
