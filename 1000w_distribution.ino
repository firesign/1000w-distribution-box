//Controller for 1000W Home distribution box
//Jan. 18, 2022

int freezerPin = 2;
int lowerFridgePin = 3;
int mainFridgePin = 4;
int furnaceModePin = 5;
int standardModeButtonPin = 6;
int furnaceModeButtonPin = 7;
long unsigned startTime, endTime;
boolean standardMode, furnaceMode, standardModeFlag, furnaceModeFlag;
boolean freezerModeFlag = false;
boolean lowerFridgeModeFlag = false;
boolean mainFridgeModeFlag = false;
#define delayTime 500         // delay time between output selections

// Device timing
#define dwellTime 900000   // 15 minutes on each device (deployment)
//#define dwellTime 60000       // 60 seconds on each device (for testing)
//#define dwellTime 10000     // 10 seconds on each device (for testing)

// FUNCTIONS

void standardModeFunction()
{
  // freezerMode
  if (freezerModeFlag == true) {
    furnaceModeFlag = false;
    digitalWrite(furnaceModePin, LOW);  // first ensure that furnace is turned off
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
    furnaceModeFlag = false;
    digitalWrite(furnaceModePin, LOW);  // first ensure that furnace is turned off
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
    furnaceModeFlag = false;
    digitalWrite(furnaceModePin, LOW);  // first ensure that furnace is turned off
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


void furnaceModeFunction()
{
  //Serial.println("furnace mode");
  digitalWrite(freezerPin, LOW);
  digitalWrite(lowerFridgePin, LOW);
  digitalWrite(mainFridgePin, LOW);
  digitalWrite(furnaceModePin, HIGH);
  unsigned long currTime = millis();
  unsigned long timeLeft = endTime - currTime;
  Serial.println(timeLeft);
  if (currTime > endTime) {
    digitalWrite(furnaceModePin, LOW);
    furnaceModeFlag = false;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(freezerPin, OUTPUT);
  pinMode(lowerFridgePin, OUTPUT);
  pinMode(mainFridgePin, OUTPUT);
  pinMode(furnaceModePin, OUTPUT);
  pinMode(standardModeButtonPin, OUTPUT);
  digitalWrite(standardModeButtonPin, HIGH);  // enable pullup
  pinMode(furnaceModeButtonPin, OUTPUT);
  digitalWrite(furnaceModeButtonPin, HIGH);   // enable pullup
  digitalWrite(freezerPin, LOW);
  digitalWrite(lowerFridgePin, LOW);
  digitalWrite(mainFridgePin, LOW);

  // default to freezer mode

  standardModeFlag = true;
  furnaceModeFlag = false;
  startTime = millis();         // start clock running
  endTime = startTime + dwellTime;  // run
  standardModeFunction();
}

void loop() {
  // test for button presses
  standardMode = digitalRead(standardModeButtonPin);
  furnaceMode = digitalRead(furnaceModeButtonPin);

  

  if ((standardMode == LOW) && (millis() > (startTime + 500))) {    // revert to standard mode after one circuit in furnace mode
                                                                    // also debounce 500ms to prevent race condition
    standardModeFlag = true;
    furnaceModeFlag = false;
    startTime = millis();         // start clock running
    endTime = startTime + dwellTime;  // run

     // Rotate mode
    if (freezerModeFlag == true) {
      freezerModeFlag = false;
      lowerFridgeModeFlag = true;
    } else if (lowerFridgeModeFlag == true) {
      lowerFridgeModeFlag = false;
      mainFridgeModeFlag = true;
    } else {
      mainFridgeModeFlag = false;
      freezerModeFlag = true;
    }
  } else if (furnaceMode == LOW) {
    delay(delayTime);
    furnaceModeFlag = true;
    standardModeFlag = false;
    startTime = millis();     // start clock running
    endTime = startTime + dwellTime; // run
  }

  // based on button presses, go to functions
  if (furnaceModeFlag == true) {
    furnaceModeFunction();
  } else {
    standardModeFunction();
  }
}
