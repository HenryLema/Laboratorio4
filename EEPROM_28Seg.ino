/*
 * Nombre: Henry Lema
 * Tarea: 12
 */
#include <EEPROM.h> // Librerias
#include<MsTimer2.h>
#include <LiquidCrystal.h>
#include <avr/wdt.h>
LiquidCrystal lcd (13, 12, 11, 10, 9, 8); // pines lcd 16x2
int i = 0;
int cont = 0;
void setup(){
  
  Serial.begin(9600); // cx serial
  Serial.println("reset"); // mensaje serial
  MsTimer2::set(1000, resetear);// segundo y metodo
  MsTimer2::start();
  i = EEPROM.read(0);
}

void loop() {
  
  Serial.println(i++);
  if (i < 255) {
    EEPROM.write(0, i);
  }
  else {
    i = 0;
  }
  delay(200);
}

void resetear() { //Metodo reset memoria 
  cont++;
  lcd.setCursor(0,0);
  lcd.print(cont);
  lcd.setCursor(7,1);
  lcd.print("Contador");
  if (cont>=28){
  wdt_disable();
  
    wdt_enable(WDTO_500MS); 
  }
}
