#define pn(x,y) pinMode(x,y)
#define H HIGH
#define L LOW
#define o OUTPUT
// Motor A connections
#define motorA_enablePin  9 // Enable pin for Motor A (PWM)
#define motorA_input1  10   // Input 1 pin for Motor A
#define motorA_input2  11   // Input 2 pin for Motor A

// Motor B connections
#define motorB_enablePin  6 // Enable pin for Motor B (PWM)
#define motorB_input3  7   // Input 3 pin for Motor B
#define motorB_input4  8   // Input 4 pin for Motor B

int motorSequence[][4] = {
  {H, L, L, H},  // Motor A forward
  {L, H, H, L},  // Motor A backward
  {H, L, L, H},  // Motor B forward
  {L, H, H, H},  // Motor B backward
  {L, H, L, H},  // Turn left
  {H, L, H, L}   // Turn right
};

void setup() {
  Serial.begin(9600);
  pn(motorA_enablePin, o);
  pn(motorA_input1, o);
  pn(motorA_input2, o);

  pn(motorB_enablePin, o);
  pn(motorB_input3, o);
  pn(motorB_input4, o);

  
}

void loop() {
  if (Serial.available() > 0) {
    char letter = Serial.read();
    direction1(letter);
  }
}


void Control(int sequenceIndex) {
  digitalWrite(motorA_input1, motorSequence[sequenceIndex][0]);
  digitalWrite(motorA_input2, motorSequence[sequenceIndex][1]);
  analogWrite(motorA_enablePin, motorSequence[sequenceIndex][2] * 255); 

  digitalWrite(motorB_input3, motorSequence[sequenceIndex][2]);
  digitalWrite(motorB_input4, motorSequence[sequenceIndex][3]);
  analogWrite(motorB_enablePin, motorSequence[sequenceIndex][2] * 255); 
}


void direction1(char letter) {
  if (letter == 'f') {
    Control(0); // Move forward
  } else if (letter == 'b') {
    Control(1); // Move backward
  } else if (letter == 's') {
    Control(2); // Stop
  } else if (letter == 'l') {
    Control(4); // Turn left
  } else if (letter == 'r') {
    Control(5); // Turn right
  }
}