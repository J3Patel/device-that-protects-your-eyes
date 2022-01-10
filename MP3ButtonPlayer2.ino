/**
 * \file MP3ButtonPlayer2.ino
 *
 * \brief Example sketch of using the MP3Shield Arduino driver using buttons,
 * with arduino recommended(simpler) debounce library
 * \remarks comments are implemented with Doxygen Markdown format
 *
 * \author Michael P. Flaga
 *
 * This sketch demonstrates the use of digital input pins used as buttons as 
 * NEXT, PLAY and STOP to control the tracks that are to be played.
 * Where PLAY or STOP will begin or cancel the stream of track000.mp3 through 
 * track999.mp3, as indexed by NEXT, begining with 0.

 * \note Use this example uses the bounce2 library to provide debouncing fuctions. Advocated by Arduino's website at http://playground.arduino.cc/code/bounce
 */

// libraries
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>


SdFat sd;
int chairSolenoid = 4;
int buzzer = 6;
int interval = 1200000; // 20 minutes



SFEMP3Shield MP3player;


void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(chairSolenoid, OUTPUT);
  
  digitalWrite(chairSolenoid, LOW);
  digitalWrite(buzzer, LOW);
  
  Serial.begin(115200);

  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

  MP3player.begin();
  MP3player.setVolume(10,10);

  MP3player.available();
  

  


}

void loop() {

// Below is only needed if not interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) \
    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )
    
  
#endif
  
  delay(interval);
  playAlarm();
  delay(2000);
  MP3player.stopTrack();
  moveChairUp();
  delay(5000);
  playRelax();
  delay(25000);
  MP3player.stopTrack();
  moveChairDown();

}

void moveChairUp() {
  digitalWrite(chairSolenoid, HIGH);
}

void moveChairDown() {
  digitalWrite(chairSolenoid, LOW);
}

void playAlarm() {
  MP3player.playMP3("alarm.mp3");
}

void playRelax() {
  MP3player.playMP3("med.mp3");
}
