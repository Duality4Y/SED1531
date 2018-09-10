#include <SED1531.h>
 
SED1531 lcd;
 
void setup(){
  lcd.begin();
  lcd.setCursor(0);
  lcd.setContrast(16);
  lcd.println("bam");
  lcd.println("bam");
  lcd.println("bam");
  lcd.println("bam");
  lcd.println("bam");
  lcd.println("bam");
  lcd.println("worked!");
  lcd.println("Hello World!");
  lcd.print("this is a long line yea it is long line");
  delay(2000);
  lcd.inverse(true);
}
void loop(){
  for(int c = 0;c<31;c++){
    lcd.setContrast(c);
    delay(20);  
  }
  for(int c=31;c>0;c--){
    lcd.setContrast(c);
    delay(15);
  }
  lcd.setContrast(16);
  lcd.inverse(false);
  for(int i = 1;i<=6;i++){
    lcd.setMarker(i,true);
    delay(400);
    lcd.setMarker(i,false);
    delay(100);
  }
  lcd.inverse(true);
}