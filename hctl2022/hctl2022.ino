#define clk 8
#define sel1 0
#define sel2 1
#define oe 2
#define rst 3

int i=0;
float t=0,timer=0;
unsigned long byte1 = 0;//byte one. this and the variables below this are really temporary variables.
unsigned long byte2 = 0;//they are only declared up here for clarity.
unsigned long byte3 = 0;
unsigned long byte4 = 0;
signed long decoval = 0;

void setup(){
  Serial.begin(9600);
 //PIN MODES
 pinMode(clk,OUTPUT);
 pinMode(sel1,OUTPUT);
 pinMode(sel2,OUTPUT);
 pinMode(oe,OUTPUT);
 pinMode(rst,OUTPUT);
 
 digitalWrite(sel1,LOW);
 digitalWrite(sel2,HIGH);
 digitalWrite(oe,LOW);
 digitalWrite(rst,LOW);
 delay(5);
 digitalWrite(rst,HIGH);
 //DDRD = B00000000;
 DDRB = B00000000;
 //PORTB = B11111111;
  //SERIAL CONFIG

 

 //Serial.print("Encoder board demo");
}

void loop(){
  
    
  delayMicroseconds(2);
  digitalWrite(clk,HIGH); 
  delayMicroseconds(2);
  digitalWrite(clk,LOW);
  
  i++;
  if(i%4000==0){
  i=0;
  decoval=decoderout();
  t=timer;
  timer = millis();
  Serial.print(timer-t);
  Serial.print("    ");
  Serial.println(decoval);
  }
}

signed long decoderout(){ 
  
  byte Delay = 2;
  
//  digitalWrite(rst,LOW);
//  digitalWrite(clk,LOW);
//  delayMicroseconds(Delay);
//  digitalWrite(clk,HIGH);
//  delayMicroseconds(Delay);
//  digitalWrite(clk,LOW);
//  delayMicroseconds(Delay);
//  digitalWrite(rst,HIGH);
  //PORTB = B11111111;
  //delayMicroseconds(Delay);
  
  
  //digitalWrite(clk,HIGH);
  //digitalWrite(oe,HIGH);
  delayMicroseconds(Delay);//wait a little
  digitalWrite(sel1,LOW);
  digitalWrite(sel2,HIGH);  
  //delayMicroseconds(Delay);
  //digitalWrite(clk,LOW);
  delayMicroseconds(Delay);
  byte4 = PINB;
  
  //delayMicroseconds(Delay);
  digitalWrite(sel1,HIGH);
  delayMicroseconds(Delay);//wait a little
  byte3 = PINB;
  
  //delayMicroseconds(Delay);
  digitalWrite(sel1,LOW);
  digitalWrite(sel2,LOW);
  delayMicroseconds(Delay);//wait a little
  byte2 = PINB;
  //delay(5000);
  //delayMicroseconds(Delay);
  digitalWrite(sel1,HIGH);
  delayMicroseconds(Delay);//wait a little
  byte1 = PINB;
  
  //delayMicroseconds(Delay);//wait a little
  //PORTB = B11111111;
  //digitalWrite(clk,HIGH);
  //digitalWrite(oe,HIGH);
  //delayMicroseconds(Delay);//wait a little
  
    
  signed long val= (byte4 << 24) | (byte3 << 16) | (byte2 <<8 ) | byte1; 
  return val;

}
