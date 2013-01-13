/*    DragonBone - RPG Dice Roller 
      Janary 15, 2013
      Written by; Wade Neuwirth 
      
      1. button1 on pin 12 is an interrupt that rolls the dice
      2. The 'mode' is checked against the potentiometer
      3. 2 dice are rolled when 4,6,8 and 10 sided dice are rolled. 1 dice is rolled when rolling a D12 or a D20
      4. Deice are animated on the 7 segment display and additional LED. Piezo sounds.
      5. The value is returned to the 7 segment display
      6. Star Wars theme played on critical success
      7. Imperial March played on critical failure (if I can make this work)
      8. 6 Additional LED that denote the dice mode and show animations 
      
      
      */

int latchPin = 4;  // Pin connected to Pin 12 of 74HC595 (Latch)
int dataPin  = 3;  // Pin connected to Pin 14 of 74HC595 (Data)
int clockPin = 2;  // Pin connected to Pin 11 of 74HC595 (Clock)

int led1 = 5;
int led2 = 6;
int led3 = 7;
int led4 = 8;
int led5 = 9;
int led6 = 10;

int button1 = 12;
int pot = A1;
// DO NOT CONNECT A0! This is the dice rollers random seed


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
  // Setup potentiometer
}

void loop(){

  int result = random(1,99);
  displayNum(result);
  Serial.println(result);
  delay(2000);
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
