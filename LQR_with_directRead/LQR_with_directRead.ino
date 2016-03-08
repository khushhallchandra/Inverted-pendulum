#include "Arduino.h"


#define finalout1 6
#define finalout2 7
#define encoder1PinA 19
#define encoder1PinB 20
#define encoder2PinA 2
#define encoder2PinB 3

int i, j, timer, T = 20,check=0;// timer1_counter; 
float error,out, perr, derr,theta1=0,theta1prev=0,theta2=0,theta2prev=0, ierr, kp, kd, ki, lasterr = 0,t=0, t_prev=0,atanT;
//int led=13;

boolean A_set = false;
boolean B_set = false;
boolean prevA_set = false;
boolean prevB_set = false;

void setup(){
  Serial.begin(115200); 
  DDRD = B00000000;
  DDRE = B00000000;
  //pinMode(encoder1PinA, INPUT); 
  //pinMode(encoder1PinB, INPUT); 
  digitalWrite(encoder1PinA, HIGH);  // turn on pullup resistor
  digitalWrite(encoder1PinB, HIGH);  // turn on pullup resistor
  
  //pinMode(encoder2PinA, INPUT); 
  //pinMode(encoder2PinB, INPUT); 
  digitalWrite(encoder2PinA, HIGH);  // turn on pullup resistor
  digitalWrite(encoder2PinB, HIGH);  // turn on pullup resistor
  
  pinMode(finalout1,OUTPUT);
  pinMode(finalout2,OUTPUT);
  
  attachInterrupt(4, interrupt1, CHANGE);    //pin 19
  attachInterrupt(0, interrupt2, CHANGE);    //pin 2
  i=0;
  kp=0.03;
  kd=0.000;
  ki=0.001;

  atanT=atan(T); 
 
 //pin 19 interrupt, pin 20 is also read
 //PD2, PD1
 
  //pin 2 interrupt, pin 3 is also read
 //PE4, PE5
}

void interrupt1() {
  boolean x = PIND & B00000010;
  boolean y = PIND & B00000100;
  theta1+=(x == (y/2))? +1 : -1;
    
}
void interrupt2() {
  //theta2+=(digitalRead(2)==digitalRead(3))? +1 : -1;
  boolean x = PINE & B00010000;
  boolean y = PINE & B00100000;
  theta2+=(x==(y/2))? +1 : -1;
}

void loop(){  
  i++;
  
  out = 0.135*theta1 - 0.0088*theta2 + 17.39*(theta1-theta1prev)/T - 4.84*(theta2-theta2prev)/T;
  theta1prev=theta1;
  theta2prev=theta2;
  out = T*atan(10*out)/atanT;

  if(i==10){
    i=0;
  timer = millis();
  Serial.print(timer);
  Serial.print("    ");
  Serial.print(theta1);
  Serial.print("    ");
  Serial.print(theta2);
  Serial.print("    ");
  Serial.println(out);
  }

    if(out>=0) {
        digitalWrite(finalout1 , HIGH);
        digitalWrite(finalout2 , LOW);

        if(out<T) {
            delay(out);                                                                                    
            digitalWrite(finalout1 , LOW);  
            digitalWrite(finalout2 , LOW);
            delay(T-out);
        }
        else
            delay(T);

    }

    else
    if(out <0 ) {
        digitalWrite(finalout1 , LOW);
        digitalWrite(finalout2 , HIGH);
                                                                                                                                                                                      
        if(out > -T) {
            delay(-out);
            digitalWrite(finalout1 , LOW);  
            digitalWrite(finalout2 , LOW);
            delay(T+out);
        }
        else
            delay(T);

    }
}
