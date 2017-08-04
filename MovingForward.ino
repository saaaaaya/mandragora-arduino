//ArduinoUno

// モーター制御
const int motorA = 12;
const int motorB = 11;
const int motorC = 10;
const int motorD = 9;
//ESPからの天気情報(晴?)
const int weather = 3;
//ESPからの湿度情報
const int soil = 2;

//超音波センサー4方向
#define FtrigPin 4
#define FechoPin 5
#define BtrigPin 14
#define BechoPin 15
#define RtrigPin 16
#define RechoPin 17
#define LtrigPin 18
#define LechoPin 19

void setup(){
  Serial.begin (9600);
  pinMode(motorA,OUTPUT); //モーター信号用ピン
  pinMode(motorB,OUTPUT); 
  pinMode(motorC,OUTPUT); 
  pinMode(motorD,OUTPUT); 
  pinMode(weather,INPUT);//晴かどうか
  pinMode(soil,INPUT);//乾いているかどうか
  
  pinMode(FtrigPin, OUTPUT);//超音波センサー
  pinMode(BtrigPin, OUTPUT);
  pinMode(RtrigPin, OUTPUT);
  pinMode(LtrigPin, OUTPUT);
  pinMode(FechoPin, INPUT);
  pinMode(BechoPin, INPUT);
  pinMode(RechoPin, INPUT);
  pinMode(LechoPin, INPUT);
}

// とりあえず指定時間だけ前に進む関数
void MovingForward(int second){
  
  //左右正回転
  digitalWrite(motorA,HIGH);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,HIGH);
  digitalWrite(motorD,LOW);
  delay(second);  
}
// とりあえず指定時間だけ後ろに進む関数
void MovingBack(int second){
  
  //左右正回転
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,HIGH);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,HIGH);
  delay(second);  
}
// とりあえず左に曲がる！
void MovingLeft(){
  
  //左正回転
  digitalWrite(motorA,HIGH);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,LOW);
  //analogWrite(PWM_AB,200);   
  //analogWrite(PWM_CD,200); 
  delay(3800);  
}
// とりあえず右に曲がる！
void MovingRight(){
  
  //右正回転
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,HIGH);
  digitalWrite(motorD,LOW);
  //analogWrite(PWM_AB,200);   
  //analogWrite(PWM_CD,200); 
  delay(3500);  
}

//右回転
void MovingRightTurn(int second){
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,HIGH);
  digitalWrite(motorC,HIGH);
  digitalWrite(motorD,LOW);
  delay(second);
}
//左回転
void MovingLeftTurn(int second){
  digitalWrite(motorA,HIGH);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,HIGH);
  delay(second);
}
// 停止
void toStop(int second){
  //全てのモータを停止
  digitalWrite(motorA,LOW);
  digitalWrite(motorB,LOW);
  digitalWrite(motorC,LOW);
  digitalWrite(motorD,LOW);
  delay(second);
}

//超音波センサー
int sonicSensorCheck(int trigPin,int echoPin){
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void loop() {
  //sonicSensorCheck(FtrigPin,FechoPin);
  toStop(1000);
  //乾いていたら移動する
  //止まるフラグをどうするか
  if(digitalRead(soil) == HIGH){
    //超音波センサーの判定
    if(sonicSensorCheck(FtrigPin,FechoPin)>20){
    MovingForward(3000);
    }else if(sonicSensorCheck(RtrigPin,RechoPin)>20){
    MovingRight();
    MovingForward(3000);
    }else iff(sonicSensorCheck(LtrigPin,LechoPin)>20){
    MovingLeft();
    MovingForward(3000);
    }else if(sonicSensorCheck(BtrigPin,BechoPin)>20){
    MovingBack(3000);
    }else{//4方向に障害物があって動けないとき
    //動けないことをESPにdigitalWhiteとかで伝える
    }
  //晴れていたらぐねぐね動く(その場で回転？)
  }else if(digitalRead(weather) == HIGH){
    MovingRithtTurn(5000);
    toStop();
    MovingLeftTurn(5000);
  }

}


