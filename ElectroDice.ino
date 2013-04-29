/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "constants.h"

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);



int pot1 = A1;
int pot2 = A2;

const unsigned int DEBOUNCE_TIME = 500;
const unsigned int REFRESH_TIME = 4000;

byte buttonInterrupt = 0;
unsigned int counter = 0;
int buttonState = 0;
int buttonPin = 2;

static unsigned long last_interrupt_time = 0;


int diceMode;
int diceAmt;
int dice;
int rolls = 0;
int curRoll = 0;
int lastRoll = 0;

byte isCrit = 0;
byte isFumble = 0;
int numCrit = 0;
int numFumble = 0;

void setup()   {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);

  display.begin();
  display.setContrast(75);
  display.clearDisplay();
  display.drawBitmap(20, 0, galemp , 48, 38, BLACK);
  display.display();


  // Set the random seed for the dice roller. 
  randomSeed(analogRead(A0));
   
  //char *song_start = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
  //char *song_start = "SWEnd:d=4,o=5,b=225:2c,1f,2g.,8g#,8a#,1g#,2c.,c,2f.,g,g#,c,8g#.,8c.,8c6,1a#.,2c,2f.,g,g#.,8f,c.6,8g#,1f6,2f,8g#.,8g.,8f,2c6,8c.6,8g#.,8f,2c,8c.,8c.,8c,2f,8f.,8f.,8f,2f";
  //char *song_start = "Star Trek:d=4,o=5,b=63:8f.,16a#,d#.6,8d6,16a#.,16g.,16c.6,f6";
  //char *song_start = "007:d=4,o=5,b=320:c,8d,8d,d,2d,c,c,c,c,8d#,8d#,2d#,d,d,d,c,8d,8d,d,2d,c,c,c,c,8d#,8d#,d#,2d#,d,c#,c,c6,1b.,g,f,1g";
  char *song_start = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";
  
  play_rtttl(song_start);
 
  delay(2000);
  display.clearDisplay();
  
}

// Roll the dice
void rollDice(){

  isCrit = 0;
  isFumble = 0;
  
  byte die0 = 0;
  byte die1 = 0;
  
  int diceTotal = 0;
  byte maxRollValue = 0;
  byte minRollvalue = 1;

  switch (diceMode){ ///////Made it here
    case 1:
      maxRollValue = (diceMode * diceAmt) * 4;
      minRollvalue = (diceAmt * 1);
      die1= random(1,(4+1));
      die0= random(1,(4+1));
      diceTotal = ((die1 * 10) + die0);
    break;
     case 2:
      maxRollValue = 66;
      minRollvalue = 11;
      die1= random(1,(6+1));
      die0= random(1,(6+1));
      diceTotal = ((die1 * 10) + die0);
    break;
     case 3:
      maxRollValue = 88;
      minRollvalue = 11;
      die1= random(1,(8+1));
      die0= random(1,(8+1));
      diceTotal = ((die1 * 10) + die0);
    break;
    case 4:
      maxRollValue = 0;
      minRollvalue = 1;
      die1= random(0,(9+1));
      die0= random(0,(9+1));
      diceTotal = ((die1 * 10) + die0);
    break;
    case 5:
      maxRollValue = 12;
      minRollvalue = 1;
      die1= random(1,(12+1));
      diceTotal = die1;
    break;
    case 6:
      maxRollValue = 20;
      minRollvalue = 1;
      die1= random(1,(20+1));
      diceTotal = die1;
    break;
  
  }

// Check is the user rolled a crit
if (diceTotal == maxRollValue) {

  isCrit = 1;
  numCrit++;

}
else if (diceTotal == minRollvalue) {

  isFumble = 1;
  numFumble++;
  
}

// Display here

}  

void loop() {

  
  

  // Set the dice mode
  setDiceMode();
  setDiceAmt();

  buttonPress();
 
  setStatScreen();
  delay(2000);
  
  buttonPress();
  
  setResultScreen();
  delay(2000);
  
  buttonPress();
 
}


void buttonPress() {

  display.clearDisplay();
  
  int buttonPressed = digitalRead(buttonPin);
  
  if (buttonPressed == 1){
  
    rolls++;
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("PRESSED");
    display.display();
    delay(2000);
  
  }
  


}

void setResultScreen() {

  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(diceAmt);
  display.print("  ");
  display.print(diceAmt);   
  display.print("\n");
  display.print (diceMode);
  display.print("  ");
  display.print (diceMode);
    display.print("\n");
  display.print (diceMode);
  display.print("  ");
  display.print (diceMode);
  display.display();

}


void setStatScreen() {

   // text display tests

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
//  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.print("D:");
//  display.setTextColor(BLACK); // 'inverted' text
  display.print(dice);
  display.print("\n");
//  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.print("#:");
//  display.setTextColor(BLACK); // 'inverted' text
  display.print(diceAmt);
  display.setCursor(4,24);
  display.setTextSize(3);
  display.print(84);
  display.setCursor(34,0);
  display.setTextSize(1);
  display.print("R:");
  display.print(rolls);
  display.display();
  display.clearDisplay();


}

void count() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {
   buttonState = 1;
  }
  last_interrupt_time = interrupt_time;
  
}


// Set the dice mode
//
void setDiceMode(){
  
  // Determine the dice mode
  /*
  Mode:
  1 = d4
  2 = d6
  3 = d8
  4 = d10
  5 = d12
  6 = d20
  7 = d100
  */
  
  
  int potValue = analogRead(pot1);
  diceMode = map(potValue,0,1023,7,1);
    
  switch(diceMode)
    {
      case 1:
        dice = 4;
        break;
      case 2:
        dice = 6;
        break;
      case 3:
        dice = 8;
        break;
      case 4:
        dice = 10;
        break;
      case 5:
        dice = 12;
        break;
      case 6:
        dice = 20;
        break;
      case 7:
        dice = 100;
        break;  
      default:
        dice = 6;
    }
 

}


// Set the dice mode
//
void setDiceAmt(){
    
  int potValue = analogRead(pot2);
  diceAmt = map(potValue,0,1023,6,0);

}




















// Play RTTTL songs
// Plays song (char)
#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

 // Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

//  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

//  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

//  Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
//      Serial.print("Playing: ");
 //     Serial.print(scale, 10); Serial.print(' ');
 //     Serial.print(note, 10); Serial.print(" (");
 //     Serial.print(notes[(scale - 4) * 12 + note], 10);
 //     Serial.print(") ");
 //     Serial.println(duration, 10);
      tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(TONE_PIN);
    }
    else
    {
 //     Serial.print("Pausing: ");
 //     Serial.println(duration, 10);
      delay(duration);
    }
  }
}








