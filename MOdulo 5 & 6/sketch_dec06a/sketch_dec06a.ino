#include <ptp.h>
#include <usbhub.h>
#include <LiquidCrystal.h>
USB usb;
PTPStateHandlers ph;
PTP ptp(&usb, &ph);

int _ISO_ [9]= {200, 250, 320, 500, 640, 800, 1000, 1250, 1600};
int ISO_Valores [9]= {200, 250, 320, 500, 640, 800, 1000, 1250, 1600};

int _Velocidad_ [12]= {8, 4,2,1,1/2, 1/4, 1/8, 1/15, 1/30, 1/60, 1/125, 1/250};
int Velocidad_Valores [12]= {8, 4,2,1,1/2, 1/4, 1/8, 1/15, 1/30, 1/60, 1/125, 1/250};

uint16_t valores_balance[7] = {0x00000002, 0x00000006, 0x00000005, 0x00000004,0x00000007,uint16_t(0xFFFF8010), uint16_t(0xFFFF8011)};

char modos_balance[7][30] = {"AUTO","Incandescente", " Fluorescente", "Luz Sol Directa", "Flash", "Nublado","Sombra"};

uint16_t valores_Exposicion[18] = {0x00000002, 0x00000005, 0x0000000A, 0x00000014, 0x00000028, 0x00000050,0x000000A6,0x0000014D, 0x0000029A,
0x000004E2, 0x000009C4, 0x00001388, 0x00002710, 0x00004E20, uint16_t(0xFFFF9C40), 0x00003880,0x000049F0, uint16_t(0XFFFF93E0)};

char modos_Exposicion[18][10] = {"1/4000", "1/2000", "1/1000","1/500", "1/250","1/125","1/60","1/30","1/15","1/8", "1/4",
"1/2", "1" , "2", "4","8", "15","30"};

uint16_t valores_FNUMBER[21]={0x0000015E,0x00000190,0x000001C2,0x000001F4,0x00000230,0x00000276,0x000002C6,0x00000320,0x00000384
,0x000003E8,0x0000044C,0x00000514,0x00000578,0x00000640,0x00000708,0x000007D0,0x00000898,0x000009C4,0x00000B54,0x00000C80,
0x00000E10};

char modos_FNUMBER[21][3]= {"3.5","4", "4.5", "5", "5.6", "6.3","7.1","8","9","10", "11","13", "14","16", "18","20","22","25", "29", "32" ,"36"};

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//int potenciometro = A4;
//int valorPotenciometro = 0;
int presionado=0;
int j=0;
int j_ant=0;
int valorPotenciometro = 0;
int AntiguoPotenciometro = 0;
int botonArriba=7;
int botonAbajo=6;
int botonGuardar=10;
int botones = A0;
int p=0;
int valorGuardar=0;
int valorArriba=0;
int valorAbajo=0;
char vector[9][20]={"Delay Inicial","Intervalo","Cant tomas", "Exposicion", "Balance de Blancos", "ISO", "ExposicionUSB", "Apertura", "velocidad" };
int valores[4][3]={{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0}};
int valores_ant[4][3]={{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0}};
int valores_guardar[4][3]={{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0},{0 , 0 , 0}};
int delay_ini=0;
int intervalo_=0;
int tomas_=0;
int expo = 0;
int valorBotones =0;
int cambio = false;
int segundos=0;
int horas=0;
int minutos=0;
int estado_pot2=0;
int estado_pot3=0;
int pp = A1;
int shutter = 10;
int focus = 8;
int horas_delay=0;
int horas_intervalo=0;
int shout=9;
int estadoShout=0;
int estadoFoto=0;
int p_ant;
//==============================================================================================
void setup() {
  pinMode(botonArriba, INPUT);
  pinMode(botonAbajo, INPUT);
  pinMode(botonGuardar, INPUT);
  pinMode(botones, INPUT);
  pinMode(shutter, OUTPUT);
  pinMode(focus, OUTPUT);
  lcd.begin(16, 2);
  imprimir();
  Serial.begin(9600);
}
//==============================================================================================
void delay(){

  if (valorBotones>=740 && valorBotones<=780){
    horas_delay++;
  }
      valores[0][0]=horas_delay;
      valores[0][1]=minutos;
      valores[0][2]=segundos;

   if(valorBotones>=260 && valorBotones<=300){
      valores_guardar[0][0]=horas_delay;
      valores_guardar[0][1]=minutos;
      valores_guardar[0][2]=segundos;
      Serial.println(valores[0][2]);
    }
}
//============================================================================================
void intervalo(){

  if (valorBotones>=740 && valorBotones<=780){

  if (horas_intervalo==10){
    horas_intervalo=0;
  }
  else
    horas_intervalo++;
  }
  valores[1][0]=horas_intervalo;
  valores[1][1]=minutos;
  valores[1][2]=segundos;
  if(valorBotones>=260 && valorBotones<=300){
      valores_guardar[1][0]=horas_intervalo;
      valores_guardar[1][1]=minutos;
      valores_guardar[1][2]=segundos;
    }
}
//==============================================================================================
void tomas (){
  int _tomas_ =segundos;
  valores[2][0]=_tomas_;
  if(valorBotones>=260 && valorBotones<=300){
  valores_guardar[2][0]=_tomas_;
  }
}
//==============================================================================================
void exposicion (){
  int expo=0;
   if (valorBotones>=740 && valorBotones<=780){
    if (expo==10){
    expo=0;
  }
  else
    expo++;
  }
  valores[3][0]=expo;
  if(valorBotones>=260 && valorBotones<=300){
  valores_guardar[3][0]=expo;
  Serial.println(valorBotones);
  }
}
//==============================================================================================
void foto(){
    Serial.println(tomas_);
    for(int i=0; i<tomas_; i++){
    digitalWrite(shutter, HIGH);
    digitalWrite(focus,HIGH);
    delay(expo*1000);
    Serial.println(expo);
    digitalWrite(shutter,LOW);
    digitalWrite(focus,LOW);
    delay(intervalo_);
  }
}
//==============================================================================================
void bajar (){
  delay(100);
  if ( p == 8)
    p = 0;
  else
    p = p+1;
    lcd.setCursor(1,0);
    lcd.print("                ");
    valorAbajo=0;
}
//==============================================================================================
void subir (){
  delay(100);
  if ( p == 0)
     p=8;
  else
    p= p-1;
    lcd.setCursor(1,0);
    lcd.print("                 ");
    valorArriba=0;
}
//==============================================================================================
void imprimir(){
  if (p==0||p==1){
     if (p_ant!=0 &&p_ant!=1){
      lcd.setCursor(1,1);
      lcd.print("                 ");
      p_ant=p;
    }
  if (valores[p][0]!=valores_ant[p][0]){
    lcd.setCursor(1,1);
    lcd.print("                 ");
    lcd.setCursor(1,1);
    lcd.print(valores[p][0]);
    valores_ant[p][0]=valores[p][0];
  }
  if (valores[p][1]!=valores_ant[p][1]){
    lcd.setCursor(5,1);
    lcd.print("                 ");
    lcd.setCursor(5,1);
    lcd.print( valores[p][1]);
    valores_ant[p][1]=valores[p][1];
  }
  if (valores[p][2]!=valores_ant[p][2]){
    lcd.setCursor(9,1);
    lcd.print("                 ");
    lcd.setCursor(9,1);
    lcd.print(valores[p][2]);
    valores_ant[p][2]=valores[p][2];
   }
   else
  {
    lcd.setCursor(1,0);
    lcd.print(vector[p]);
    lcd.setCursor(1,1);
    lcd.print(valores[p][0]);
    lcd.setCursor(3,1);
    lcd.print(":");
    lcd.setCursor(5,1);
    lcd.print( valores[p][1]);
    lcd.setCursor(7,1);
    lcd.print(":");
    lcd.setCursor(9,1);
    lcd.print(valores[p][2]);
  }
  }

  else if (p==2||p==3){
    if (p_ant!=2 && p_ant!=3){
      lcd.setCursor(1,1);
      lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (valores[p][0]!=valores_ant[p][0]){
        lcd.setCursor(1,1);
        lcd.print("                 ");
        lcd.setCursor(1,1);
        lcd.print(valores[p][0]);
        valores_ant[p][0]=valores[p][0];
    }
    else{
    lcd.setCursor(1,0);
    lcd.print(vector[p]);
    lcd.setCursor(1,1);
    lcd.print(valores[p][0]);
    }
  }
  else if (p==4){
    if (p_ant!=4){
      lcd.setCursor(1,1);
      lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (j!=j_ant){
      lcd.setCursor(1,1);
      lcd.print("                 ");
      lcd.setCursor(1,1);
      lcd.print(modos_balance[j]);
      j_ant=j;
  }
    else{
    lcd.setCursor(1,0);
    lcd.print(vector[p]);
    lcd.setCursor(1,1);
    lcd.print(modos_balance[j]);
    }
 }
 else if (p==5){
    if (p_ant!=5){
      lcd.setCursor(1,1);
 lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (j!=j_ant){

  lcd.setCursor(1,1);
 lcd.print("                 ");
  lcd.setCursor(1,1);
 lcd.print(ISO_Valores[j]);
    j_ant=j;
  }
    else{
    lcd.setCursor(1,0);
  lcd.print(vector[p]);
    lcd.setCursor(1,1);
  lcd.print(ISO_Valores[j]);
    }
  }
  else if (p==6){
    if (p_ant!=6){
      lcd.setCursor(1,1);
 lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (j!=j_ant){

  lcd.setCursor(1,1);
 lcd.print("                 ");
  lcd.setCursor(1,1);
 lcd.print(modos_Exposicion[j]);
    j_ant=j;
  }
    else{
    lcd.setCursor(1,0);
  lcd.print(vector[p]);
    lcd.setCursor(1,1);
  lcd.print(modos_Exposicion[j]);
    }
  }
  else if (p==7){
    if (p_ant!=7){
      lcd.setCursor(1,1);
      lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (j!=j_ant){
     lcd.setCursor(1,1);
     lcd.print("                 ");
     lcd.setCursor(1,1);
     lcd.print(modos_FNUMBER[j]);
     j_ant=j;
     }
    else{
        lcd.setCursor(1,0);
        lcd.print(vector[p]);
        lcd.setCursor(1,1);
        lcd.print(modos_FNUMBER[j]);
    }
  }
  else if (p==8){
    if (p_ant!=8){
      lcd.setCursor(1,1);
 lcd.print("                 ");
      p_ant=p;
      Serial.println(p_ant);
    }
    if (j!=j_ant){

  lcd.setCursor(1,1);
 lcd.print("                 ");
  lcd.setCursor(1,1);
 lcd.print(Velocidad_Valores[j]);
    j_ant=j;
  }
    else{
    lcd.setCursor(1,0);
  lcd.print(vector[p]);
    lcd.setCursor(1,1);
  lcd.print(Velocidad_Valores[j]);
    }
  }
}
//==============================================================================================
void exposicion_(){
j = 0;
  if (valorBotones>=740 && valorBotones<=770)
  {
    if (j==17){
      j=0;
    }
    else
    j++;
  }
  uint16_t val = valores_Exposicion[j];
  if(valorBotones>=260 && valorBotones<=300){
    ptp.SetDevicePropValue(Tiempo_exposicion,uint16_t(val));
  }
}
//==============================================================================================
void balance(){
    j = 0;
    if (valorBotones>=740 && valorBotones<=770){
        if (j==6){
        j=0;
    }
    else
    j++;
  }
  uint16_t val = valores_balance[j];
  if(valorBotones>=260 && valorBotones<=300){
    ptp.SetDevicePropValue(WhiteBalance,uint16_t(val));
    }
}
//==============================================================================================
void FNumber_(){
    j = 0;
    if (valorBotones>=740 && valorBotones<=770){
        if (j==20){
          j=0;
        }
    else
        j++;
  }
  uint16_t val = valores_FNUMBER[j];
  if(valorBotones>=260 && valorBotones<=300){
    ptp.SetDevicePropValue(FNumber,uint16_t(val));
    }
}
//==============================================================================================
void Velocidad_(){
    j = 0;
    if (valorBotones>=740 && valorBotones<=770){
    if (j==20){
      j=0;
    }
    else
    j++;
  }
  uint16_t val = Velocidad_Valores[j];
  if(valorBotones>=260 && valorBotones<=300){
   ptp.SetDevicePropValue(Velocidad,uint16_t(val));
}
}
//==============================================================================================
void ISO_(){
j = 0;
  if (valorBotones>=740 && valorBotones<=770){
    if (j==20){
      j=0;
    }
    else
    j++;
  }
  int val = _ISO_[j];
if(valorBotones>=260 && valorBotones<=300){
   ptp.SetDevicePropValue(ISO,uint16_t(val));
}
}
//==============================================================================================
void estadoBotones(){
  if(valorBotones>=800 && valorBotones<=840){
      subir();
     }
}
//==============================================================================================
void loop() {
  if(valorBotones!=0){
    Serial.println(valorBotones);
  }
  usb.Task();
  delay_ini=((valores_guardar[0][0]*3600)+(valores_guardar[0][1]*60)+valores_guardar[0][2])*1000;
  intervalo_=((valores_guardar[1][0]*3600)+(valores_guardar[1][1]*60)+valores_guardar[1][2])*1000;
  valorBotones = analogRead(A0);
  tomas_ = valores_guardar[2][0];
  estadoFoto = analogRead(pp);
  expo=valores_guardar[3][0];
  estado_pot2 = analogRead(A4);
  estado_pot3 = analogRead(A5);
  minutos =map(estado_pot2, 0, 1023, 0, 60);
  segundos = map(estado_pot3, 0, 1023, 0, 60);
  imprimir();
  estadoBotones();
  switch(p){
  case 0:
    delay();
  case 1:
    intervalo();
  case 2:
    tomas();
  case 3:
    exposicion();
  case 4:
    balance();
  case 5:
    ISO_();
  case 6:
    exposicion_();
  case 7:
    FNumber_();
  case 8:
    Velocidad_();
  if (estadoFoto<500){
      Serial.println(valorBotones);
      Serial.println(tomas_);
      Serial.println(delay_ini);
      delay(delay_ini);
      foto();
  }
}
}

