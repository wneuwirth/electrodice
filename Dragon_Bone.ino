/*    DragonBone - RPG Dice Roller 
      Janary 15, 2013
      Written by; Wade Neuwirth 
      
      1. button1 on pin 12 is an interrupt that rolls the dice
      2. The 'mode' is checked against the potentiometer
      3. 2 dice are rolled when 4,6,8 and 10 sided dice are rolled. 1 dice is rolled when rolling a D12 or a D20
      4. Deice are animated on the 7 segment display and additional LED. Piezo sounds.
      5. The value is returned to the 7 segment display
      6. Star Wars theme played on critical success
        a. or Another MacGyver theme
        b. or A-Team theme
        c. or Bond theme 
        d. or Happy Days theme
      7. Imperial March played on critical failure (if I can make this work)
        a. or Another One Bites the Dust
        b. or The Good, the Bad and The Ugly
        c. or Benny Hill theme
        d. or Looney Tunes theme
      8. Randomly will play: Futurama theme, The Force theme, Danger Mouse (/5)
      9. 6 Additional LED that denote the dice mode and show animations - wired tot he potentiometer
      
      
      */


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
int pot = A1;

int diceMode = 1;
int diceResult = 0;

byte isCrit = 0;
byte isFumble = 0;

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

  int die1 = 0;
  int die0 = 0;
  int diceTotal = 0;
  byte maxRollValue = 0;
  byte minRollvalue = 1;

  switch (diceMode){
    case 1:
      maxRollValue = 8;
      minRollvalue = 2;
      die1= random(1,(4+1));
      die0= random(1,(4+1));
      diceTotal = ((die1 * 10) + die0);
    break;
     case 2:
      minRollvalue = 2;
      maxRollValue = 12;
      die1= random(1,(6+1));
      die0= random(1,(6+1));
      diceTotal = ((die1 * 10) + die0);
    break;
     case 3:
      maxRollValue = 16;
      minRollvalue = 2;
      die1= random(1,(8+1));
      die0= random(1,(8+1));
      diceTotal = ((die1 * 10) + die0);
    break;   
    case 4:
      maxRollValue = 20;
      minRollvalue = 2;
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
  
  setMode();  // Set's the dice mode from 1 - 6
  diceResult = rollDice();  // Roll the dice
  displayNum(diceResult); // Display the result
  delay(1000);
  
}
