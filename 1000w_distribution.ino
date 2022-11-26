// Controller for 1000W Home distribution box
// Sep 29, 2019

// v. 2.0 Nov. 26, 2022
// changed code from furnace mode to accessory mode:

// Default is for power to be delivered to the top three outlets
// Accessory mode allows for power to be delivered to the top 3 plus the lower Accessory outlet
// Accessory outlet is only for device chargers or internet router
// NOTE: When Accessory mode is enabled, press system reset button to return to default mode

int freezerPin = 2;
int lowerFridgePin = 3;
int mainFridgePin = 4;
int accessoryModePin = 5;
int standardModeButtonPin = 6;
int accessoryModeButtonPin = 7;
long unsigned startTime, endTime;
boolean standardMode, accessoryMode, standardModeFlag, accessoryModeFlag;
boolean freezerModeFlag = false;
boolean lowerFridgeModeFlag = false;
boolean mainFridgeModeFlag = false;
#define delayTime 500         // delay time between output selections

// Device timing
#define dwellTime 1800000     // 30 minutes on each device (deployment)
//#define dwellTime 60000     // 60 seconds on each device (for testing)
//#define dwellTime 5000      // 5 seconds on each device (for testing)



void setup() {
  Serial.begin(9600);
  pinMode(freezerPin, OUTPUT);
  pinMode(lowerFridgePin, OUTPUT);
  pinMode(mainFridgePin, OUTPUT);
  pinMode(accessoryModePin, OUTPUT);
  pinMode(standardModeButtonPin, OUTPUT);
  digitalWrite(standardModeButtonPin, HIGH);  // enable pullup
  pinMode(accessoryModeButtonPin, OUTPUT);
  digitalWrite(accessoryModeButtonPin, HIGH);   // enable pullup
  digitalWrite(freezerPin, LOW);
  digitalWrite(lowerFridgePin, LOW);
  digitalWrite(mainFridgePin, LOW);

  // default to freezer mode

  standardModeFlag = true;
  accessoryModeFlag = false;
  startTime = millis();         // start clock running
  endTime = startTime + dwellTime;  // run
  standardModeFunction();
}

void loop() {
  // test for button presses
  standardMode = digitalRead(standardModeButtonPin);
  accessoryMode = digitalRead(accessoryModeButtonPin);

  
  if ((standardMode == LOW) && (millis() > (startTime + 500))) {    // revert to standard mode after one circuit in furnace mode
                                                                    // also debounce 500ms to prevent race condition
    standardModeFlag = true;
    accessoryModeFlag = false;
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
  } else if (accessoryMode == LOW) {
    delay(delayTime);
    accessoryModeFlag = true;
    standardModeFlag = false;
    startTime = millis();     // start clock running
    endTime = startTime + dwellTime; // run
  }

  // based on button presses, go to functions
  if (accessoryModeFlag == true) {
    accessoryModeFunction();
  } else {
    standardModeFunction();
  }
}

