#include <Servo.h>

Servo myservo;

#define motorkiriA 6
#define motorkiriB 5
#define motorkananA 9
#define motorkananB 10

#define trigPin 8
#define echoPin 7

long duration;
int distance;
int posisi;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(motorkiriA, OUTPUT);
  pinMode(motorkiriB, OUTPUT);
  pinMode(motorkananA, OUTPUT);
  pinMode(motorkananB, OUTPUT);
  myservo.attach(3);
}

void motor(int pwmkiriA, int pwmkiriB, int pwmkananA, int pwmkananB) {
  analogWrite(motorkiriA, pwmkiriA);
  analogWrite(motorkiriB, pwmkiriB);
  analogWrite(motorkananA, pwmkananA);
  analogWrite(motorkananB, pwmkananB);
}

void loop() {
  cekJarak();
  myservo.write(90);
  if (distance > 10) {
    motor(255, 0, 255, 0);
  }
  else {
    cekPosisi();
    if (posisi == 1) { //belok kiri
      motor(0, 255, 255, 0);
      delay(1000);
      posisi = 2;
    }
    else if (posisi == 3) { //belok kanan
      motor(255, 0, 0, 255);
      delay(1000);
      posisi = 2;
    }
    else {
      motor(0, 0, 0, 0);
      delay(1000);
      posisi = 2;
    }
    //cek kondisi kiri -  depan - kanan

}}



void cekJarak() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
}


void cekPosisi() {
  myservo.write(180);
  delay(500);
  cekJarak();
  int posA = distance;
  myservo.write(90);
  delay(500);
  cekJarak();
  int posB = distance;
  myservo.write(0);
  delay(500);
  cekJarak();
  int posC = distance;
  // anggap bahwa nilai yang didapat tidak ada yang sama
  if (posA > posB) { // cek apakah A lebih besar dari B?  jika ya bandingkan dengan C jika tidak B berarti lebih besar dan B harus dibandingkan dengan C
    if (posA > posC) { // cek apakah A lebih besar dari C?
      posisi = 1; //jika ya, posisi dipilih berarti sama dengan 1 = ke kiri
    }
    else {
      posisi = 3; //jika tidak, posisi dipilih berarti sama dengan 3 = ke kanan
    }
  }

  else {
    if (posB > posC) { // cek apakah B lebih besar dari C?
      posisi = 2; // jika ya, posisi dipilih berarti sama dengan 2 = maju/// kok aneh yaa :D
    }
    else {
      posisi = 3; //jika tidak, posisi dipilih berarti sama dengan 3 = ke kanan
    }
  }
}
