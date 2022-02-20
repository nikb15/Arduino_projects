int recived_state;
int current_state;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {
    recived_state = Serial.read();
    Serial.println(recived_state);
    if (recived_state != current_state)
    {
      current_state = recived_state;
      
      switch (current_state)
      {
        case 1:
          Serial.println("User Moving toward right");
          break;
        case 2:
          Serial.println("USerMoving towwards left");
          break;
        case 3:
          Serial.println("USerMoving towwards up");

          break;
        case 4:
          Serial.println("USerMoving towwards down");

          break;
      }
    }
  }
}
