/*
 * Author: Elijah Karl
 * 
 * This program works with an Arduino Uno or equivilant, light sensing circuit that outputs an 
 * analog voltage based on light prevelance, and a common anode or common cathode 
 * 2 digit 7 segment display (with intermediate circuitry for power requirements).
 * 
 *
 */

// constants for which pins control which segment in the 7-segment display
const byte a = 10;
const byte b = 13;
const byte c = 4;
const byte d = 6;
const byte e = 12;
const byte f = 11;
const byte g = 5;
const byte dp = 7;
const byte ONES = 3;
const byte TENS = 2;

// for logging data only - use with EEPROM library
/*
const bool logData = 1;
const byte chipCount = 1;
const byte chipSizes[chipCount] = {4}; // kB
const byte chipFreq = 100; //kHz
int chipMemoryPointer = 0;
*/

// organizing segments into list
byte segments[8] = {a, b, c, d, e, f, g, dp};

// store combinations of segments for each number 0 - 9
bool numbers[10][7] = {{1, 1, 1, 1, 1, 1, 0}, 
                       {0, 1, 1, 0, 0, 0, 0}, 
                       {1, 1, 0, 1, 1, 0, 1}, 
                       {1, 1, 1, 1, 0, 0, 1}, 
                       {0, 1, 1, 0, 0, 1, 1}, 
                       {1, 0, 1, 1, 0, 1, 1}, 
                       {1, 0, 1, 1, 1, 1, 1}, 
                       {1, 1, 1, 0, 0, 0, 0}, 
                       {1, 1, 1, 1, 1, 1, 1}, 
                       {1, 1, 1, 1, 0, 1, 1}};

void setup() {
  // set pin modes
  pinMode(a, OUTPUT); // set pin that controls segment a to output
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  pinMode(TENS, OUTPUT); // pin that controls the 10s place enable
  pinMode(ONES, OUTPUT); // ones place enable

  if(logData){
    extEEPROM myEEPROM(kbits_4, 1, 16);
    byte i2cStat = myEEPROM.begin(extEEPROM::twiClock400kHz);
    if (i2cStat != 0){
      pinMode(13, OUTPUT);
      digitalWrite(13, 1);
    }
  }
}

void loop() { // loop reads analog value then displays the value on the 7 segment display for a period of time
  float val = analogRead(A0); // read analog data from port A0
  
  /*
  if(logData){
    
  }
  */
  
  for(int j = 0; j < 50; j++){ 
    float augmentedVal = (val / 1024) * 100 * 1.5 ;
    displayNumber(augmentedVal);
  }
}

// display driver
int displayNumber(int number){
  // calculate ones and tens value from the given integer
  byte ones = number % 10;
  byte tens = (number - ones) / 10;
  
  // ----- tens place display ------ //
  
  // turn off all segments
  for(byte i = 0; i < 8; i++){
    digitalWrite(segments[i], 0);
  }
  
  // delay to prevent bleeding
  delay(1);
  
  // disable ones place, enable tens place (segment digits are enabled with LOW and diabled with HIGH)
  digitalWrite(ONES, 1);
  digitalWrite(TENS, 0);

  // turn on all needed segments
  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], numbers[tens][i] * 1);
  }
  
  // leave number displayed for a short time
  delay(5);
  
  // ----- ones place ----- //
  // reset all segments
  for(byte i = 0; i < 8; i++){
    digitalWrite(segments[i], 0);
  }
  
  // enable ones, diable tens
  digitalWrite(TENS, 1);
  digitalWrite(ONES, 0);
  
  // enable segments needed for number display
  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], numbers[ones][i] * 1);
  }
  
  // leave ones place enabled for a short time
  delay(5);
  
  // turn off all segments
  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], 0);
  }
  
  // disable digits
  digitalWrite(TENS, 1);
  digitalWrite(ONES, 1);

  //delay(5);
  return 0;
}
