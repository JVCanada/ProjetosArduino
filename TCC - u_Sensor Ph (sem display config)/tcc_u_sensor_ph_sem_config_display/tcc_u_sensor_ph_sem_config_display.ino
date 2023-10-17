
/*
  Para verificar a configuração do display, acessar:
  https://www.electroniclinic.com/ph-meter-arduino-ph-meter-calibration-diymore-ph-sensor-arduino-code/

*/


float calibration_value = 21.34; //21.34, 24.34, 21.34 - 0.7
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
// for the OLED display


void setup() 
{

 Serial.begin(9600);

}
void loop() {

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
}
