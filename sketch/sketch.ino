 // La función setup corre una vez, al prenderse el Arduino
// o bien al reiniciar mediante el botón reset
  //anodo comun 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

//definimos NTPClient para poder consultar el tiempo.
const long utcOffset = -10800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org",utcOffset);


//definimos wifiClient para conectarnos a una red
WiFiClient wifiClient;
const char* ssid = "FiberCorp WiFi887 2.4GHz";
const char* password = "0041285223";
char host[] = "192.168.0.7";
const int digitos [10][7] = {
   /*0*/ {0,0,0,0,0,0,1},
    /*1*/ {1,0,0,1,1,1,1},
    /*2*/ {0,0,1,0,0,1,0},
    /*3*/ {0,0,0,0,1,1,0},
    /*4*/ {1,0,0,1,1,0,0},
    /*5*/ {0,1,0,0,1,0,0},
    /*6*/ {0,1,0,0,0,0,0},
    /*7*/ {0,0,0,1,1,1,1},
    /*8*/ {0,0,0,0,0,0,0},
    /*9*/ {0,0,0,0,1,0,0}

    };
const int OFF = HIGH;
const int A = 4;
const int B = 0;
const int C = 2;
const int D = 14;
const int E = 12;
const int F = 13;
const int G = 15;
int conmutador = 0;
const int N = 7;
const int SEGMENTOS[N] = {A,B,C,D,E,F,G};
int var = 0;
int unidad = 0;
int decena = 0;
int cont = 0;

  
void setup()
{
   Serial.begin(9600);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");  
    }
    Serial.println("Wifi Connected");
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
   //inicializamos pines digitales conectados a los segmentos del display.
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(5,OUTPUT);
    for (int i=0; i<N; i++){
      pinMode(SEGMENTOS[i], OUTPUT);
      digitalWrite(SEGMENTOS[i], OFF);//apagar
    }
    timeClient.begin();
}


void loop(){
  delay(10);
  int sensorValue = analogRead(A0); 
  if(sensorValue < 30){
    if(decena == 0 && unidad == 0){
      timeClient.update();
      httpPOST("start",timeClient.getFormattedTime());
    } 
    delay(50);
    unidad++;
    cont ++;
    if(unidad > 9){
      unidad = 0;
      decena += 1;
      if(decena > 9){
        decena = 0;
        }
      }
  }
  if(conmutador == 0){
    digitalWrite(10,1); // 10 es el pin de la unidad
    digitalWrite(9,0); // 9 es el pin de la decena
    var = unidad;
    conmutador = 1;
    }else{
      digitalWrite(10,0);
      digitalWrite(9,1);
      var = decena;
      conmutador = 0;
      }
      print(var);

      if(cont == 20){
          timeClient.update();
          httpPOST("finish",timeClient.getFormattedTime());
          digitalWrite(5, HIGH);
          delay(5000);
          digitalWrite(5, LOW);
          cont = 0;
          unidad = 0;
          decena = 0;
        }
  
}

void httpPOST(String timer, String date){
  int contRepeat = 0;
  HTTPClient http;
  char *url = "http://192.168.0.7:3000/post";
  http.begin(wifiClient,url);
  http.addHeader("Content-Type","application/json");
  DynamicJsonDocument postMessage(2048);
  postMessage["message"] = timer;
  postMessage["time"] = date;
  String jsonBody;
  serializeJson(postMessage,jsonBody);
  Serial.println(jsonBody);
  int resCode = http.POST(jsonBody);
  Serial.println(resCode);
  while(resCode != 201 && contRepeat < 3){
    int resCode = http.POST(jsonBody);
    Serial.println(resCode);
    contRepeat++;
  } 
  String res = http.getString();
  parserMessage(res);
  http.end();
}
void httpGET(){
  HTTPClient http;
  char *url = "http://192.168.0.7:3000/";
  http.begin(wifiClient,url);
  int resCode = http.GET();
  Serial.println(resCode);
  String res = http.getString();
  Serial.println(res);
  parserMessage(res);
  http.end();
}
void parserMessage(String res){
  DynamicJsonDocument doc(2048);
  deserializeJson(doc,res);
  const char* message = doc["message"];
  Serial.println(message);
}
void print(int d){
  for (int i=0; i<N; i++){
    digitalWrite(SEGMENTOS[i], digitos[d][i]);
  }
}




// La función loop corre una y otra vez sin parar
  
  /*
 delay(10);
  int sensorValue = analogRead(A0); 
  if(sensorValue < 30){
    delay(50);
    unidad++;
    cont ++;
    if(unidad > 9){
      unidad = 0;
      decena += 1;
      if(decena > 9){
        decena = 0;
        }
      }
      
   }
   
  if(conmutador == 0){
    digitalWrite(10,1); // 10 es el pin de la unidad
    digitalWrite(9,0); // 9 es el pin de la decena
    var = unidad;
    conmutador = 1;
    }else{
      digitalWrite(10,0);
      digitalWrite(9,1);
      var = decena;
      conmutador = 0;
      }
      print(var);
      if(cont == 20){
          digitalWrite(5, HIGH);
          delay(5000);
          digitalWrite(5, LOW);
          cont = 0;
          unidad = 0;
          decena = 0;
        }
      
   }
  */
