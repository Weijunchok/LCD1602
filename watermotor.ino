#include <EEPROM.h>
//LCD1602显示5*8点阵汉字程序，然后有16*2个点阵
#include <Wire.h>  //加载Wire通讯库
#include <LiquidCrystal_I2C.h>  //加载液晶屏库
LiquidCrystal_I2C lcd(0x27,16,2);  // 设 LCD的地址为0x27，16列2行 
//设置LCD1602设备地址，这里的地址是一般是0x20，或者0x27，也可能0x3F具体看模块手册

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;
int Relay_level=0;
int Liquid_level=0;
byte value;
int T1;
int T2;
int bt1 = 15;
int bt2 = 16;
int bt3 = 17;
int input1 = 5;
int input2 = 6;
int input3 = 3;
int input4 = 9;
void setup() {
  /** Empty setup. **/
  Serial.begin(9600);
  //Serial.println(EEPROM.length()); //1024
  //EEPROM.write(2, 0); //加了这句可以重新写入T1 T2
  pinMode(7,OUTPUT); //继电器1
  pinMode(14,INPUT); //液面传感器
  pinMode(bt1,INPUT); //按键1
  pinMode(bt2,INPUT); //按键1
  pinMode(bt3,INPUT); //按键1
  pinMode(input1,OUTPUT); //电机1正极
  pinMode(input2,OUTPUT); //电机1负极
  pinMode(input3,OUTPUT); //电机2正极
  pinMode(input4,OUTPUT); //电机1负极
  lcd.init();     //初始化LCD
  lcd.backlight(); //打开背光

  lcd.setCursor(0,0);                //设置显示指针
  lcd.print("Please Press");     //输出字符到LCD1602上
  lcd.setCursor(0,1);
  lcd.print("Key A");
  
  delay(100);
  if(EEPROM.read(2)==0){
  Serial.println("write");
  EEPROM.write(0, 2);
  delay(100);
  EEPROM.write(1, 3);
  delay(100);
  EEPROM.write(2, 1);
  delay(100);
  }
  

  value = EEPROM.read(0);
  Serial.print(0);
  Serial.print("\t");
  T1=value;
  Serial.print(T1);
  //Serial.print(value, DEC);
  Serial.println();
  value = EEPROM.read(1);
  Serial.print(1);
  Serial.print("\t");
  T2=value;
  Serial.print(T2);
  //Serial.print(value, DEC);
  Serial.println();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  Liquid_level=digitalRead(14);
  Serial.print("Liquid_level= ");Serial.println(Liquid_level);
  digitalWrite(7,HIGH);
  Relay_level=digitalRead(7);
  Serial.print("Relayfirst_level= ");Serial.println(Relay_level);
  delay(2000);
  Liquid_level=digitalRead(14);
  Serial.print("Liquid_level= ");Serial.println(Liquid_level);
  digitalWrite(7,LOW);
  Relay_level=digitalRead(7);
  Serial.print("Relayseconde_level= ");Serial.println(Relay_level);
  lcd.setCursor(0,0);                //设置显示指针
  lcd.print("T1            T2");     //输出字符到LCD1602上
  lcd.setCursor(0,1);
  lcd.print(Relay_level);
  lcd.setCursor(14,1);
  lcd.print(Liquid_level);
  delay(2000);
}
