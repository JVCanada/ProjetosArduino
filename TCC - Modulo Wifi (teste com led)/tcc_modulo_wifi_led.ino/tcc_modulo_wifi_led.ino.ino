#define BLYNK_TEMPLATE_ID "TMPL277BigU_T"
#define BLYNK_TEMPLATE_NAME "TPArduino"
#define BLYNK_AUTH_TOKEN "gXGLO-56MxFROERE7SnBlNdpoFYjO_FI"

#define BLYNK_PRINT Serial
#define led_vermelho 30

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

BLYNK_WRITE(V0){
  int valorPin = param.asInt();
  if(valorPin == 1) {
    digitalWrite (led_vermelho, HIGH); 
    Serial.print("Entrou em 1!");
  } else {
    digitalWrite (led_vermelho, LOW);
    Serial.print("Entrou em 0!");
  }
}

void setup()
{
	// Debug console
	Serial.begin(9600);

  // programacao do led com o pino virtual
  pinMode (led_vermelho, OUTPUT);
	
	delay(10);
	
	// Set ESP8266 baud rate
	EspSerial.begin(ESP8266_BAUD);
	delay(10);
	
	Blynk.begin(auth, wifi, ssid, pass);
}

void loop()
{
	Blynk.run();
}
