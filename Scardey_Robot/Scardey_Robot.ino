#define ALERT 2
#define EYE 10
#define ENABLE1 4
#define ENABLE2 7
#define MA1 5
#define MA2 6
#define MB1 3
#define MB2 9
#define SPEAKER 8
#define IR_BACK A2
#define IR_RIGHT A3
#define IR_LEFT A1
#define IR_FRONT A0

int LEFT_RANGE;
int RIGHT_RANGE;
int FRONT_RANGE;
int BACK_RANGE;
int IR_LESS_RANGE[2] = {550,800};
int IR_RANGE[2] = {300,800};

void setup() {
  pinMode(ALERT,OUTPUT);
  pinMode(EYE,OUTPUT);
  pinMode(ENABLE1,OUTPUT);
  pinMode(ENABLE2,OUTPUT);
  digitalWrite(ENABLE1,1);
  digitalWrite(ENABLE2,1);
  pinMode(MA1,OUTPUT);
  pinMode(MA2,OUTPUT);
  pinMode(MB1,OUTPUT);
  pinMode(MB2,OUTPUT);  
 
  Serial.begin(9600);
}

void loop() {  
  digitalWrite(ALERT,1);
  RIGHT_RANGE = analogRead(IR_RIGHT);
  LEFT_RANGE = analogRead(IR_LEFT);
  FRONT_RANGE = analogRead(IR_FRONT);
  BACK_RANGE = analogRead(IR_BACK);
  Serial.print(FRONT_RANGE); 
  Serial.print("  ");
  Serial.print(RIGHT_RANGE);
  Serial.print("  "); 
  Serial.print(BACK_RANGE); 
  Serial.print("  ");
  Serial.println(LEFT_RANGE);  
  if(RIGHT_RANGE < IR_RANGE[0]){
    LEFT_ESCAPE();
  }
  else if(LEFT_RANGE < IR_RANGE[0]){
    RIGHT_ESCAPE();
  }
  else if(FRONT_RANGE < IR_RANGE[0]){
    BACKWARD_ESCAPE();
  }
  else if(BACK_RANGE < IR_RANGE[0]){
    FORWARD_ESCAPE();
  }
  
  if(RIGHT_RANGE < IR_RANGE[1]){
    DYNAMIC_ALERT(RIGHT_RANGE-IR_RANGE[0]);
  }
  else if(LEFT_RANGE < IR_RANGE[1]){
    DYNAMIC_ALERT(LEFT_RANGE-IR_RANGE[0]);
  }
  else if(FRONT_RANGE < IR_RANGE[1]){
    DYNAMIC_ALERT(FRONT_RANGE-IR_RANGE[0]);
  }
  else if(BACK_RANGE < IR_RANGE[1]){
    DYNAMIC_ALERT(BACK_RANGE-IR_RANGE[0]);
  }
  
 
}

void LEFT_ESCAPE(){
  LEFT();
  delay(150);
  STOP();
  delay(100);
  FORWARD();
  delay(500);
  STOP();
}

void RIGHT_ESCAPE(){
  RIGHT();
  delay(150);
  STOP();
  delay(100);
  FORWARD();
  delay(500);
  STOP();
}

void FORWARD_ESCAPE(){
  FORWARD();
  delay(650);
  STOP();
}

void BACKWARD_ESCAPE(){
  LEFT();
  delay(300);
  STOP();
  delay(100);
  FORWARD();
  delay(650);
  STOP();
}

void LEFT(){
  digitalWrite(MA1,1);
  digitalWrite(MA2,0);
  digitalWrite(MB1,1);
  digitalWrite(MB2,0);
}

void RIGHT(){
  digitalWrite(MA1,0);
  digitalWrite(MA2,1);
  digitalWrite(MB1,0);
  digitalWrite(MB2,1);
}

void FORWARD(){
  digitalWrite(MA1,0);
  digitalWrite(MA2,1);
  digitalWrite(MB1,1);
  digitalWrite(MB2,0);
}

void BACKWARD(){
  digitalWrite(MA1,1);
  digitalWrite(MA2,0);
  digitalWrite(MB1,0);
  digitalWrite(MB2,1);
}

void STOP(){
  digitalWrite(MA1,0);
  digitalWrite(MA2,0);
  digitalWrite(MB1,0);
  digitalWrite(MB2,0);
}


void DYNAMIC_ALERT(int range){
  if(range < 0){
    range = 0;
  }
  tone(SPEAKER,740);
  digitalWrite(ALERT,1);
  delay(range/2);
  noTone(SPEAKER);
  digitalWrite(ALERT,0);
  delay(range/2);
}
