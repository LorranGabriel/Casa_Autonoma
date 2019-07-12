/*************************************************************
D0 -- 16
D1 -- 5
D2 -- 4
D3 -- 0
D4 -- 2
D5 -- 14
D6 -- 12
D7 -- 13
D8 -- 15
A0 -- 17
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Ultrasonic.h>

#define pino_trigger 12
#define pino_echo 15
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2ao7bq_4ozsSPOFBQGp0fVntQjOzM7mo";
Ultrasonic ultrasonic(pino_trigger, pino_echo);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Legume faz bem";
char pass[] = "mariaconta1";
Servo servo;
int sensorPin = A0;
int sensorValue = 0; 
int pinorele = 2; //Pino ligado ao rele
int pinopir = 7; //Pino ligado ao sensor PIR
int acionamento; //Variavel para guardar valor do sensor
bool estadoSensor;


BlynkTimer timer;


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  servo.attach(5);
  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13,INPUT);
 
  timer.setInterval(1000L, myTimerEvent);

}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)
{
  servo.write(param.asInt());
}

BLYNK_WRITE(V2)
{
 if(param.asInt()){
   digitalWrite(16,HIGH);
 }
 else{
  digitalWrite(16,LOW);
 }
}


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{     
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  delay(100);
  if(sensorValue > 500){
   digitalWrite(14,LOW);
  }
  else{
  digitalWrite(14,HIGH);
  }

  
  estadoSensor = digitalRead(13);
  Serial.println(estadoSensor);
  
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);

}
