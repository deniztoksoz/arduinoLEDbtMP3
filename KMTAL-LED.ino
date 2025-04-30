#include <Arduino.h>
#include <SoftwareSerial.h>
#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>

//led tanımlamaları
#define NUM_LEDS 9
#define DATA_PIN 4
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

//BlueTooth ayarları
SoftwareSerial BTL(2,3);


//MP3-Tf-16p ayarları
SoftwareSerial mp3Player(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

//Bt gelen veri için değişkenler....
String gelen; 
char harf; 


void setup(){
  BTL.begin(9600);
  Serial.begin(9600);
  mp3Player.begin(115200);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop(){

  bt_veri_oku();
 
}

void bt_veri_oku(){ //
        while(BTL.available()){
          harf = BTL.read();
          gelen.concat(harf);
              if(harf == '#'){ // if end of message received
                gelen = gelen.substring(0,gelen.indexOf('#'));
                Yak_Oku(gelen);
                Serial.print(gelen); //display message and 
                gelen = ""; //clear buffer
                Serial.println();
              }
        }
}

void Yak_Oku(String deger){

      int sira = deger.toInt();
      //ilgili led 
      leds[sira] = CRGB::Green;
      FastLED.show();
      myDFPlayer.play(sira);  //Play the first mp3
 

}
