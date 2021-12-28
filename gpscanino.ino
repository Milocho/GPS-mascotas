 #include <LiquidCrystal.h>   //incluimos libreria para LCD
 #include <SoftwareSerial.h>  //incluimos libreria SoftwareSerial
 #include <TinyGPS.h>         //incluimos libreria TinyGPS


 LiquidCrystal lcd(12, 11, 10, 9, 8, 7);   /* LCD RS pin to digital pin 12 * LCD Enable pin to digital pin 11 
                                               * LCD D4 pin to digital pin 10 * LCD D5 pin to digital pin 9
                                               * LCD D6 pin to digital pin 8  * LCD D7 pin to digital pin 7 */
    TinyGPS GPS;                      //Declaramos el objeto GPS
    SoftwareSerial Serial_GPS(4,3);   //Declaramos el pin 4 (Tx del GPS) y 3 (Rx del GPS)                                               


    unsigned long chars;
    unsigned short sentences, failed_checksum;
    

    void setup() {
     lcd.begin(16,2); 
     Serial_GPS.begin(9600); //Iniciamos el puerto serie del gps
        
     lcd.clear();
     lcd.setCursor(0, 0); 
     lcd.print("  Arduino Nano  "); 
     lcd.setCursor(0, 1);
     lcd.print("GPS Neo-6M & LCD");
     delay(5000);
    }

    void loop() {

     while(Serial_GPS.available()){
      int c = Serial_GPS.read(); 
      if(GPS.encode(c)){
       float latitude, longitude;
       GPS.f_get_position(&latitude, &longitude);
       lcd.clear();
       lcd.setCursor(0, 0); 
       lcd.print("Lat.= ");  
       lcd.setCursor(7, 0);
       lcd.print(latitude,6);
       lcd.setCursor(0, 1); 
       lcd.print("Lon.= ");  
       lcd.setCursor(6, 1);
       lcd.print(longitude,6);
       delay(1000);
       GPS.stats(&chars, &sentences, &failed_checksum);
      }
     }
    }

    
