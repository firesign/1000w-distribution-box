void standardModeFunction()
{
  // freezerMode
  if (freezerModeFlag == true) {
    //accessoryModeFlag = false;

    //digitalWrite(accessoryModePin, LOW);  // first ensure that accessory is turned off
    digitalWrite(freezerPin, HIGH);
    
    digitalWrite(lowerFridgePin, LOW);
    digitalWrite(mainFridgePin, LOW);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(freezerPin, LOW);
      freezerModeFlag = false;
      lowerFridgeModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
    // lowerFridgeMode
  } else if (lowerFridgeModeFlag == true) {
    //accessoryModeFlag = false;
    //digitalWrite(accessoryModePin, LOW);  // first ensure that accessory is turned off
    digitalWrite(freezerPin, LOW);
    
    digitalWrite(lowerFridgePin, HIGH);
    digitalWrite(mainFridgePin, LOW);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(lowerFridgePin, LOW);
      lowerFridgeModeFlag = false;
      mainFridgeModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
  } else {  // mainFridgeMode
    //accessoryModeFlag = false;
    //digitalWrite(accessoryModePin, LOW);  // first ensure that accessory is turned off
    digitalWrite(freezerPin, LOW);
    
    digitalWrite(lowerFridgePin, LOW);
    digitalWrite(mainFridgePin, HIGH);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(mainFridgePin, LOW);
      mainFridgeModeFlag = false;
      freezerModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
  }
}

void accessoryModeFunction()
{
  // freezerMode
  if (freezerModeFlag == true) {
    accessoryModeFlag = true;

    digitalWrite(accessoryModePin, HIGH);  // first ensure that accessory is turned on
    digitalWrite(freezerPin, HIGH);
    
    digitalWrite(lowerFridgePin, LOW);
    digitalWrite(mainFridgePin, LOW);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(freezerPin, LOW);
      freezerModeFlag = false;
      lowerFridgeModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
    // lowerFridgeMode
  } else if (lowerFridgeModeFlag == true) {
    accessoryModeFlag = true;
    digitalWrite(accessoryModePin, HIGH);  // first ensure that accessory is turned off
    digitalWrite(freezerPin, LOW);
    
    digitalWrite(lowerFridgePin, HIGH);
    digitalWrite(mainFridgePin, LOW);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(lowerFridgePin, LOW);
      lowerFridgeModeFlag = false;
      mainFridgeModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
  } else {  // mainFridgeMode
    accessoryModeFlag = true;
    digitalWrite(accessoryModePin, HIGH);  // first ensure that accessory is turned off
    digitalWrite(freezerPin, LOW);
    
    digitalWrite(lowerFridgePin, LOW);
    digitalWrite(mainFridgePin, HIGH);
    unsigned long currTime = millis();
    if (currTime > endTime) {
      digitalWrite(mainFridgePin, LOW);
      mainFridgeModeFlag = false;
      freezerModeFlag = true;
      delay(delayTime);
      startTime = millis();     // start clock running
      endTime = startTime + dwellTime; // run
    }
  }
}


