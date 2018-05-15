// include the library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int potenciometro = A4;  // A2     // asigna a la constante perilla con el valor 0
int valorPot = 0;
int oldPot = 0;
int bot=A0;
int p=0;
int valSave=0;
int valUp=0;
int valDown=0;
int vector[3]={1,0,1};
int valorPot1;
int valorPot2;
int valorPot3;

int Shutter = 10;//Pin shutter
int Focus = 8;//Pin Focus
int PinPh=A1;
int val;
float vel1;
int vel;

void setup() {
  pinMode(bot, INPUT);
  pinMode(Shutter, OUTPUT);//Shutter
  pinMode(Focus, OUTPUT);//Focu
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.print(" Val. Pote: 0");  
}


//funcion para guardar valor
void save ()
{
  vector[p]=valorPot;
      lcd.print("    ");
        valSave=0;
}

//funcion para subir en el menu
void up ()
{
  delay(100);
  if ( p == 0)
      p=2;
  else 
    p= p-1;
        lcd.setCursor(12,0);
      lcd.print("    ");
        valUp=0;
}

//funcion para bajar en el menu
void down ()
{
  
  delay(100);
  if ( p == 2)
    p = 0;
  else 
    p = p+1;
        lcd.setCursor(12,0);
      lcd.print("    ");
        valDown=0;
  
}

//funcion para imprimir en pantalla 
void letrero(String a )
{
  lcd.setCursor(0,0); 
    lcd.print(a);
  if ( p == 2)
    lcd.print(" ");
    lcd.print(" ");
  if (p == 2){
    lcd.setCursor(8,0);
    lcd.print(velods(vel));
  }
  else
    lcd.print(vector[p]);
    lcd.print("    ");
  
}

//funcion de la velocidad de obturacion
float velod(int a){
  switch(a){
    case 1:
      return 8;
    break;
    case 2:
      return 4;
    break;
    case 3:
      return 2;
    break;
    case 4:
      return 1;
    break;
    case 5:
      return 0.5;
    break;
    case 6:
      return 0.25;
    break;
    case 7:
      return 0.125;
    break;
    case 8:
      return 1/15;
    break;
    case 9:
      return 1/30;
    break;
    case 10:
      return 1/60;
    break;
    case 11:
      return 1/125;
    break;
    case 12:
      return 1/250;
    break;
    case 13:
      return 1/500;
    break;
    case 14:
      return 1/1000;
    break;
    case 15:
      return 1/2000;
    break;
}
}

//funcion para imprimir cadena de valores de la velocidad de obturacion
String velods(int a){
  switch(a){
    case 1:
      return "8";
    break;
    case 2:
      return "4";
    break;
    case 3:
      return "2";
    break;
    case 4:
      return "1";
    break;
    case 5:
      return "1/2";
    break;
    case 6:
      return "1/4";
    break;
    case 7:
      return "1/8";
    break;
    case 8:
      return "1/15";
    break;
    case 9:
      return "1/30";
    break;
    case 10:
      return "1/60";
    break;
    case 11:
      return "1/125";
    break;
    case 12:
      return "1/250";
    break;
    case 13:
      return "1/500";
    break;
    case 14:
      return "1/1000";
    break;
    case 15:
      return "1/2000";
    break;
}
}


//funcion para tomar foto
void tomaFoto(float vel1){
  digitalWrite(Focus, HIGH);
  digitalWrite(Shutter, HIGH);
         delay(vel1);
  digitalWrite(Focus, LOW);
  digitalWrite(Shutter, LOW);
}

void loop() {
  valSave=analogRead(bot);
  valUp=analogRead(bot);
  valDown=analogRead(bot);
  val = analogRead(PinPh);
   vel = vector[2];
  vel1=velod(vel)*1000;
  
  if( valorPot != oldPot ) {
    lcd.setCursor(12,1);
    lcd.print("    ");
    lcd.setCursor(12,1);
    lcd.print(valorPot); 
    oldPot = valorPot;
  
  }

  
  if(p==0){
    valorPot1 = analogRead(potenciometro);
    valorPot = map(valorPot1,0,1023,0,10);
    letrero("Cant. Foto:");
    if(800 < valSave && valSave < 840 ){
      save();
    }
    if(740 < valUp && valUp < 780 ){
      up();
    }
    if(217 < valDown && valDown < 417){
      down();
    }
   
   
  }
  if(p==1){
    valorPot2 = analogRead(potenciometro);
    valorPot = map(valorPot2,0,1023,0,60);
    letrero("Inter(seg):");
    if(800 < valSave && valSave < 840 ){
      save();
    }
    if(740 < valUp && valUp < 780 ){
      up();
    }
    if(217 < valDown && valDown < 417){
      down();
    }    
  }
  if(p==2){
    valorPot3 = analogRead(potenciometro);
    valorPot = map(valorPot3,0,1023,1,15);
    letrero("Speed:");
   if(800 < valSave && valSave < 840 ){
      save();
    }
    if(740 < valUp && valUp < 780 ){
      up();
    }
    if(217 < valDown && valDown < 417){
      down();
    } 
  }
  

  
  
  
  if ((val < 600)and(vector[0]>0)){ 
    for(int i =0; i<vector[0]; i++){
      tomaFoto(vel1);
      delay(vector[1]*1000);
    }}
  
 }
  
