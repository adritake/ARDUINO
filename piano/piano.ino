/*
 * Simple program to play the piano with a buzzer and a remote controller
 */


#include <IRremote.h>
#include <NewTone.h>


//Infrared pin
#define IR_PIN 2

//Buzzer pin
#define BUZZ_PIN 8


//Notes IR
#define DO_IR  16724175
#define RE_IR  16718055
#define MI_IR  16743045
#define FA_IR  16716015
#define SOL_IR 16726215
#define LA_IR  16734885
#define SI_IR  16728765

//Notes Hz
#define DO_HZ  261
#define RE_HZ  294
#define MI_HZ  330
#define FA_HZ  349
#define SOL_HZ 392
#define LA_HZ  440
#define SI_HZ  494


//Default value of the IR signal
#define DEFAULTIR 4294967295

//IR variables
IRrecv irrecv(IR_PIN);
decode_results results;


void setup() {
  
  Serial.begin(9600);

  irrecv.enableIRIn(); 
  
}

void loop() {
  
  unsigned long ircode;

  if (irrecv.decode(&results)){ 
    irrecv.decode(&results);

    ircode = results.value;

    switch(ircode){
      case DO_IR:
        NewTone(BUZZ_PIN,DO_HZ,500);
        break;
      case RE_IR:
        NewTone(BUZZ_PIN,RE_HZ,500);
        break;
      case MI_IR:
        NewTone(BUZZ_PIN,MI_HZ,500);
        break;
      case FA_IR:
        NewTone(BUZZ_PIN,FA_HZ,500);
        break;
      case SOL_IR:
        NewTone(BUZZ_PIN,SOL_HZ,500);
        break;
      case LA_IR:
        NewTone(BUZZ_PIN,LA_HZ,500);
        break;
      case SI_IR:
        NewTone(BUZZ_PIN,SI_HZ,500);
        break;
    }
   
    irrecv.resume();
    Serial.print(String(ircode)+ "\n");
  }

}
