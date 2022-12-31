//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <ESP32Servo.h>
Servo servo1;
Servo servo2;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

int minUs = 1000;
int maxUs = 2000;
int servo1Pin = 34;
int servo2Pin = 35;
BluetoothSerial SerialBT;
const int ENA = 14;  // 16 corresponds to GPIO16
const int ENB = 27;
// setting PWM properties
const int freq = 5000;
const int PWM_1 = 0;
const int resolution = 8;

const int freq2 = 5000;
const int PWM_2 = 2;
const int resolution2 = 8;
char blue;     // là vùng nhớ để so sánh kí tự trả về từ app.
int spd = 255;
TaskHandle_t Task1;
TaskHandle_t Task2;
#define IN1 26
#define IN2 25
#define IN3 33
#define IN4 32
ESP32PWM pwm;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("MEKHANE"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  servo1.setPeriodHertz(50);      // Standard 50hz servo
  servo2.setPeriodHertz(50);      // Standard 50hz servo
  servo3.setPeriodHertz(330);      // Standard 50hz servo
  servo4.setPeriodHertz(200);      // Standard 50hz servo
  ledcSetup(PWM_1, freq, resolution);
  ledcSetup(PWM_2, freq2, resolution2);
  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
#if defined(ARDUINO_ESP32S2_DEV)
  pwm.attachPin(37, 10000);//10khz
#else
  pwm.attachPin(27, 10000);//10khz
#endif
  servo3.attach(servo3Pin, minUs, maxUs);
  servo4.attach(servo4Pin, minUs, maxUs);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, PWM_1);
  ledcAttachPin(ENB, PWM_2);
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(100);

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    5000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(100);
}
void Task1code( void * pvParameters ) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    core_2();
  }
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ) {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    core_1();
  }

}

void loop() {

}
void core_1()
{

  switch (blue)
  {
    case ('0'):
      spd = 100;
    case ('1'):
      spd = 120;
      break;
    case ('2'):
      spd = 140;
      break;
    case ('3'):
      spd = 160;
      break;
    case ('4'):
      spd = 180;
      break;
    case ('5'):
      spd = 190;
      break;
    case ('6'):
      spd = 210;
      break;
    case ('7'):
      spd = 220;
      break;
    case ('8'):
      spd = 240;
      break;
    case ('9'):
      spd = 255;
      break;
    case ('S'):
      dung();
      break;
    case ('F'):
      tien();
      break;
    case ('B'):
      lui();
      break;
    case ('L'):
      trai();
      break;
    case ('R'):
      phai();
      break;
  }
  Serial.println("gia tri cua spd");
  Serial.println(spd);
}
void core_2()
{
  if (SerialBT.available()) {
    blue = SerialBT.read();
    Serial.println("gia tri cua blue la   ");
    Serial.println(blue);
  }
  delay(20);
}
void tien()
{
  Serial.println("tien");
  ledcWrite(PWM_1, spd);
  ledcWrite(PWM_2, spd);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void lui()
{
  Serial.println("lui");
  ledcWrite(PWM_1, spd);
  ledcWrite(PWM_2, spd);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void trai()
{
  Serial.println("trai");
  ledcWrite(PWM_1, spd);
  ledcWrite(PWM_2, spd);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void phai()
{
  Serial.println("phai");
  ledcWrite(PWM_1, spd);
  ledcWrite(PWM_2, spd);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void dung()
{
  Serial.println("dung");
  ledcWrite(PWM_1, 0);
  ledcWrite(PWM_2, 0);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void gap()
{
  servogap.write(0);
  delay(0);
}

void nha()
{
  servogap.write(75);
  delay(0);
}
void nang()
{

  servonang.write(7);
  delay(0);
}
void ha()
{

  servonang.write(120);
  delay(0);
}
void gapnang()
{


}
void hanha()
{
}

void servoNang()
{
nang();

}
void servoGap()

{
  
    gap();

}
void servoHa()
{
  ha();

}
void servoNha()

{
 
    nha();

}
