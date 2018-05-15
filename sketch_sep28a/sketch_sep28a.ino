#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int potenciometro=A4;  
int click=0;    
int valorPot=0;
int valAntPot=0;
int btnAnt=A0;
int btnSig=A0;
int valAnt=0;
int valSig=0;
int photoT=A1;
int EstadoPhoto=0;
int valGuardar=0;
int vector[3]={0,1,2};
void setup() {
  // put your setup code here, to run once:
  pinMode(btnAnt, INPUT);
  pinMode(btnSig, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("-> Opcion:");
  lcd.setCursor(13,0);
  lcd.print(vector[click]);
  lcd.setCursor(0,1);
  lcd.print("-> Valor: ");
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  valorPot=analogRead(potenciometro);
  valAnt=analogRead(btnAnt);
  valSig=analogRead(btnSig);
  EstadoPhoto=analogRead(photoT);
  
  if(valorPot != valAntPot) {
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(valorPot); 
    valAntPot = valorPot;
  }
  
    lcd.setCursor(0,0);
    lcd.print(click+1);
    lcd.setCursor(0,1);
    lcd.print(click+1);
    lcd.setCursor(12,0);
    lcd.print(vector[click]);
    Serial.println(valSig);
      
  if(click==0){
    
    if(EstadoPhoto < 25 == HIGH){
      vector[click]=valorPot;
        valGuardar=0;          
      
    }
    if(valAnt >= 267 && valAnt <= 367){
        delay(20);
        if(click == 0)
        click=2;
        else      
          click = click - 1;
          lcd.setCursor(12,0);
          lcd.print("    ");
            valAnt=0;
    }
    if(valSig >= 40 && valSig <= 140){
        delay(20);
        if (click == 2)
          click = 0;
        else
          click = click + 1;
          lcd.setCursor(12,0);
          lcd.print("    ");
          valSig=0;
    }
  }
  if(click==1){
    if(EstadoPhoto < 25){
      vector[click]=valorPot;
      lcd.print("    ");
      valGuardar=0;
    }
    
    if(valAnt >= 267 && valAnt <= 367){
      delay(20);
        if(click == 0)
        click=2;
        else
          click = click - 1;
          lcd.setCursor(12,0);
            valAnt=0;
    }
    if(valSig >= 40 && valSig <= 140){
      delay(20);
        if (click == 2)
          click = 0;
        else
          click = click + 1;
          lcd.setCursor(12,0);
          valSig=0;
    }
  }
  if(click==2){
    if(EstadoPhoto < 25){
      vector[click]=valorPot;
      valGuardar=0;
    }
    
    if(valAnt >= 267 && valAnt <= 367){
      delay(20);
        if(click == 0)
        click=2;
        else
          click = click - 1;
          lcd.setCursor(12,0);
            valAnt=0;
    }
    if(valSig >= 40 && valSig <= 140){
      delay(20);
        if (click == 2)
          click = 0;
        else
          click = click + 1;
          lcd.setCursor(12,0);
          valSig=0;
    }
  }
}
