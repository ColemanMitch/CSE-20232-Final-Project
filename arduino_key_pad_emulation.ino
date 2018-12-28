#include <Mouse.h>
#include <Keyboard.h>

/* Arduino Keypad Emulation 
 *  
 *  
 *
 * By: Cole Mitchell
 *      Team C'nior
 *      Fall 2017
 */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                              LIBRARY
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                             VARIABLES
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int horzPin = A1;                                                                                 // Analog output of horizontal joystick pin
int vertPin = A0;                                                                                 // Analog output of vertical joystick pin
int selPin = 8;                                                                                   // select button pin of joystick

int vertZero, horzZero;                                                                           // Stores the initial value of each axis, usually around 512
int vertValue, horzValue;                                                                         // Stores current analog output of each axis
const int sensitivity = 100;                                                                      // Higher sensitivity value = slower mouse, should be <= about 500
int mouseClickFlag = 0;


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                              SETUP
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(horzPin, INPUT);                                                                        // Set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT);                                                                         // set button select pin as input
  digitalWrite(selPin, HIGH);                                                                     // Pull button select pin high
  delay(1000);                                                                                    // short delay to let outputs settle
  vertZero = analogRead(vertPin);                                                                 // get the initial values
  horzZero = analogRead(horzPin);                                                                 // Joystick should be in neutral position when reading these

}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                            MAIN LOOP
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  vertValue = analogRead(vertPin) - vertZero;                                                     // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;                                                     // read horizontal offset

//  Serial.print("x ");
//  Serial.println(horzValue);
//  Serial.print("y ");
//  Serial.println(vertValue);

if (vertValue >= 400) { // if greater than 400
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_DOWN_ARROW); 
} 
else if(vertValue <= -400) { // if less than -400
      Keyboard.release(KEY_UP_ARROW); 
      Keyboard.press(KEY_DOWN_ARROW); 
}
else { // else
      Keyboard.release(KEY_DOWN_ARROW); 
      Keyboard.release(KEY_UP_ARROW); 
}

if (horzValue >= 400) { // if greater than 400
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW); 
} 
else if(horzValue <= -400) { // if less than -400
      Keyboard.release(KEY_RIGHT_ARROW); 
      Keyboard.press(KEY_LEFT_ARROW); 
}
else { // else
      Keyboard.release(KEY_RIGHT_ARROW); 
      Keyboard.release(KEY_LEFT_ARROW); 
}

if ((digitalRead(selPin) == 0) && (!mouseClickFlag))                                            // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Keyboard.press(KEY_RETURN);                                                                    // press ENTER key
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag))                                               // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Keyboard.release(KEY_RETURN);                                                                    // release ENTER key
  }
}
