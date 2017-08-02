// モーター制御
//ArduinoUno
const int motorA = 12;
const int motorB = 11;
const int PWM_AB = 7;
const int motorC = 10;
const int motorD = 9;
const int PWM_CD = 6;

// 後退gittest

//とりあえず前に進む 
/*//esp
const int motorA = 15;
const int motorB = 12;
const int PWM_AB = 0;
const int motorC = 13;
const int motorD = 14;
const int PWM_CD = 2;*/
#define trigPin 4
#define echoPin 5

int distance = 10000;//進みたい距離(モーター回す時間)
double ultraSonic = 0;//超音波センサーの値

void setup(){
  pinMode(motorA,OUTPUT); //信号用ピン
  pinMode(motorB,OUTPUT); 
  pinMode(motorC,OUTPUT); 
  pinMode(motorD,OUTPUT); 

  
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);//超音波センサー
  pinMode(echoPin, INPUT);
}

// とりあえず指定時間だけ前に進む関数
void MovingForward(int second){
  
  //左右正回転
  digitalWrite(motorA,HIGH);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,HIGH);
  digitalWrite(motorD,LOW);
  //analogWrite(PWM_AB,200);   
  //analogWrite(PWM_CD,200); 
  delay(second);  
}
// 停止
void toStop(){
  //全てのモータを停止
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,LOW);
  delay(1000);
}

void loop() {
    int duration, kyori;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  kyori = (duration/2) / 29.1;
  if (kyori >= 200 || kyori <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(kyori);
    Serial.println(" cm");
  }
  
  if(distance >= 0 && kyori > 20){//たどり着いてなくて障害物がない時
    MovingForward(1000);
    distance = distance - 1000;
  }else if(distance >= 0 && ultraSonic <= 20){//たどり着いてなくて障害物がある時
    toStop();
    distance = distance + 1000;
  }else if(distance < 0){//たどり着いたとき
 //   toStop();
 //   delay(5000);
    distance = 10000;
  }
}


