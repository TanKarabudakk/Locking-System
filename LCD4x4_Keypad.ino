

#include<Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

using namespace std;

const byte Rows = 4;
const byte Columns = 4;

char Keydata[Rows][Columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte RowPins[Rows] = {9, 8, 7, 6};
byte ColumnPins[Columns] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(Keydata), RowPins, ColumnPins, Rows, Columns);

LiquidCrystal_I2C lcd(0x27,20,4);
Servo myservo;
char Password[4];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*char customKey = customKeypad.getKey();

  if(customKey){
    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(2,1);
    lcd.print(customKey);  
  }*/                   
  lcd.init();           // initialize the lcd 
  lcd.backlight();
  lcd.clear();          // Clear the LCD screen

  lcd.setCursor(3, 0);
  lcd.print("Password System");
  lcd.setCursor(2, 1);
  lcd.print("Choose Operation");
  lcd.setCursor(3, 2);
  lcd.print("*");
  lcd.setCursor(15, 2);
  lcd.print("#");
  lcd.setCursor(2, 3);
  lcd.print("New");
  lcd.setCursor(13, 3);
  lcd.print("Enter");

  char customKey = 0;

  // Wait for a key press
  while (!customKey) {
      customKey = customKeypad.getKey();
  }

  if (customKey == '*') {
      lcd.clear();
      lcd.setCursor(1, 1);
      lcd.print("Enter new password:");
      lcd.setCursor(3, 2);
      int index = 0;
      while (index < 4) { //How to enter a 4 digit password
        char key = customKeypad.getKey();
        if (key) {
            Password[index] = key;
            lcd.print('*'); // Display asterisk instead of the actual character
            index++;
        }
      }
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Password Set");
      delay(2000); // Display the "Password Set" message for 2 seconds
      lcd.clear();
  } else if (customKey == '#') {
      /*lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("Password is " + String(Password[0]) + Password[1] + Password[2] + Password[3]);
      delay(2000); 
      lcd.clear();*/
      char PasswordAttempt[4];
      lcd.clear();
      lcd.setCursor(1, 1);
      lcd.print("Enter password:");
      lcd.setCursor(3, 2);
      int index = 0;
      while (index < 4) { //How to enter a 4 digit password
        char key = customKeypad.getKey();
        if (key) {
            PasswordAttempt[index] = key;
            lcd.print('*'); // Display asterisk instead of the actual character
            index++;
        }
      }
      bool match = false;
      for(int i = 0; i < 4; i++){
        if(Password[i] == PasswordAttempt[i]){
          match = true;
        }else{
          match = false;
        }
        if(match == false){
          break;
        }
      }
      
      if(match == true){
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Correct :D");
        myservo.write(0);
        delay(5000);
        myservo.write(90); 
        lcd.clear();
      }else if(match == false){
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Not Correct :(");
        delay(2000); 
        lcd.clear();
      }else{
        //WTF
      }
  }

}
