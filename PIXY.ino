#include <SPI.h>
#include <Pixy2.h>
Pixy2 pixy;
int sign=0;

int maxArea = 0;
int minArea = 0;
int i=0;
int x = 0;                  
int y = 0;
int pot_val=0;
char bl_val;
int mid_val=500;
unsigned int width = 0;        
unsigned int height = 0;        
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;                
int Xmax = 200;
void setup() {
 Serial.begin(115200);
 pinMode(1,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pixy.init();
}
void scan()
{
  pixy.ccc.getBlocks();
  width=pixy.ccc.blocks[i].m_width;
  height = pixy.ccc.blocks[i].m_height;
  x= pixy.ccc.blocks[i].m_x;
  y= pixy.ccc.blocks[i].m_y;

}





void Forward()
 {
  Serial.println("Moving Forward");
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
 }

 void Backward()
 {
   Serial.println("Moving Backward");
   digitalWrite(2,HIGH);
   digitalWrite(3,LOW);
   digitalWrite(4,HIGH);
   digitalWrite(5,LOW);
 }

 void Right()
 {
   Serial.println("Moving Right");
   digitalWrite(2,LOW);
   digitalWrite(3,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(5,LOW);
 }
 void Left()
 {
  Serial.println("Moving Left");
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
 }
 void Freeze()
  {
  Serial.println("Stopping");
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
 }
   void mode1()
{
  while(millis()<5000)
  {
    scan();
    area = width * height;
    maxArea = area + 1000;
    minArea = area - 1000;
  }
  scan();
   sign=pixy.ccc.blocks[i].m_signature;
    if(sign == 1)
    {
    newarea = width * height;
      if (x < Xmin)
      {    
       Left();
      }
      else if (x > Xmax)
      {
       Right();
      }
      else if(newarea < minArea)
      {
       Forward();
      }
      else if(newarea > maxArea)
      {
       Backward();
      }
      else
      {
        Freeze();
      }
   }
   else
   {
    Freeze();
   }

}
void mode2(){
   if(Serial.available()){
     bl_val = Serial.read();
     Serial.println(bl_val);
   }
   if(bl_val == 'w')
   {
    Forward();
   }
   else if(bl_val == 'a')
   {
    Left();
   }
   else if(bl_val == 'd')
   {
    Right();
   }
   else if(bl_val == 's')
   {
    Backward();
   }
   else
   {
    Freeze();
   }
}



 void loop() {
   pot_val = analogRead(A0);
   Serial.println(pot_val);
     
     if(pot_val<mid_val)
     {
      Serial.println("Mode1 -Follow Mode");
      mode1();
     }
     else
     {
      Serial.println("Bluetooth Mode");
      mode2();
     }
  }
