
/* 
  Projeto: Protótipo de Troca Parcial Automática de um aquário marinho
  Programador: Joao Victor Canada, Eduardo Mendes e Ricardo de Almeida
  Data: 26/10/2023
  Versão: 1.5
*/

// Bibliotecas do sensor de Temperatura e do Display
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleTimer.h>
#include <LiquidCrystal_I2C.h>

#define BLYNK_TEMPLATE_ID "TMPL277BigU_T"
#define BLYNK_TEMPLATE_NAME "TPArduino"
#define BLYNK_AUTH_TOKEN "gXGLO-56MxFROERE7SnBlNdpoFYjO_FI"

#define BLYNK_PRINT Serial

#include "ESP8266_Lib.h"
#include "BlynkSimpleShieldEsp8266.h"





// Definições e declarações do Blynk e do ESP:




// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "gXGLO-56MxFROERE7SnBlNdpoFYjO_FI";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Eduardo";
char pass[] = "271197edu";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1



 
// Definicao Timer:
SimpleTimer timer;











// DEFINIÇÕES E DECLARAÇÕES DO SENSOR DE PH

float calibration_value = 21.34; //21.34, 24.34, 21.34 - 0.7
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
// for the OLED display




// DEFINIÇÕES E DECLARAÇÕES DO SENSOR DO TDS E DO SENSOR DE TEMPERATURA:

namespace pin {
const byte tds_sensor = A4;
const byte one_wire_bus = 2; // Dallas Temperature Sensor
}

namespace device {
float aref = 4.3;
}

namespace sensor {
float ec = 0;
unsigned int tds = 0;
float waterTemp = 0;
float ecCalibration = 1;
}

OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);




// DEFINIÇÕES E DECLARAÇÕES DOS CÓDIGOS DOS RELÉS 

int rele1 = 26;
int rele2 = 28;
int rele3 = 7;
int valorPin;
int valorPin2;

// DEFINIÇÕES DAS SÁIDAS DOS RELÉS PARA O ESP32
int detectaEsp1 = 22;
int detectaEsp2 = 24;




/*
BLYNK_WRITE(V2){
  int valorPin3 = param.asInt();
  if(valorPin3 == 1) {
    digitalWrite (rele3, HIGH); 
    Serial.print("V2: Entrou em 1!");
  } else {
    digitalWrite (rele3, LOW);
    Serial.print("V2: Entrou em 0!");
  }
}
*/






void setup() {

  // PinMode do Rele1
  pinMode(rele1, OUTPUT);
  //digitalWrite (rele1, LOW);

  // PinMode do Rele2
  pinMode(rele2, OUTPUT);
  //digitalWrite (rele1, LOW);

  // Detecção de relé (via ESP32)
  pinMode(detectaEsp1, INPUT);
  pinMode(detectaEsp2, INPUT);

  // Debug console
	Serial.begin(9600);
  //Serial.begin(115200);

  // Set ESP8266 baud rate
	
  // Inicia blynk:
  

  // Inicia o dallas temperature:
  dallasTemperature.begin();

  // Inicio Wire:
  Wire.begin();
  
  // timer ph (para leitura)
  timer.setInterval(60000L, leituraPh);
  delay(10000);
  timer.setInterval(60000L, leituraTDS);
  

}

void loop() {
  
  // Roda o Blyn

  // rodando o timer
  timer.run();

  delay(10);

  // FUNÇÕES DOS PINOS VIRTUAIS (PARA AS BOMBAS)

  valorPin = digitalRead(detectaEsp1);
  if(valorPin == 1) {
    digitalWrite(rele1, HIGH); 
    //Serial.println("V0: Entrou em 1!");
  } else {
    digitalWrite(rele1, LOW);
    //Serial.println("V0: Entrou em 0!");
  }




  valorPin2 = digitalRead(detectaEsp2);
  if(valorPin2 == 1) {
    digitalWrite(rele2, HIGH); 
    //Serial.println("V1: Entrou em 1!");
  } else {
    digitalWrite(rele2, LOW);
    //Serial.println("V1: Entrou em 0!");
  }




}


float leituraPh() {

   
  // Ajustar a entrada do sensor de ph (caso não seja A1).
  for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A1);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;
 double phV3 = (float)ph_act;
 Serial.print("0:");
 Serial.println(phV3);
 //Serial.print(phV3);
 //delay(1000);
 //Blynk.virtualWrite(V3, phV3);
  
  
}


float leituraTDS() {

  //delay(10000);
  dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  float rawEc = analogRead(pin::tds_sensor) * device::aref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp - 25.0); // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration; // temperature and calibration compensation
  sensor::tds = (133.42 * pow(sensor::ec, 3) - 255.86 * sensor::ec * sensor::ec + 857.39 * sensor::ec) * 0.5; //convert voltage value to tds value
  //Serial.print("1"+sensor::tds);
  //Blynk.virtualWrite(V4, sensor::tds);
  Serial.print(F("TDS:")); Serial.println(sensor::tds);
  //Serial.print(F("EC:")); Serial.println(sensor::ec, 2);
  //Serial.print(F("Temperature:")); Serial.println(sensor::waterTemp,2);
  

}


