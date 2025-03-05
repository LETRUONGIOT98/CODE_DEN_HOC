/*
VCC to +5V
GND to ground
TRIG to digital pin 12
ECHO to digital pin 13
*/
 
const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
#define bientro A0
#define coi 10
#define den 3
long time;
int khoangcach = 40;  ///thay đổi thôgn số này để điều chỉnh khoảng cách bật đèn, tắt đèn nếu rời khỏi khonảg cách này
int gioihan = 20; //thay đổi thông số này để giới hạn khoảng cách, nếu ngồi gần thì còi kêu
int thoigian = 10000; //cài đặt thời gian tắt khi không sử dụng, 1000 = 1s; 30 000 = 30s;
void setup() 
{
  // initialize serial communication:
  Serial.begin(9600);
  ///Thiết lạp ngõ ra/vào cho arduino
  pinMode(den, OUTPUT);
  pinMode(coi, OUTPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}
 
void loop()
{
  long duration, distanceCm, distanceIn;//Khai báo biến
 ////Phát xung từ chân TRIG của module siêu âm////////
  digitalWrite(TRIG_PIN, LOW);   //Tắt xung
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);  //Phát xung
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);    //Tắt xung
  duration = pulseIn(ECHO_PIN,HIGH);   //Đếm thời gian xung phản hồi lại 
 
  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;   //Tính toán khoảng cách 
  distanceIn = duration / 74 / 2;
 
  if (distanceCm <= 0)  
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distanceIn);
    Serial.print("in: ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }
  delay(50);
  int val = map(analogRead(bientro),0,1023,0,255);  //Đổi giá trị analog từ 0-1023 ra 0-255
 if(distanceCm < khoangcach){  //nếu khoảng cách bé hơn giới hạn
  analogWrite(den, val);    //bật đèn theo độ sáng từ biến trở
  time = millis();
 }
 if(distanceCm > khoangcach){   //Nếu khoảng cách lớn hơn giới hạn, nghãi là người dùng rời khỏi bàn học
  if(millis() - time > thoigian){  //SAu khoảng thời gian đã cài đặt thì
 analogWrite(den, 0);}          ///Tắt đèn 
 }
if(distanceCm < gioihan){   //Nếu khoảng cách quá gần
 digitalWrite(coi, HIGH);   //Còi kêu
 }
 else digitalWrite(coi, LOW);   //nếu không thfi còi tắt
  delay(100);
}
