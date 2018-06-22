char inByte;
String command;
String Mode;
String Speed1;
String Speed2;
char Speed1Array[4];
char Speed2Array[4];
int Speed1Int;
int Speed2Int;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);       //Channel A Speed Pin Initialize
  pinMode(9,OUTPUT);       //Channel B Speed Pin Initialize 
  pinMode(2,OUTPUT);      //Channel A Direction Pin Initialize
  pinMode(8,OUTPUT);      //Channel B Direction Pin Initialize
  pinMode(5,OUTPUT);      //Indicator LED Pin Initialize
  digitalWrite(5,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
    while (Serial.available() > 0){
    inByte = Serial.read();
    if ((inByte >= 65 && inByte <= 90) || (inByte >=97 && inByte <=122) || (inByte >= 48 &&
    inByte <=57) || inByte == 43 || inByte == 61 || inByte == 63) {
      command.concat(inByte);
    }
  }
  Mode = command.substring(0,4);
  Speed1 = command.substring(4,7);
  Speed2 = command.substring(7);
  Speed1.toCharArray(Speed1Array,4);
  Speed2.toCharArray(Speed2Array,4);
  Speed1Int = atoi(Speed1Array);
  Speed2Int = atoi(Speed2Array);
  if (Mode.equalsIgnoreCase("1R2L")){
      Serial.println("Status is first right, second left");
      Serial.print("Speed 1 ");
      Serial.println(Speed1);
      Serial.print("Speed 2 ");
      Serial.println(Speed2);
      digitalWrite(2, HIGH);
      digitalWrite(8, LOW);
      analogWrite(3, Speed1Int);
      analogWrite(9, Speed2Int);
      delay(500); 
  }
  if (Mode.equalsIgnoreCase("1L2R")){
      Serial.println("Status is first left second right");
      Serial.print("Speed 1 ");
      Serial.println(Speed1Int);
      Serial.print("Speed 2 ");
      Serial.println(Speed2Int);
      digitalWrite(2, LOW);
      digitalWrite(8, HIGH);      
      analogWrite(3, Speed1Int);
      analogWrite(9, Speed2Int);
      delay(500);
  }
  if (Mode.equalsIgnoreCase("1R2R")){
      Serial.println("Status is both right");
      Serial.print("Speed 1 ");
      Serial.println(Speed1);
      Serial.print("Speed 2 ");
      Serial.println(Speed2);
      digitalWrite(2, HIGH);
      digitalWrite(8, HIGH);
      analogWrite(3, Speed1Int);
      analogWrite(9, Speed2Int);
      delay(500);
  }
  if (Mode.equalsIgnoreCase("1L2L")){
      Serial.println("Status is both left");
      Serial.print("Speed 1 ");
      Serial.println(Speed1);
      Serial.print("Speed 2 ");
      Serial.println(Speed2);
      digitalWrite(2, LOW);
      digitalWrite(8, LOW);
      analogWrite(3, Speed1Int);
      analogWrite(9, Speed2Int);
      delay(500);
  }
  if (Mode.equalsIgnoreCase("Stan")){
    Serial.println("Punching, Stand by please");
    analogWrite(3,0);
    analogWrite(9,0);
    digitalWrite(5,HIGH);
    delay(2500);
    digitalWrite(5,LOW);
    Serial.println("Ejecting");
    digitalWrite(2, LOW);
    digitalWrite(8, HIGH);
    analogWrite(3, 128);
    analogWrite(9, 128);
    delay(3000);
    analogWrite(3, 0);
    analogWrite(9, 0);
    Serial.println("Ejection complete, Next Letter");
  }
  
  delay(50);
  command = "";
}
