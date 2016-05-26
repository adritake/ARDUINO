#include <Arduino.h>
#include <NECIRrcv.h>


//Infrared pin
#define IR_PIN 4

//LED's pins
#define LED_FORWARD 2
#define LED_BACKWARD 3

//Decimal values of the remote's "+" and "-" buttoms 
#define IR_FORWARD 3927310080
#define IR_BACKWARD 4161273600

//Set up of the motor's imput
#define MOTOR_IN_1 8
#define MOTOR_IN_2 9
#define MOTOR_IN_3 10
#define MOTOR_IN_4 11


NECIRrcv ir(IR_PIN) ;

//Motor's steps
int Steps [ 8 ][ 4 ] =
   {  {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {1, 0, 0, 1}
   };

bool direction = true; // true  = forward
                       // false = backward


void setup()
{

  //Set output mode for the led pins
  pinMode(LED_FORWARD, OUTPUT);
  pinMode(LED_BACKWARD, OUTPUT);
  
  //Set output mode for the motor pins
  pinMode(MOTOR_IN_1, OUTPUT);
  pinMode(MOTOR_IN_2, OUTPUT);
  pinMode(MOTOR_IN_3, OUTPUT);
  pinMode(MOTOR_IN_4, OUTPUT);

  //Starting the infrared decoding
  ir.begin() ;
  
}


void loop()
{

  //Value of the signal received
  unsigned long ircode ;
  
  while (ir.available()) {
 
    ircode = ir.read() ;  
    
    if( ircode == IR_FORWARD ){
      
      digitalWrite(LED_FORWARD,HIGH);
      digitalWrite(LED_BACKWARD,LOW);
      direction = true;
      Run();
      
    }

    if( ircode == IR_BACKWARD ){ 
     
      digitalWrite(LED_FORWARD,LOW);
      digitalWrite(LED_BACKWARD,HIGH);
      direction = false;
      Run();
      
    }
    
  
  }
  
}

//Runs the motor for 3000 steps
void Run(){
  
  int steps = 0;
  int current_step = 0;
  
  while( steps < 3000 ){ 
    
    nextStep( current_step ) ;     
    steps++ ;
    
    if( direction )       current_step++;
    else                  current_step--;

    current_step = ( current_step + 8 ) % 8;
     
    delay (1) ;
    
   }

  
    
  
}

//It sends the next step to the motor
void nextStep( int next_step ){ 
  
  digitalWrite( MOTOR_IN_1, Steps[next_step][ 0] );
  digitalWrite( MOTOR_IN_2, Steps[next_step][ 1] );
  digitalWrite( MOTOR_IN_3, Steps[next_step][ 2] );
  digitalWrite( MOTOR_IN_4, Steps[next_step][ 3] );
  
}


