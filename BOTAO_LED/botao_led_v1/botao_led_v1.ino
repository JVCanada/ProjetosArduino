/* 
  Projeto: botão e led
  Programador: Joao Victor
  Data: 25/08/23
  Versão: 1.0

*/

#define S1 43
#define S2 47 
#define led_verde 46
#define led_amarelo 42
#define led_vermelho 38 

void setup() {
  pinMode (S1, INPUT);
  pinMode (S2, INPUT);
  pinMode (led_verde, OUTPUT);
  pinMode (led_amarelo, OUTPUT);
  pinMode (led_vermelho, OUTPUT);

  digitalWrite (led_verde, LOW);
  digitalWrite (led_amarelo, LOW);
  digitalWrite (led_vermelho, LOW);
}

void loop() {
  
   
  if (digitalRead(S1) == HIGH) {
    digitalWrite (led_amarelo, HIGH);
    digitalWrite (led_vermelho, LOW);
    digitalWrite (led_verde, LOW);
  } else if (digitalRead(S2) == HIGH) {
    digitalWrite (led_amarelo, LOW);
    digitalWrite (led_vermelho, HIGH);
    digitalWrite (led_verde, HIGH);
  }

  
  
}
