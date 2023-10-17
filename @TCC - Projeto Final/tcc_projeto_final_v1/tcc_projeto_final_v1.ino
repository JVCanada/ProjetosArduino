
/* 
  Projeto: Protótipo de Troca Parcial Automática de um aquário marinho
  Programador: Joao Victor Canada, Eduardo Mendes e Ricardo de Almeida
  Data: 19/10/2023
  Versão: 1.0
*/



/* DEFINIÇÕES E DECLARAÇÕES DO BLINK: 

#define BLYNK_TEMPLATE_ID "TMPL277BigU_T"
#define BLYNK_TEMPLATE_NAME "TPArduino"
#define BLYNK_AUTH_TOKEN "gXGLO-56MxFROERE7SnBlNdpoFYjO_FI"

#define BLYNK_PRINT Serial

#include "ESP8266_Lib.h"
#include "BlynkSimpleShieldEsp8266.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "gXGLO-56MxFROERE7SnBlNdpoFYjO_FI";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CANADA_2G";
char pass[] = "Ma100809";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include "SoftwareSerial.h"
SoftwareSerial EspSerial(10,11); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

*/ 





/* Bibliotecas do sensor de Temperatura e do Display
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <LiquidCrystal.h>
*/

/* DEFINIÇÕES E DECLARAÇÕES DO DISPLAY 


*/



/* DEFINIÇÕES E DECLARAÇÕES DO SENSOR DE PH

float calibration_value = 21.34; //21.34, 24.34, 21.34 - 0.7
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
// for the OLED display

*/


/* DEFINIÇÕES E DECLARAÇÕES DO SENSOR DO TDS E DO SENSOR DE TEMPERATURA:

namespace pin {
const byte tds_sensor = A0;
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

*/


/* DEFINIÇÕES E DECLARAÇÕES DOS CÓDIGOS DAS BOMBAS E RELÉS 
// #define bombaDescarte (ou relé)
// #define bombaGalao (ou relé)
// #define bombaReposicao (ou relé)
// #define bombaCirculacao (ou relé)
*/

/* FUNÇÕES DOS PINOS VIRTUAIS (PARA AS BOMBAS)
BLYNK_WRITE(V0){

}

BLYNK_WRITE(V1){

}

BLYNK_WRITE(V2){

}

BLYNK_WRITE(V3){

}

*/


void setup() {
  // Debug console
	Serial.begin(9600);

  // Set ESP8266 baud rate
	//EspSerial.begin(ESP8266_BAUD);

  // Inicia blynk:
  // Blynk.begin(auth, wifi, ssid, pass);

  // Inicia o dallas temperature:
  //dallasTemperature.begin();

}

void loop() {
  
  // Roda o Blynk:
  // Blynk.run();

  leituraPh();

  leituraTDS();

}


float leituraPh() {

  /* 
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

 Serial.println("pH Val: ");
 Serial.print(ph_act);
 delay(1000);
  */
  
}

float leituraTDS() {

  /* 
  dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  float rawEc = analogRead(pin::tds_sensor) * device::aref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp - 25.0); // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration; // temperature and calibration compensation
  sensor::tds = (133.42 * pow(sensor::ec, 3) - 255.86 * sensor::ec * sensor::ec + 857.39 * sensor::ec) * 0.5; //convert voltage value to tds value
  Serial.print(F("TDS:")); Serial.println(sensor::tds);
  Serial.print(F("EC:")); Serial.println(sensor::ec, 2);
  Serial.print(F("Temperature:")); Serial.println(sensor::waterTemp,2);
  //lcd.clear();
  //lcd.print("TDS   EC   Temp");
  //lcd.setCursor(0,1); 
  //lcd.print(sensor::tds); 
  //lcd.setCursor(5,1); 
  //lcd.print(sensor::ec, 2); 
  //lcd.setCursor(11,1); 
  //lcd.print(sensor::waterTemp,2); 
  */

}

void mostraPh_TDS() {

}
