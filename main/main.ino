#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif
BluetoothSerial SerialBT;
#define PWM_FREQ 1000
#define PWM_RES 8

#define Drv_In1_pin 23
#define PWM_In1_pin 16       // PWM
#define Drv_In1_chn 2

#define Drv_In4_pin 17
#define PWM_In4_pin 15    // PWM
#define Drv_In4_chn 1

int motor_speed = 200; 
#define SENSOR_1 27
#define SENSOR_2 26
#define SENSOR_3 25
#define SENSOR_4 33
#define SENSOR_5 32

#define On_calb_led_pin 19

#define spd 110

#define SERVO_FREQ 50  // tĂ¡ÂºÂ§n sĂ¡Â»â€˜
#define SERVO_RES 11   // Ă„â€˜Ă¡Â»â„¢ phĂƒÂ¢n giĂ¡ÂºÂ£i

#define SERVO_1_chn 7
#define SERVO_1_pin 5  // UP/down
#define SERVO_2_chn 8
#define SERVO_2_pin 13  // UP/down
#define SERVO_3_chn 9
#define SERVO_3_pin 12  // UP/down

int mode = 0;

void tien() {
  digitalWrite(Drv_In1_pin, HIGH);
  digitalWrite(Drv_In4_pin, HIGH);
  ledcWrite(Drv_In1_chn, motor_speed);  // PWM_1_pin
  ledcWrite(Drv_In4_chn, motor_speed);
}
void lui() {
  digitalWrite(Drv_In1_pin, LOW);
  digitalWrite(Drv_In4_pin, LOW);
  ledcWrite(Drv_In1_chn, motor_speed);  // PWM_1_pin
  ledcWrite(Drv_In4_chn, motor_speed);
}
void retrai() {
  digitalWrite(Drv_In1_pin, HIGH);
  digitalWrite(Drv_In4_pin, LOW);
  ledcWrite(Drv_In1_chn, motor_speed);  // PWM_1_pin
  ledcWrite(Drv_In4_chn, motor_speed);
}
void rephai() {
  digitalWrite(Drv_In1_pin, LOW);
  digitalWrite(Drv_In4_pin, HIGH);
  ledcWrite(Drv_In1_chn, motor_speed);  // PWM_1_pin
  ledcWrite(Drv_In4_chn, motor_speed);
}

void dung() {
  ledcWrite(Drv_In4_chn, 0); // PWM_2_pin
  ledcWrite(Drv_In1_chn, 0); // PWM_1_pin
}
void tien_1() {
  digitalWrite(Drv_In1_pin, 1);
  ledcWrite(Drv_In1_chn, spd-25);
  digitalWrite(Drv_In4_pin, 1);
  ledcWrite(Drv_In4_chn, spd-25);
}
void lui_1() {
  digitalWrite(Drv_In1_pin, 0);
  ledcWrite(Drv_In1_chn, spd-25);
  digitalWrite(Drv_In4_pin, 0);
  ledcWrite(Drv_In4_chn, spd-25);
}
void rephai_1() {
  digitalWrite(Drv_In1_pin,0);
  ledcWrite(Drv_In1_chn, spd);
  digitalWrite(Drv_In4_pin, 1);
  ledcWrite(Drv_In4_chn, spd+20);
}
void retrai_1() {
  digitalWrite(Drv_In1_pin, 1);
  ledcWrite(Drv_In1_chn, spd);
  digitalWrite(Drv_In4_pin, 0);
  ledcWrite(Drv_In4_chn, spd+20);
}
void rephai1() {
  digitalWrite(Drv_In1_pin, 0);
  ledcWrite(Drv_In1_chn, spd);
  digitalWrite(Drv_In4_pin, 1);
  ledcWrite(Drv_In4_chn, spd-10);
}
void retrai1() {
  digitalWrite(Drv_In1_pin, 1);
  ledcWrite(Drv_In1_chn, spd-10);
  digitalWrite(Drv_In4_pin, 0);
  ledcWrite(Drv_In4_chn, spd);
}
void rephai2() {
  digitalWrite(Drv_In1_pin, 0);
  ledcWrite(Drv_In1_chn, spd);
  digitalWrite(Drv_In4_pin, 1);
  ledcWrite(Drv_In4_chn, spd);
}
void retrai2() {
  digitalWrite(Drv_In1_pin, 1);
  ledcWrite(Drv_In1_chn, spd);
  digitalWrite(Drv_In4_pin, 0);
  ledcWrite(Drv_In4_chn, spd);
}
void tien_999() {
  digitalWrite(Drv_In1_pin, 1);
  ledcWrite(Drv_In1_chn, spd-50);
  digitalWrite(Drv_In4_pin, 1);
  ledcWrite(Drv_In4_chn, spd-50);
}

const int threshold = 1150; //1150
int sensor_1, sensor_2, sensor_3, sensor_4, sensor_5;
int vitri;

void readSensor() {
    Serial.print("    ");  
             Serial.print(analogRead(SENSOR_1));  
                   Serial.print("    ");  
                         Serial.print(analogRead(SENSOR_2));  
                               Serial.print("    ");  
                                     Serial.print(analogRead(SENSOR_3));  
                                           Serial.print("    ");  
                                                 Serial.print(analogRead(SENSOR_4)); 
                                                  Serial.print("    ");  
                                                 Serial.println(analogRead(SENSOR_5)); 
    sensor_1 = (analogRead(SENSOR_1) >= threshold) ? 1 : 0;
    sensor_2 = (analogRead(SENSOR_2) >= threshold) ? 1 : 0;
    sensor_3 = (analogRead(SENSOR_3) >= threshold) ? 1 : 0;
    sensor_4 = (analogRead(SENSOR_4) >= threshold) ? 1 : 0;
    sensor_5 = (analogRead(SENSOR_5) >= threshold) ? 1 : 0;
}

void do_line() {
    readSensor();
    vitri = 10000 * sensor_1 + 1000 * sensor_2 + 100 * sensor_3 + 10 * sensor_4 + sensor_5;
    Serial.println(vitri);
    switch (vitri) {
        // case 0:
        //     lui();
        //     Serial.println("LUI");
        //     break;
       case 10000: case 11000:  case 11110: 
            // rephai_1();
            retrai_1();
            Serial.println("rephai_1");
            // tien_999();
            break;
        case 1: case 11:  case 111: case 1111: 
            // retrai_1();
            rephai_1();
            Serial.println("retrai_1");
            // tien_999();
            break;
        case 100: case 1110: case 11111: case 11011:
            lui_1();
            Serial.println("tien");
            break;
        case 110: case 10: 
            rephai1();
            // retrai1();
            Serial.println("retrai1 1");
            break;
        case 1000: 
            Serial.println("rephai1 1");
            retrai1();
            // rephai1();
            break;
    }
}

// //DsR
void chan21(){
  ledcWrite(SERVO_2_chn,100);
}
void chan22(){
  ledcWrite(SERVO_2_chn,130);
}
void nang(){
  ledcWrite(SERVO_3_chn,250);
}
void nang2(){
  ledcWrite(SERVO_3_chn,120);
}
void gap() {
  ledcWrite(SERVO_1_chn,240);
}
void nha(){
  ledcWrite(SERVO_1_chn,190);
}

// ba gia 2
// void chan21(){
//   ledcWrite(SERVO_2_chn,100);
// }
// void chan22(){
//   ledcWrite(SERVO_2_chn,150);
// }
// void nang(){
//   ledcWrite(SERVO_3_chn,220);
// }  
// void nang2(){
//   ledcWrite(SERVO_3_chn,110);
// }
// void gap() {
//   ledcWrite(SERVO_1_chn,150);
// }
// void nha(){
//   ledcWrite(SERVO_1_chn,90);
// }

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DsR"); 
  // MOTOR
  pinMode(Drv_In1_pin,OUTPUT);
  ledcSetup(Drv_In1_chn, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_In1_pin, Drv_In1_chn);

  pinMode(Drv_In4_pin,OUTPUT);
  ledcSetup(Drv_In4_chn, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_In4_pin, Drv_In4_chn);

  ledcSetup(SERVO_1_chn, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(SERVO_1_pin, SERVO_1_chn);
  ledcSetup(SERVO_2_chn, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(SERVO_2_pin, SERVO_2_chn);
  ledcSetup(SERVO_3_chn, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(SERVO_3_pin, SERVO_3_chn);

}
void dieukhien() {
  if (SerialBT.available()) {
    int blue = SerialBT.read();
      switch (blue) {
      case 0:
        dung();
        break;
      case 1:
        tien();
        break;
      case 2:
       retrai();
        // rephai();
        break;
      case 3:
        lui();
        break;
      case 4:
      rephai();
        // retrai();
        break;
      case 11:
        gap();
        break;
      case 12:
        nha();
        break;
      case 13:
        chan22();
        break;
      case 14:
        chan22();
        break;
      case 15:
        nang2();
        break;
      case 16:
        nang2();
        break;
      case 10:
        chan21();
        break;
      case 17:
        nang();
        break;
      case 18:
        nang();
        break;
  //     case 20:
  //     mode=0;
  //     break;
  //   case 21:
  //     mode =1;
  //     break;
    }
  //    if (blue ==20 ) {
  //     mode = 0; // Chuyển sang điều khiển
  //   } else if (blue == 21) {
  //     mode = 1; // Chuyển sang dò line
  //   } 

  //   if (mode == 1) {
  //     do_line();
  //   } else {
  //     dieukhien();
  // }
  }
}
void loop() {
  if (SerialBT.connected()) {
    dieukhien();}
  else{
    do_line();
  }
  // for(int i=0 ; i<360; i+=10){
  //   ledcWrite(SERVO_1_chn,i);
  //   Serial.println(i);
  //   delay(1000);
 // }
  // dieukhien();
  // ledcWrite(SERVO_1_chn,100);
  // delay(1000);
}