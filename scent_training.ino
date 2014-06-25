int DHpin = 8;
byte dat[5]; 
byte read_data() {
  byte data;
  for(int i=0; i<8; i++) {
    if(digitalRead(DHpin) == LOW) {
      while(digitalRead(DHpin) == LOW);
      delayMicroseconds(30); //判断高电平的持续时间,以判定数据是‘0’还是‘1’;
      if(digitalRead(DHpin) == HIGH)
        data |= (1<<(7-i)); //高位在前,低位在后;
      //等待 50us;

      while(digitalRead(DHpin) == HIGH);
    } 
  }
  return data; 
}
void start_test() {
  //数据‘1’,等待下一位的接收;
  digitalWrite(DHpin,LOW); //拉低总线,发开始信号;
  delay(30); //延时要大于 18ms,以便 DHT11 能检测到开始信号; 
  digitalWrite(DHpin,HIGH);
  delayMicroseconds(40); //等待 DHT11 响应;
  pinMode(DHpin,INPUT);
  while(digitalRead(DHpin) == HIGH);
  delayMicroseconds(80); //DHT11 发出响应,拉低总线 80us;
  if(digitalRead(DHpin) == LOW);
  delayMicroseconds(80); //DHT11 拉高总线 80us 后开始发送数据;
  for(int i=0;i<4;i++) //接收温湿度数据,校验位不考虑;
    dat[i] = read_data();
  pinMode(DHpin,OUTPUT);
  digitalWrite(DHpin,HIGH); //发送完一次数据后释放总线,等待主机的下一次开 始信号;
}
void setup() {
  Serial.begin(9600);
  pinMode(DHpin,OUTPUT); 
}
void loop() {
  start_test();
  Serial.print("Current humdity = "); 
  Serial.print(dat[0], DEC); //显示湿度的整数位; 
  Serial.print('.');
  Serial.print(dat[1],DEC); //显示湿度的小数位; 
  Serial.println('%');
  Serial.print("Current temperature = "); 
  Serial.print(dat[2], DEC); //显示温度的整数位; 
  Serial.print('.');
  Serial.print(dat[3],DEC); //显示温度的小数位;
  Serial.println('C'); 
  delay(700);
}



