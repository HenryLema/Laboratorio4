
/*
 * Nombre: Henry Lema
 *Asignatura : Sistemas Embebidos
 * 
 */
 #include <MsTimer2.h>// librerias timer
#include <LiquidCrystal.h>
#include <avr/power.h> // encendido
#include <avr/sleep.h>
#include <EEPROM.h>
int on=0,i,h,j;
int tiempo=0,r,k,kc,hr=0,mm=0,mr;
int cont=0;
const int leds[3] = {4,5,6};
long randLed;
long randLed2;
LiquidCrystal lcd (13,12,11,10,9,8);
int act=0;
String dato,clave="asdf";
void setup() {
for(i=0;i<3;i++){
  hr= EEPROM.read(0);
    mm= EEPROM.read(0);
    pinMode(leds[i],OUTPUT);}
  Serial.begin(9600);
  lcd.begin(16,2);
  MsTimer2::set(1000,reloj);
  attachInterrupt(0,activacion,LOW);
  attachInterrupt(1,configuracion,LOW);  
  Serial.println("Alarma Home\n");
  delay (1000);
  Serial.println("Ingresar Clave");
  power_adc_disable();
  lcd.setCursor(2,0);
  lcd.print("SISTEMA OFF  ");
  lcd.setCursor(2,1);
  lcd.print("ALARMA CASA");

}
void loop() {
  if(on==1){
    if(Serial.available()){
      dato=Serial.readString();
      }
  
  Serial.println(analogRead(0));
  delay(1000);
}

 if(k==1){mm++;
 if(mr<3600){
  EEPROM.write(0,hr);
  EEPROM.write(1,mm);
  }
  if(mm==60){
    hr++;
    mm=0;
    }
  if(hr==24){hr=0;
  mm=0;
  mr=0;
  }
  delay(10);
  
 
 lcd.setCursor(1,0);  
 lcd.print("SISTEMA ONLINE"); 
 lcd.setCursor(0,1); 
 lcd.print(String(hr)+" : "+String(mm)+"               ");  
 kc++;
 randLed= random(0,3);
 randLed2 = random (0,3);
 digitalWrite(leds[randLed], HIGH);
  digitalWrite(leds[randLed2], LOW);   
  
     delay(300);
     
  if(h<25){    
    for(j=0;j<h;j++){
      for(i=0;i<4;i++){
        digitalWrite(leds[i], LOW);
       
       } 
    }
    
  }
 //Serial.println(String(cont));
}
}
void activacion(){
  switch(on){
    case 0:
    Serial.println("confirme activacion");
    tiempo=20;
    
    on++;
      break;
    case 1:
    Serial.println(String("Activacion en: ")+String(tiempo)+String("seg"));
    MsTimer2::start();
    on++;
   
    break;
    case 2:
    Serial.println("vuelva a ingresar la clave");
    tiempo=0;
    on=0;
    MsTimer2::stop();
    power_adc_disable();
    on++;
    k=0;
    break;
   
  }
}

void configuracion(){
  if(on==1){if(dato==clave){
      Serial.println(String("desea activar"));
    if(tiempo<21){
      Serial.println(String("Activacion en: ")+String(tiempo)+String("seg"));
    }
    else
    tiempo=0;cont=0;
  }
  else{Serial.println("CLAVE ERRONEA");on=on+2;}}
}

void reloj(){
  cont++;
  r=tiempo-cont;
  Serial.println(String("Tiempo de salida: ")+String(tiempo-cont));
  lcd.setCursor(1,0);
  lcd.print("Activado en:"+String(r)+"   ");
  lcd.setCursor(1,13);
  if(cont==tiempo){
    power_adc_enable();
    delay(10);
    Serial.println(analogRead(0));
    cont=0;tiempo=0;on=0;dato="";
    MsTimer2::stop();
    k++;
   // lcd.setCursor(1,0);
  //  lcd.print("SISTEMA OFF");
    lcd.setCursor(0,1);
    lcd.print("ALARMA CASA ");
    power_adc_disable();
  }
  
}
