#include <JC_Button.h>

//#define DEBUG

//ENTER YOUR PIN, USERNAME, PASSWORD HERE
#define KEYDE //comment if you do not need german keyboard layout
#define USERNAME "username"
#define PASSWORD "password"
//first button and count
#define PIN_D1_BUTTON b1
#define PIN_D1_COUNT 1
//second button and count
#define PIN_D2_BUTTON b2
#define PIN_D2_COUNT 2
//third button and count
#define PIN_D3_BUTTON b3
#define PIN_D3_COUNT 3
//fourth button and count
#define PIN_D4_BUTTON b4
#define PIN_D4_COUNT 4
//delay for pin input to reset or accept in milliseconds
#define PIN_DELAY 2500
//delay for auto lock if not used in milliseconds
#define LOCK_DELAY 3600000 //one houre

//define GPIOs for the buttons
#define B1 5
#define B2 2
#define B3 1
#define B4 0

//define states LOCK
#define LOCK_CLOSE 1
#define LOCK_OPEN 0

//define states PIN
#define PIN_WRONG 0
#define PIN_D1 10
#define PIN_D2 20
#define PIN_D3 30
#define PIN_D4 40
#define PIN_OK 50

//set debug specific settings
#ifdef DEBUG
  #define LOCK_DELAY 10000
#endif

#ifdef KEYDE
  #include "DigiKeyboardDe.h"
  #define DK DigiKeyboardDe
#else
  #include "DigiKeyboard.h"
  #define DK DigiKeyboard
#endif

//set global vars
bool lock = true;
unsigned long buttonTime, lockTime;
int pin = 0;
int d1count = PIN_D1_COUNT;
int d2count = PIN_D2_COUNT;
int d3count = PIN_D3_COUNT;
int d4count = PIN_D4_COUNT;

//define the buttons
#ifdef B1
Button b1(B1);
#endif
#ifdef B2
Button b2(B2);
#endif
#ifdef B3
Button b3(B3, 25, false, false);
#endif
#ifdef B4
Button b4(B4);
#endif

void setup() {
  //init the button objects
  #ifdef B1
  b1.begin(); 
  #endif
  #ifdef B2
  b2.begin(); 
  #endif
  #ifdef B3
  b3.begin(); 
  #endif
  #ifdef B4
  b4.begin(); 
  #endif

  //init usb-keyboard
  DK.sendKeyStroke(0);
}


void loop() {
  // read the button
  #ifdef B1
  b1.read();
  #endif
  #ifdef B2
  b2.read();
  #endif
  #ifdef B3
  b3.read();
  #endif
  #ifdef B4
  b4.read();
  #endif

  // do state machine LOCK
  switch (lock) {
    case LOCK_CLOSE: //1

      //reset PIN machine if no input for PIN_DELAY Milliseconds
      if ( millis() - buttonTime >= PIN_DELAY && pin != PIN_WRONG ) {
        d1count = PIN_D1_COUNT;
        d2count = PIN_D2_COUNT;
        d3count = PIN_D3_COUNT;
        d4count = PIN_D4_COUNT;
        if ( pin == PIN_OK ) {
          #ifdef DEBUG
            DK.sendKeyStroke(0);
            DK.println(F("unlock"));
          #endif
          buttonTime = millis();
          pin = PIN_WRONG;
          lock = LOCK_OPEN;
          led();
        } else {
          #ifdef DEBUG
            DK.sendKeyStroke(0);
            DK.println(F("reset"));
          #endif
          lock = LOCK_CLOSE;
          pin = PIN_WRONG;
          led();
          led();
        }
      }
      
      // do state machine PIN
      switch (pin) {
        case PIN_WRONG: //0
          if ( PIN_D1_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("d1s"));
              DK.println(d1count);
            #endif
            --d1count;
            #ifdef DEBUG
              DK.println(d1count);
            #endif  
            if ( d1count == 0 ) {
              d1count = PIN_D1_COUNT;
              pin = PIN_D2;
              #ifdef DEBUG
                DK.sendKeyStroke(0);
                DK.println(F("d1f"));
              #endif
            } else {
              pin = PIN_D1;
            }
          } else if ( PIN_D2_BUTTON.wasReleased() || PIN_D3_BUTTON.wasReleased() || PIN_D4_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("not d1"));
            #endif
            d1count = PIN_D1_COUNT;
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_WRONG
        case PIN_D1: //10
          if ( PIN_D1_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("d1c"));
            #endif
            --d1count;
            #ifdef DEBUG
              DK.println(d1count);
            #endif
            if ( d1count == 0 ) {
              d1count = PIN_D1_COUNT;
              pin = PIN_D2;
              #ifdef DEBUG
                DK.sendKeyStroke(0);
                DK.println(F("d1f"));
              #endif
            }
          } else  if ( PIN_D2_BUTTON.wasReleased() || PIN_D3_BUTTON.wasReleased() || PIN_D4_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("not d1c"));
            #endif
            d1count = PIN_D1_COUNT;
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_D1
        case PIN_D2: //20
          if ( PIN_D2_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("d2c"));
            #endif
            --d2count;
            #ifdef DEBUG
              DK.println(d2count);
            #endif
            if ( d2count == 0 ) {
              d2count = PIN_D2_COUNT;
              #ifdef DEBUG
                DK.sendKeyStroke(0);
                DK.println(F("d2f"));
              #endif
              pin = PIN_D3;
            }
          } else  if ( PIN_D1_BUTTON.wasReleased() || PIN_D3_BUTTON.wasReleased() || PIN_D4_BUTTON.wasReleased() ){
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("not d2"));
            #endif
            d2count = PIN_D2_COUNT;
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_D2
        case PIN_D3: //30
          if ( PIN_D3_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("d3c"));
            #endif
            --d3count;
            #ifdef DEBUG
              DK.println(d3count);
            #endif
            if ( d3count == 0 ) {
              d3count = PIN_D3_COUNT;
              #ifdef DEBUG
                DK.sendKeyStroke(0);
                DK.println(F("d3f"));
              #endif
              pin = PIN_D4;
            }
          } else  if ( PIN_D1_BUTTON.wasReleased() || PIN_D2_BUTTON.wasReleased() || PIN_D4_BUTTON.wasReleased() ){
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("not d3"));
            #endif
            d3count = PIN_D3_COUNT;
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_D3
        case PIN_D4: //40
          if ( PIN_D4_BUTTON.wasReleased() ) {
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("d4c"));
            #endif
            --d4count;
            #ifdef DEBUG
              DK.println(d4count);
            #endif
            if ( d4count == 0 ) {
              d4count = PIN_D4_COUNT;
              #ifdef DEBUG
                DK.sendKeyStroke(0);
                DK.println(F("d4f"));
              #endif
              pin = PIN_OK;
            }
          } else if ( PIN_D1_BUTTON.wasReleased() || PIN_D2_BUTTON.wasReleased() || PIN_D3_BUTTON.wasReleased() ){
            buttonTime = millis();
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("not d4"));
            #endif
            d4count = PIN_D4_COUNT;
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_D4
        case PIN_OK:
          if ( PIN_D1_BUTTON.wasReleased() || PIN_D2_BUTTON.wasReleased() || PIN_D3_BUTTON.wasReleased() || PIN_D4_BUTTON.wasReleased() ){
            #ifdef DEBUG
              DK.sendKeyStroke(0);
              DK.println(F("too much"));
            #endif
            lock = LOCK_CLOSE;
            pin = PIN_WRONG;
          }
          break; //PIN_OK
      } //end state machine PIN
      
      break; //LOCK_CLOSE
    case LOCK_OPEN: //0

      if ( millis() - buttonTime >= LOCK_DELAY ) {
        #ifdef DEBUG
        DK.sendKeyStroke(0);
        DK.println(F("auto lock"));
        #endif
        led();
        led();
        led();
        lock = LOCK_CLOSE;
      }

      #ifdef B1
      if ( b1.wasReleased() ) {
        buttonTime = millis();
        DK.sendKeyStroke(0);
        DK.println(F(PASSWORD));
        DigiKeyboard.delay(250);
      }
      #endif

      #ifdef B2
      if ( b2.wasReleased() ) {
        buttonTime = millis();
        DK.sendKeyStroke(0);
        DK.print(F(USERNAME));
        DK.write('\t');
        DK.println(F(PASSWORD));
        DigiKeyboard.delay(250);
      }
      #endif

      #ifdef B3
      if ( b3.wasReleased() ) {
        buttonTime = millis();
        DK.sendKeyStroke(0);
        DK.println(F(USERNAME));
        DigiKeyboard.delay(200);
        DK.println(F(PASSWORD));
        DigiKeyboard.delay(250);
      }
      #endif
      
      #ifdef B4
      if ( b4.wasReleased() ) {
        DK.sendKeyStroke(0);
        #ifdef DEBUG
          DK.println("lock");
        #endif
        led();
        DigiKeyboard.delay(250);
        lock = LOCK_CLOSE;
      }
      #endif
      
      break; //LOCK_OPEN
  } //end state machine LOCK

} //end mail loop

void led() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  DigiKeyboard.delay(250);
  digitalWrite(1, LOW);
  DigiKeyboard.delay(500);
  pinMode(1, INPUT);
}
