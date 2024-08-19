#include<LiquidCrystal_I2C.h>
#include <DHT22.h>
#include<EEPROM.h>

#define I2C_ADDR   0x27
#define LCD_COLUMNS 20
#define LCD_LINE    4

#define pinData 2 

float T_fix =25;

int x=0;

 LiquidCrystal_I2C Icd(I2C_ADDR, LCD_COLUMNS,LCD_LINE);

 DHT22 dht22cns(pinData);

 byte Rbtn1=1;
 byte Bbtn1=3;
 byte Gbtn1=4;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Icd.init();
  //Icd.begin();
  Icd.backlight();
  Icd.clear();

  pinMode(Rbtn1, INPUT_PULLUP);
   pinMode(Bbtn1, INPUT_PULLUP);
    pinMode(Gbtn1, INPUT_PULLUP);

}


void loop() {
  if(digitalRead(Rbtn1)==LOW){T_fix++; delay(1000);}
   if(digitalRead(Bbtn1)==LOW){ T_fix--; delay(1000);}
    if(digitalRead(Gbtn1)==LOW){EEPROM.write(100,T_fix); delay(1000); }

    Serial.println("temp real value=");
  Serial.println(T_fix); 
  x=EEPROM.read(100);
  Serial.println("temp fix value=");
  Serial.println(x);
  delay(1000);
  
  
  // put your main code here, to run repeatedly:
float h =  dht22cns.getHumidity();
float temp = dht22cns.getTemperature();

Icd.clear();
Icd.setCursor(0,1);
Icd.print("T:");
Icd.print(temp);

Icd.setCursor(6,1);
Icd.print(" H ");
Icd.print(h);

if(T_fix < temp){
  Icd.setCursor(3,0);
  Icd.print("Over Heat"); 
} else if(T_fix > temp){
  Icd.setCursor(3,0);
  Icd.print("Cool"); 

} else{
  Icd.setCursor(3,0);
  Icd.print("Temp is ok"); 
}

delay(1000);

}
