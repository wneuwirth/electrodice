/*    
      DragonBone - RPG Dice Roller 
      Janary 15, 2013
      Written by; Wade Neuwirth 
      
      1. button1 on pin 12 is an interrupt that rolls the dice
      2. The 'mode' is checked against the potentiometer
      3. 2 dice are rolled when 4,6,8 and 10 sided dice are rolled. 1 dice is rolled when rolling a D12 or a D20
      4. Deice are animated on the 7 segment display and additional LED. Piezo sounds.
      5. The value is returned to the 7 segment display
      6. Star Wars theme played on critical success
        a. or MacGyver theme
        b. or A-Team theme
        c. or Bond theme 
        d. or Happy Days theme
      7. Imperial March played on critical failure (if I can make this work)
        a. or Another One Bites the Dust
        b. or The Good, the Bad and The Ugly
        c. or Benny Hill theme
        d. or Looney Tunes theme
      8. Randomly will play: Futurama theme, The Force theme, Danger Mouse (1/5 chance on roll)
      9. 6 Additional LED that denote the dice mode and show animations - wired to t he potentiometer  
      
      
List of songs to choose from
//char *song = "Imperial March:d=4,o=5,b=180:a,8p,a,8p,a,8p,8f,8c6,a,8p,8f,8c6,a,2p,e6,8p,e6,8p,e6,8p,f6,8c#6,g#,8p,8f,8c6,a";
//char *song = "The Force:d=4,o=5,b=180:d,g,g,g,a,a,8a#,8c6,8a#,a#,a#,d,8d,8p,d,g,g,a,a#,d,8a#,8g,8d6,c6,c6,c6,c6";
//char *song = "Futurama:d=8,o=5,b=125:e,4e,4e,a,4a,4d,4d,e,4e,4e,e,4a,4g#,4d,d,f#,f#,4e,4e,e,4a,4g#,4b,16b,16b,g,g,f#,f#,4e,4e,a,4a,4d,4d,e,g,f#,4e,e,4a,4g#,4d,d,f#,f#,4e,4e,e,4a,4g#,4b,16b,16b,g,g,f#,f#,p,16e,16e,e,d#,d,d,c#,c#";
//char *song = "Danger Mouse:d=4,o=5,b=355:a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2d6,p,8a4,8p,d,p,a.,8a,2a#.,8a#4,8p,d#,2p,a#,2a#,2f#,2d#,a#.,8a#,2b.,8b4,8p,e,2p,b,2b,2g,2e,b.,8d6,1e.6,e6,8e6,8e";
//char *song = "Benny Hill Theme:d=16,o=5,b=125:8d.,e,8g,8g,e,d,a4,b4,d,b4,8e,d,b4,a4,b4,8a4,a4,a#4,b4,d,e,d,4g,4p,d,e,d,8g,8g,e,d,a4,b4,d,b4,8e,d,b4,a4,b4,8d,d,d,f#,a,8f,4d,4p,d,e,d,8g,g,g,8g,g,g,8g,8g,e,8e.,8c,8c,8c,8c,e,g,a,g,a#,8g,a,b,a#,b,a,b,8d6,a,b,d6,8b,8g,8d,e6,b,b,d,8a,8g,4g";
//char *song = "Another One Bites The Dust:d=16,o=4,b=112:d5,c5,8a,8p,8a,8p,4a.,p,a,a,p,8a,8c5,a,4d5,8p.,d5,c5,8a,8p,8a,8p,4a.,p,a,a,p,8a,8c5,a,4d.5,p,d5,c5,8a,8p,8a,8p,4a.,p,a,a,p,8a,8c5,a,4d5,8p.,d5,c5,8a,8p,8a,8p,4a.,p,a,a,p,8a,8c5,a,4d.5";
//char *song = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *song = "Happy Days:d=4,o=5,b=200:c,c,e,g,a,8b,a.,p,d,d,f,a,b,8c6,b.,p,e,e,g,b,c6,8d6,c.6,p,8a,8a,8p,8b,2p,8a,8a,8p,8b,2p,b,b,c6,8c#6,d6";
//char *song = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *song = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
//char *song = "MacGyver:d=4,o=6,b=150:8b4,8e5,8a5,8b5,a5,8e5,8b4,8p,8e5,8a5,8b5,8a5,8e5,b4,8p,8e5,8a5,8b5,a5,8e5,8b4,8p,8a5,8d,8c,8d,8c,8b5,8a5,8b4,8e5,8a5,8b5,a5,8e5,8b4,8p,8e5,8a5,8b5,8a5,8e5,b4,8p,8e5,8a5,8b5,a5,8e5,8b4,8p,8a5,8d,8c,8d,8c,8b5,8a5,b5,8p,2b5,8p,b5,8p,a5,d.,b5,8p,2b5,8p,8b5,8p,2a5,p,8c,8c,8c,8c,8c,8c,2b5,16p,8f#5,8a5,8p,2g5,8p,8c,8c,8p,b5,8a5,8b5,8a5,8g5,8p,e,2a5,16p,8c,8c,8p,2b5,8p,8f#5,8a5,8p,2g5,8p,8c,8c,8p,4b5,8a5,8b5,8a5,8g5,8p,4e,2a5,2b5,32p,8c,8b5,8a5,c,8b5,8a5,8d,8c,8b5,d,8c,8b5,e,8d,8e,f#,b5,g,8p,f#,f,b5,8g,8e,8b5,8f#,8d,8a5,8e,8c,8g5,8d,8b5,8g5,8c,8e5,8b5,8d5,8c,8b5,8a5,8g5,a#5,a5,8g,8g5,8d,8g5,8d#,8d#5,8a#5,8a5,8g5,8g4,8d5,8g4,8d#5,8g4,8a#4,8a4,8g4,8g4,8g4,8g4,8g4,8g4,8g4";
//char *song = "dualingbanjos:d=4,o=5,b=200:8c#,8d,e,c#,d,b4,c#,d#4,b4,p,16c#6,16p,16d6,16p,8e6,8p,8c#6,8p,8d6,8p,8b,8p,8c#6,8p,8a,8p,b,p,a4,a4,b4,c#,d#4,c#,b4,p,8a,8p,8a,8p,8b,8p,8c#6,8p,8a,8p,8c#6,8p,8b";
//char *song = "Popeye:d=4,o=5,b=140:16g.,16f.,16g.,16p,32p,16c.,16p,32p,16c.,16p,32p,16e.,16d.,16c.,16d.,16e.,16f.,g,8p,16a,16f,16a,16c6,16b,16a,16g,16a,16g,8e,16g,16g,16g,16g,8a,16b,32c6,32b,32c6,32b,32c6,32b,8c6";

      
    To play song:
  - Assign the corect char to the song variable
  - play_rtttl(song);
      
*/

// Definae all notes and variables for music effects (piezo)
#define OCTAVE_OFFSET 0
#define TONE_PIN 11

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};


// DO NOT CONNECT A0! This is the dice rollers random seed

int latchPin = 4;  // Pin connected to Pin 12 of 74HC595 (Latch)
int dataPin  = 3;  // Pin connected to Pin 14 of 74HC595 (Data)
int clockPin = 2;  // Pin connected to Pin 11 of 74HC595 (Clock)

int led1 = 5;
int led2 = 6;
int led3 = 7;
int led4 = 8;
int led5 = 10;
int led6 = 9;

int button1 = 12;
int buttonState;             // the current reading from the input pin
long debounceDelay = 300;    // the debounce time; increase if the output flickers

// Potentiometer
int pot = A1;

int diceMode = 1;
int diceResult = 0;

byte isCrit = 0;
byte isFumble = 0;

char *song_crit = "The Force:d=4,o=5,b=180:d,g,g,g,a,a,8a#,8c6,8a#,a#,a#,d,8d,8p,d,g,g,a,a#,d,8a#,8g,8d6,c6,c6,c6,c6";
char *song_fumble = "Imperial March:d=4,o=5,b=180:a,8p,a,8p,a,8p,8f,8c6,a,8p,8f,8c6,a,2p,e6,8p,e6,8p,e6,8p,f6,8c#6,g#,8p,8f,8c6,a";


//  These define the characters that appear on the LCD. Each 1 represents
//  a segment in the 7 segment display
byte digits[] = {
B00111111, B00000110, B01011011, B01001111, B01100110, B01101101,
B01111100, B00000111, B01111111, B01101111
};

// Set to 1 to enable Serial
int DEBUG = 1;

//holder for infromation you're going to pass to shifting function
byte data = 0;

// set up
void setup() {

  if(DEBUG) {
 
    Serial.begin(9600);
    
  }
  
  // DO NOT CONNECT A0! This is the dice rollers random seed. You cannot connect this pin. 
  randomSeed(analogRead(A0));
  
  // Set up shift registers
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  // Set up LEDs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  
  // Setup button1
  pinMode(button1, INPUT);
  
  //char *start_song = "Danger Mouse:d=4,o=5,b=355:a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a.,8g,a,8a,p,8a4,8p,d,p,a,a,a#,a#,a#,a#,a#,a#,a#,c6,2d6,p,8a4,8p,d,p,a.,8a,2a#.,8a#4,8p,d#,2p,a#,2a#,2f#,2d#,a#.,8a#,2b.,8b4,8p,e,2p,b,2b,2g,2e,b.,8d6,1e.6,e6,8e6,8e";
  //play_rtttl(start_song);

}


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

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

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

  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  Serial.print("wn: "); Serial.println(wholenote, 10);


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
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone(TONE_PIN, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(TONE_PIN);
    }
    else
    {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
  }
}

// Display 2 digit number
void displayNum(int num)
{

  // get digit 0
  int dig0 = (num/10) % 10;
  
  // get digit 1
  int dig1 = num % 10;

 
    // shift out digits
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digits[dig1]);
    shiftOut(dataPin, clockPin, MSBFIRST, digits[dig0]);
    digitalWrite(latchPin, HIGH);
}

void setMode(){
  
  // Determine the dice mode
  /*
  Mode:
  1 = 2 x d4
  2 = 2 x d6
  3 = 2 x d8
  4 = 2 x d10 (represented as 0-9 (0=10))
  5 = 1 x d12
  6 = 1 x d20
  */
  
  
  int potValue = analogRead(pot);
  int potResult = map(potValue,0,1023,6,1);
  Serial.println(potResult);
  
  clearAllLED();
  
  switch (potResult){
  case 1:
  // roll 2 d4
  digitalWrite(led1, HIGH);
  diceMode = 1;
  break;
  case 2:
  // roll 2d6
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  diceMode = 2;
  break;
  case 3:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  diceMode = 3;
  break;
  case 4:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  diceMode = 4;
  break;
  case 5:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  diceMode = 5;
  break;
  case 6:
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  diceMode = 6;
  break;

  }
  

}

void clearAllLED(){

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

}

int rollDice(){

  isCrit = 0;
  isFumble = 0;
  
  int die1 = 0;
  int die0 = 0;
  int diceTotal = 0;
  byte maxRollValue = 0;
  byte minRollvalue = 1;

  switch (diceMode){
    case 1:
      maxRollValue = 44;
      minRollvalue = 11;
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

} 
else if (diceTotal == minRollvalue) {

  isFumble = 1;

} 

return diceTotal;

}

void loop(){
  
  // Set's the dice mode from 1 - 6
  setMode();  
  
  // Read the button
  buttonState = digitalRead(button1);
  
  if (buttonState == HIGH) {

    Serial.println("Button pressed");
    
    // Roll the dice
    diceResult = rollDice();  // Roll the dice
  
    // Display the result
    displayNum(diceResult); // Display the result
  
    // If it's a crit play a little tune
    if (isCrit == 1) {
  
    play_rtttl(song_crit);
    delay(100);
  
    }
  
    // If it's a fumble, play a baaaad tune
    if (isFumble == 1) {
  
    play_rtttl(song_fumble);
    delay(100);
  
    }
  
  // Put in a debounce delay
  delay(debounceDelay);
  }
  
  
}
