#include <NewPing.h>
#include <Servo.h>
#include<SoftwareSerial.h>
Servo myservo;
char bdata = 0;
SoftwareSerial blue(2, 3);
/*Mendeklarasikan komponen yang digunakan*/
23
#define mopping 12          // Mendefinisikan pin 12 Arduinouno.
#define TRIGGER_PIN 11 Mendefinisikan Arduino uno
trigger pin 11 ke sensor ultrasonic.
#define ECHO_PIN 10 Mendefinisikan Arduino uno echo
pin 10 ke sensor ultrasonic.
#define MAX_DISTANCE 1000   //Mendefinsikan jarak untuk ping sebesar 1000 
NewPing sonar(TRIGGER_PIN,ECHO_PIN, MAX_DISTANCE);
#define motor_aPin1 7
#define motor_aPin2 6
#define motor_bPin1 5
#define motor_bPin2 4
/*Mendefinisikan pin motor dc.*/
#define OB_range 30 Mendefinisikan jarak dengan
rentan 30
int i = 0, pos = 0, current_distance = 0;
int range0 = 0, range30 = 0, range60 = 0,
    range85 = 0, range90 = 0, range95 = 0,
    range120 = 0, range150 = 0, range180 = 0 ;
unsigned long previous_millis = 0;
char serialData;
/*Menggunakan data serial.*/
void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  blue.begin(9600);
  pinMode(motor_aPin1, OUTPUT);
  pinMode(motor_aPin2, OUTPUT);
  pinMode(motor_bPin1, OUTPUT);
  pinMode(motor_bPin2, OUTPUT);
  pinMode(mopping, OUTPUT);
}
/*Motor dc berfungsi sebagai output.*/
void relay_on()
{
  digitalWrite(mopping, HIGH);
}
void relay_off()
{
  digitalWrite(mopping, LOW);
}
/*Ketika relay menyala kondisi
motor dc pel dalam keadaan high
dan ketika relay mati kondisi motor
dc pel dalam keaadan low.*/

void brake()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, LOW);
}
/*Ketika robot dalam kondisi
berhenti maka motor dc roda dalam
keadaan low.*/
void forward()
{
  digitalWrite(motor_aPin1, HIGH);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, HIGH);
  digitalWrite(motor_bPin2, LOW);
}
/*Ketika robot dalam kondisi
bergerak maju kedepan maka
motor dc roda a1 dan b1 dalam
keadaan high dan motor dc roda a2
dan b2 dalam keadaan low.*/
void forward_left()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, HIGH);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, LOW);
}
/*Ketika robot dalam kondisi
bergerak maju kekiri maka motor
dc roda a1 , b1, b2 dalam keadaan
low dan motor dc roda a2 dalam
keadaan high.*/
void forward_right()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, HIGH);
}
/*Ketika robot dalam kondisi
bergerak maju kekanan maka
motor dc roda a1 , a1, b1 dalam
keadaan low dan motor dc roda b2
dalam keadaan high.*/
void backward()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, HIGH);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, HIGH);
}
/*Ketika robot dalam kondisi
bergerak mundur kebelakang maka
motor dc roda a1 dan b1 dalam
keadaan low dan motor dc roda a2
dan b2 dalam keadaan high.*/
void backward_right()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, HIGH);
  digitalWrite(motor_bPin2, LOW);
}
/*Ketika robot dalam kondisi
bergerak mundur kekanan maka
motor dc roda a1, a1, b2 dalam
keadaan low dan motor dc roda a1
dalam keadaan high.*/

void backward_left()
{
  digitalWrite(motor_aPin1, HIGH);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, LOW);
}
/*Ketika robot dalam kondisi
bergerak mundur kekiri maka
motor dc roda a2, b1, b2 dalam
keadaan low dan motor dc roda a1
dalam keadaan high.*/
void left()
{
  digitalWrite(motor_aPin1, LOW);
  digitalWrite(motor_aPin2, HIGH);
  digitalWrite(motor_bPin1, HIGH);
  digitalWrite(motor_bPin2, LOW);
}
/* Ketika robot dalam kondisi belok
kekiri maka motor dc roda a1 dan
b2 dalam keadaan low dan motor
dc roda a2 dan b1 dalam keadaan
high.*/
void right()
{
  digitalWrite(motor_aPin1, HIGH);
  digitalWrite(motor_aPin2, LOW);
  digitalWrite(motor_bPin1, LOW);
  digitalWrite(motor_bPin2, HIGH);
}
/*Ketika robot dalam kondisi belok
kekanani maka motor dc roda a2
dan b1 dalam keadaan low dan
motor dc roda a1 dan b2 dalam
keadaan high.*/ 
int range(int pos)
{
  myservo.write(pos);
  delay(300);
  current_distance = sonar.ping_cm();
  if (current_distance == 0)
    current_distance = 100;
  if (current_distance > 0 &&
      current_distance < 15) {
    Serial.print("B");
    if (pos == 90) {
      backward(); delay(500);
    }
    if (pos < 90) {
      backward_right(); delay(500);
    }
    if (pos > 90) {
      backward_left(); delay(500);
    }
    return current_distance;
  }
}
void loop()
{
  Kondisi perulangan
  26
Automatic: brake();
  delay(300);
  while (1) {
    if (blue.available() > 0)
      serialData = blue.read();
    if (serialData == '5')
      goto Manual;
above: range90 = 0;
    range90 = range(90);
    delay(10);
    while (range90 >= OB_range ) {
      if (millis()
          - previous_millis > 2000) {
        previous_millis = millis();
        range(180);
        delay(50);
        range(0);
        delay(50);
      }
      range90 = range(90);
      forward(); Serial.print("F");
      if (blue.available() > 0)
        serialData = blue.read();
      if (serialData == '5')
        goto Manual;
    }
    brake();
    if (range90 < OB_range) {
      brake();
      range60 = 0;
      range60 = range(60);
      delay(200);
      range120 = 0;
      27
      range120 = range(120);
      delay(200);
      if (blue.available() > 0)
        serialData = blue.read();
      if (serialData == '5')
        goto Manual;
      if (range60 > OB_range || range120
          > OB_range
         )
      {
        if (range60 >= range120) {
          forward_right(); Serial.print("R");
          delay(50); goto above;
        }
        else if (range60 < range120) {
          forward_left(); Serial.print("L");
          delay(50); goto above;
        }
      }
      if (range60 < OB_range && range120
          < OB_range) {
above1: range30 = 0;
        range30 = range(30);
        delay(200);
        range150 = 0;
        range150 = range(150);
        delay(200);
        if (blue.available() > 0)
          serialData = blue.read();
        if (serialData == '5')
          goto Manual;
        if (range30 > OB_range || range150
            > OB_range
           )
        {
          if (range30 >= range150) {
            right(); Serial.print("R");
            delay(100); goto above;
          }
          else if (range30
                   < range150) {
            left(); Serial.print("L");
            delay(100); goto above;
          }
        }
        28
        if (range30 < OB_range && range150
            < OB_range) {
          range0 = 0;
          range0 = range(0);
          delay(200);
          range180 = 0;
          range180 = range(180);
          delay(200);
          if (blue.available() > 0)
            serialData = blue.read();
          if (serialData == '5')
            goto Manual;
          if (range0 > OB_range || range180
              > OB_range
             )
          {
            if (range0 >= range180) {
              backward_right(); Serial.print("R");
              delay(200); goto above;
            }
            else if (range0 < range180) {
              backward_left(); Serial.print("L");
              delay(200); goto above;
            }
          }
          if (range0 < OB_range && range180
              < OB_range) {
            backward(); Serial.print("B");
            delay(200);
            goto above1;
          }
        }
      }
    }
  }
Manual: brake();
  delay(300);
  while (1) {
    if (blue.available() > 0)
      serialData = blue.read();
    if (serialData == '6')
      goto Automatic;
    29
    if (serialData == '1')
      forward();
    if (serialData == '3')
      backward();
    if (serialData == '0')
      brake();
    if (serialData == '2')
      left();
    if (serialData == '4')
      right();
    if (serialData == '7')
      relay_on();
    if (serialData == '8')
      relay_off();
  }
}
