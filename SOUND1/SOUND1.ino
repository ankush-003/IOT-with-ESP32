// #include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

//const int SD_pin = 6;  //example uses hardware SS pin 53 on Mega2560
//Sd2Card card;

TMRpcm audio;   // create an object for use in this sketch

//recoring & playing
int rec_pin = A0;
boolean can_press_1 = true;
boolean can_press_2 = true;
int button_1 = 2;
int button_2 = 7;
boolean _recording = false;
boolean _playing = false;


void setup() {
 
 Serial.begin(9600);
 while (!Serial) {
   // wait for serial port to connect. Needed for native USB port only
 }
 Serial.println("Serial connected");

 //Set the SD card
/*  if (!SD.begin(SD_pin)) {
   Serial.println("SD not OK");
   return;
 }else{
   Serial.println("SD OK"); 
 }
 audio.CSPin = SD_pin;
 */
 //recording & playing
 /* audio.setVolume(7); //volume
 audio.quality(1);
 audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
 pinMode(10,OUTPUT);  //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45 */
 pinMode(rec_pin, INPUT);
 //pinMode(button_1, INPUT);
 //pinMode(button_2, INPUT);
}
void loop() {

   //button 1 (record)
   /* if (digitalRead(button_1)) {
    if (can_press_1) {
      can_press_1 = false;
      //if button 1 pressed:
      Serial.println("pressed button 1");

      if (_playing) { //stop playing
        _playing = false;
        audio.stopPlayback();
        Serial.println("stopped playback");
      } */
      
      
  if (!_recording) { //start or stop recording
        _recording = true;
        audio.startRecording("audio.wav",16000,rec_pin);
        Serial.println("started recording");
      } else {
        _recording = false;
        audio.stopRecording("audio.wav");
        Serial.println("stopped recording");
      }

   //button 2 (play)
}