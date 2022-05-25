#include <Keypad.h>
#include <String.h>
#include <LiquidCrystal.h>

const int rs = 0, en = 1, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



const byte ROWS = 4; 
const byte COLS = 3; 

String key="12345";
String reset="01010";
String input="";

int redLed=A1;
int greenLed=A0;
int buzzer=A2;


int ujra=1;

int size(String x){
  int kar=0;
  while (x[kar]!=0) kar++;
  return kar;
}

boolean equals(String x, String y){

  
  int megegyezik=0;
if(size(x)==size(y)){
  for(int i=0;i<size(x);i++){
    if(x[i]==y[i]) megegyezik++;
    else {return false; }
  }
  if (megegyezik==5) return true;
}

 
}


char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
//  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);

lcd.begin(16,2);
}
  
void loop(){
  delay(50);
  digitalWrite(buzzer,LOW);

  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    digitalWrite(buzzer,HIGH);
    if(customKey!='*'&&customKey!='#')
{input=String(input)+char(customKey);    }
else
{input=""; lcd.setCursor(0,0);
  lcd.print("             ");}
  }
  

if(ujra==1){

// Serial.println(input);
if(size(input)==5&&equals(input,key)) {Serial.println("Megegyezik!"); digitalWrite(greenLed, HIGH);lcd.setCursor(0,1);
  lcd.print("Disarmed!"); ujra=0;}
if(size(input)==5&&!equals(input,key)) {Serial.println("Kaboom!"); digitalWrite(redLed, HIGH);lcd.setCursor(0,1);
  lcd.print("Kaboom!"); ujra=0;}

 lcd.setCursor(0,0);
  lcd.print(input);
}
if(size(input)==5&&equals(input,reset)) {Serial.println("Reset!"); digitalWrite(greenLed, LOW);digitalWrite(redLed, LOW); input="";  lcd.clear(); ujra=1;}

}
