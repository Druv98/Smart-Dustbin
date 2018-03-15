#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cleancity-559cf.firebaseio.com"
#define FIREBASE_AUTH "FEm2l5Ukw7KeiE59xyKUyR7iplALwhFOhDNqdXI6"
#define WIFI_SSID "raju"
#define WIFI_PASSWORD "12345678"

int IR_1=14;
int IR_2=12;
int IR_3=13;
int level_ind=0;

void setup() {
  Serial.begin(115200);
  pinMode(IR_1,INPUT);  
  pinMode(IR_2,INPUT);
  pinMode(IR_3,INPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("/dusbins/dustbin1/level", 1);
  
}


void loop() {
Serial.print(digitalRead(IR_1));
Serial.print(digitalRead(IR_2));
Serial.println(digitalRead(IR_3));  
if(digitalRead(IR_1)==1 && digitalRead(IR_2)==0 && digitalRead(IR_3)==0)
 {
   level_ind=0;
 }
if(digitalRead(IR_1)==0 && digitalRead(IR_2)==0 && digitalRead(IR_3)==0)
 {
   level_ind=50;
   Serial.println(digitalRead(IR_1));
 }
if(digitalRead(IR_2)==1 && level_ind==50)
 {
   level_ind=75;
 }
if(digitalRead(IR_3)==1 && level_ind==75)
 {
   level_ind=90;
 }


 

if (level_ind==50 || level_ind==0) 
 {
   Firebase.setInt("/dusbins/dustbin1/level", 1);
 }
else if (level_ind==75) 
 {
   Firebase.setInt("/dusbins/dustbin1/level", 2);
 }
 else if (level_ind==90) 
 {
   Firebase.setInt("/dusbins/dustbin1/level", 3);
 }
 delay(200);
 Serial.println(level_ind);
}
