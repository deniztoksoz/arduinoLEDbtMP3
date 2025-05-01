//Arduino MEGA 2560
//hc-05 Bt modülü
//mp3 tf 16p mp3 modülü
//5v ws2812b şerit led
//BT den gelen 1-9 sayılarına göre ilgili led yakıp mp3 çalan prje uygulaması


#include <Arduino.h>
#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>



//led tanımlamaları
#define NUM_LEDS  9    // Led sayısı
#define PIN       7      // led bağlantı pini
CRGB leds[NUM_LEDS];

//BlueTooth ayarları
#define BTL Serial2     // BT mega'nın tx2 rx2  bağlı

//MP3-Tf-16p ayarları
#define mp3Player Serial3    // mp3 mega'nın tx3 rx3 bağlı
#define busyPin 8
DFRobotDFPlayerMini myDFPlayer;

//Bt gelen veri için değişkenler....
String gelen; 
char harf; 


String sayy;

void setup(){
  BTL.begin(9600);
  Serial.begin(9600);

          mp3Player.begin(9600);
          Serial.println();
          Serial.println(F("DFRobot DFPlayer Mini Demo"));
          Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
        
        if (!myDFPlayer.begin(mp3Player)) {  
          Serial.println(F("Unable to begin:"));
          Serial.println(F("1.Please recheck the connection!"));
          Serial.println(F("2.Please insert the SD card!"));
          while(true);
        }
        Serial.println(F("DFPlayer Mini online."));
        pinMode(busyPin, INPUT);

  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);    // Set power limit of LED strip to 5V, 1500mA
  FastLED.clear();
  FastLED.show();       
}

void loop(){

  bt_veri_oku();
  int val = digitalRead(busyPin); 
  //delay(1000);
  //Serial.print(val);


  
  if (val == 0){
    
      BTL.write(11);
      delay(1000);
      Serial.println(11);

  } 
  if (val == 1){
    
      BTL.write(12);
      delay(1000);
      Serial.println(12);

  } 
}

void bt_veri_oku(){ //
        while(BTL.available()){
          //bt ile gelen veri okunarak stringe dönüşüyor
          harf = BTL.read();
          gelen.concat(harf);
              if(harf == '#'){ // if end of message received
                gelen = gelen.substring(0,gelen.indexOf('#'));

                Yak_Oku(gelen);
                Serial.print(gelen); 
                gelen = ""; 
                Serial.println();
              }
        }
}

void Yak_Oku(String deger){

      int sira = deger.toInt();
      //ilgili led 
      FastLED.clear();                  // ledi temizle
      leds[sira-1].setRGB(255, 0, 0);   // renk ayarla
      FastLED.show();                   // ledi yak

      myDFPlayer.play(sira);  //gelen sıraya göre ses çalınıyor
 

}
