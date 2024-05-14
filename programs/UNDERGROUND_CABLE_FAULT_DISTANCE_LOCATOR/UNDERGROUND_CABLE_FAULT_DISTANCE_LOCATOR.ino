
#include <LiquidCrystal.h>                                     //include lcd library

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;    // set pins used in lcd module
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                     // define lcd pins
                                                               
//----------------------------------
int Li          = 17;
int Lii         = 1; 
int Ri          = -1;
int Rii         = -1;

//----------------------------------

int phase[3] = {7, 8, 9};                                       // define phase control pins

//----------------------------------

int SPEAKER = 10;                                               // define speaker

int numTones = 10;
int tones[] = { 988, 932, 988, 784, 784, 784, 784, 784, 784, 784};


//================================================================================================================================


 void setup()
 {
  
   for (int i = 0; i < numTones; i++)
   {
     tone(SPEAKER, tones[i]);
     delay(100);
   }
   noTone(SPEAKER);
   
 //-------------------------------------------------------------

   lcd.begin(16, 2);                                           // start the LCD library
   
   for (int i = 0; i <= 16; i++)                               // "PHYSICS PROJECT" scrolling right 
   {
     lcd.setCursor(0, 0);
     lcd.print(Scroll_LCD_Right("PHYSICS PROJECT_"));
     delay(180);
   }
   delay(2000);   
   lcd.clear();
   Clear_Scroll_LCD_Right();   
                   
   lcd.setCursor(5,0);
   lcd.print("Group:");                                     // Display  " GROUP: ROLL NO. 6 to 10"
   delay(1000);
 
   for (int i = 0; i <=15; i++)                   
   {                                                                           
     lcd.setCursor(0, 1);                                                
     lcd.print(Scroll_LCD_Left("ROLL NO. 6 to 10"));        
     delay(150);
   }
   delay(2000);
   Clear_Scroll_LCD_Left();                                  // Use if the text in the string is changed / different from before
   lcd.clear();           

   for (int i = 0; i <= 11; i++) 
   {
     lcd.setCursor(0, 0);
     lcd.print(Scroll_LCD_Right("Topic:"));                  // Display  " Topic" - scrolling right
     delay(150);
   }
   for (int i = 0; i <= 56; i++)                             // 56 is the result of the lcd = 16 column plus the length of the string 40.
   {                                                                              
     lcd.setCursor(0, 1);                                                
     lcd.print(Scroll_LCD_Left("UNDERGROUND CABLE FAULT DISTANCE LOCATOR"));              // Display  " UNDERGROUND CABLE FAULT DISTANCE LOCATOR" scrolling left
     delay(150);
   }
   Clear_Scroll_LCD_Left();                                  // Use if the text in the string is changed / different from before  
   for (int i = 16; i <= 26; i++) 
   {
     lcd.setCursor(0, 0);
     lcd.print(Scroll_LCD_Right("Topic :"));                // Display  " Topic" - scrolling left
     delay(150);
   }

   Clear_Scroll_LCD_Right();                                 // Use if the text in the string is changed / different from before
   Clear_Scroll_LCD_Left();                                  // Use if the text in the string is changed / different from before

 //-------------------------------------------------------------
 
  for (int j = 0; j < 3; j++)                                // set pin mode for phase relays 
  {                              
    pinMode(phase[j], OUTPUT);
  }
}


//================================================================================================================================
 
 void loop()
 {
  digitalWrite(phase[0], HIGH);
  delay(500);
  int dist1 = distance(analogRead(A0));
  if (dist1 == 0) {
    lcd.setCursor(0, 0);
    lcd.write("R: ");
    lcd.setCursor(3, 0);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.write("R: ");
    lcd.setCursor(3, 0);
    lcd.print(dist1);
    lcd.setCursor(4, 0);
    lcd.write(" KM");
    noTone(SPEAKER);
  }
  digitalWrite(phase[0], LOW);
  
 //-------------------------------------------------------------
  digitalWrite(phase[1], HIGH);
  delay(500);
  int dist2 = distance(analogRead(A0));
  if (dist2 == 0) {
    lcd.setCursor(8, 0);
    lcd.write("Y: ");
    lcd.setCursor(11, 0);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(8, 0);
    lcd.write("Y: ");
    lcd.setCursor(11, 0);
    lcd.print(dist2);
    lcd.setCursor(12, 0);
    lcd.write(" KM");
    noTone(SPEAKER);
  }
  digitalWrite(phase[1], LOW);
  
 //-------------------------------------------------------------
  digitalWrite(phase[2], HIGH);
  delay(500);
  int dist3 = distance(analogRead(A0));
  if (dist3 == 0) {
    lcd.setCursor(0, 1);
    lcd.write("B: ");
    lcd.setCursor(3, 1);
    lcd.write("NF   ");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.write("B: ");
    lcd.setCursor(3, 1);
    lcd.print(dist3);
    lcd.setCursor(4, 1);
    lcd.write(" KM");
    noTone(SPEAKER);
  }
  digitalWrite(phase[2], LOW);
}      


       
//ADC FUNCTIONS      
//================================================================================================================================

 int distance(int inputVoltage) 
 {
   if (inputVoltage >= 890 && inputVoltage < 920) 
   {
     tone(SPEAKER, 550);
     delay(1000);
     return 8;
   }
   else if (inputVoltage >= 850 && inputVoltage < 890) 
   {
     tone(SPEAKER, 400);
     delay(1000);
     return 6;
   }
   else if (inputVoltage >= 750 && inputVoltage < 850) 
   {
     tone(SPEAKER, 250);
     delay(1000);
     return 4;
   }
   else if (inputVoltage >= 600 && inputVoltage < 750) 
   {
     tone(SPEAKER, 100);
     delay(1000);
     return 2;
   }
 
   else return 0 ;

 } 



        
//LCD FUNCTIONS 
//================================================================================================================================
   String Scroll_LCD_Left(String StrDisplay)
   {
      String result;
      String StrProcess = "                " + StrDisplay + "                ";
      result = StrProcess.substring(Li,Lii);
      Li++;
      Lii++;
      if (Li>StrProcess.length())
      {
        Li=16;
        Lii=0;
      }
      return result;
   }

   void Clear_Scroll_LCD_Left()
   {
      Li=16;
      Lii=0;
   }

 //-------------------------------------------------------------
   String Scroll_LCD_Right(String StrDisplay)
   {
      String result;
      String StrProcess = "                " + StrDisplay + "                ";
      if (Rii<1)
      {
         Ri  = StrProcess.length();
         Rii = Ri-16;
      }
      result = StrProcess.substring(Rii,Ri);
      Ri--;
      Rii--;
      return result;
   }

   void Clear_Scroll_LCD_Right()
   {
      Ri=-1;
      Rii=-1;
   }
//================================================================================================================================
