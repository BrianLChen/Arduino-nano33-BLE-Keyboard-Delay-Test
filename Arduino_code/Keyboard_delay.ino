/* 用于测量键盘延迟，通过读取 串口 输入的字符来对比延迟 */
/* This is a function to test the delay time of a KEYBOARD. By reading the serial port data to measure the delay */

void setup() 
{
  // put your setup code here, to run once:
  char key_button = 'j';
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(P1_11, OUTPUT);
  // Serial.write("Serial start");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  char input = Serial.read();
  int i;
  int n = 10;
  digitalWrite(P1_11, HIGH);
  // 统计十次求平均 Measure 10 times and get the average
  // for (i = 0; i < n; i++) 
  // {
  //   // 当 serial 的输入 = key_button
  //   while()
  //   {
  //     // 停止计时器
  //   }
  // }

  while(1)
  {
    input = Serial.read();
    if(input == '1')
    {
      digitalWrite(P1_11, LOW);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(20);
      digitalWrite(P1_11, HIGH);
      Serial.write("receive");
    }
    else if(input == '0')
    // else
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("receive");

    }
    else
    {

    }

    // if(digitalRead(P1_11) = LOW)
    // {
    //   Serial.write("push");
    // }
    // else{}
  }
}
