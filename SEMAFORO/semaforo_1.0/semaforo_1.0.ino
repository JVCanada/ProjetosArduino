/* 
  Projeto: Semáforo com três leds
  Programador: Joao Victor
  Data: 25/08/2023
  Versão: 1.0
*/

// Não é necessário colocar pontovirgula no define.

#define led_verde 46
#define led_amarelo 42
#define led_vermelho 38

void setup() {
  pinMode (led_verde, OUTPUT);
  pinMode (led_amarelo, OUTPUT);
  pinMode (led_vermelho, OUTPUT);

  digitalWrite (led_verde, HIGH);

}

void loop() {
  
  delay(10000);
  digitalWrite (led_verde, LOW);
  digitalWrite (led_amarelo, HIGH);
  delay(3000);
  digitalWrite (led_amarelo, LOW);
  digitalWrite (led_vermelho, HIGH);
  delay(7000);
  digitalWrite (led_vermelho, LOW);
  digitalWrite (led_amarelo, HIGH);
  delay(3000);
  digitalWrite (led_vermelho, HIGH);
  digitalWrite (led_verde, HIGH);
  delay(5000);
  digitalWrite (led_verde, LOW);
  digitalWrite (led_amarelo, LOW);
  digitalWrite (led_vermelho, LOW);
  delay(5000);
  digitalWrite (led_verde, HIGH);
}
