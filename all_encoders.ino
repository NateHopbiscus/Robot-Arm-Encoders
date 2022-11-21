/*
Code by Nate Hopper
Requires: 
- SCORBOT ER3 Robotic Arm
- 4 Momentary Buttons
- 3 DC Motor Drivers
- 1 ATMEGA 2560
- 1 Analog Thumb Joystick
- 1 Schmidt Trigger Hex Inverter
*/
#define CLW 0   //Clockwise
#define CCW 1   //Counterclockwise
#define STP 2   //Stop

#define BASE 3
#define LOWERARM 4
#define UPPERARM 5
#define WRISTONE 6
#define WRISTTWO 7

int Motor1a = 14;
int Motor1b = 15;
int Motor2a = 4;
int Motor2b = 5;
int Motor3a = 6;
int Motor3b = 7;
int Motor4a = 8;
int Motor4b = 9;
int Motor5a = 10;
int Motor5b = 11;

volatile long baseCount;
volatile long lowerArmCount;
volatile long upperArmCount;
volatile long wrist1Count;
volatile long wrist2Count;

int targetCount = -60;

int bdir = STP;
int ladir = STP;
int uadir = STP;
int w1dir  = STP;
int w2dir = STP;

int motor = 3;


void setup() {
  Serial.begin(9600);
  // pinMode(10, OUTPUT);
  //pinMode(11, OUTPUT);
  pinMode(Motor1a, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2a, OUTPUT);
  pinMode(Motor2b, OUTPUT);
  pinMode(Motor3a, OUTPUT);
  pinMode(Motor3b, OUTPUT);
  pinMode(Motor4a, OUTPUT);
  pinMode(Motor4b, OUTPUT);
  pinMode(Motor5a, OUTPUT);
  pinMode(Motor5b, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(22, INPUT);
  pinMode(23, INPUT);

  attachInterrupt(1, basePulse, FALLING);
  attachInterrupt(0, lowerArmPulse, FALLING);
  attachInterrupt(2, upperArmPulse, FALLING);
  attachInterrupt(3, wrist1Pulse, FALLING);
  attachInterrupt(4, wrist2Pulse, FALLING);

  pinMode(46, INPUT);
  pinMode(47, INPUT);

  pinMode(50, INPUT);
  pinMode(51, INPUT);

}

void loop() {

  int y = analogRead(2);
  int button1 = digitalRead(46);
  int button2 = digitalRead(47);
  int grab = digitalRead(50);
  int release = digitalRead(51);


  Serial.print("Base Count:");
  Serial.println(baseCount);
  Serial.print("Lower Arm Count:");
  Serial.println(lowerArmCount);
  Serial.print("Upper Arm Count:");
  Serial.println(upperArmCount);
  Serial.print("Wrist One Count:");
  Serial.println(wrist1Count);
  Serial.print("Wrist Two Count:");
  Serial.println(wrist2Count);
  Serial.println("----------------");
  Serial.print("Current Motor: ");
  if (motor == 3) {
    Serial.println("BASE");
  } else if (motor == 4) {
    Serial.println("LOWER ARM");
  } else if (motor == 5) {
    Serial.println("UPPER ARM");
  } else if (motor == 6) {
    Serial.println("WRIST ONE");
  } else if (motor == 7) {
    Serial.println("WRIST TWO");
  }
  Serial.print("Current Direction: ");
  if (motor == 3) {
    if (bdir == 0) {
      Serial.println("Clockwise");
    }  else if (bdir == 1) {
      Serial.println("Counterclockwise");
    } else if (bdir == 2) {
      Serial.println("STOPPED");
    }
  } else if (motor == 4) {
    if (ladir == 0) {
      Serial.println("Clockwise");
    } else if (ladir == 1) {
      Serial.println("Counterclockwise");
    } else if (ladir == 2) {
      Serial.println("STOPPED");
    }
  } else if (motor == 5) {
    if (uadir == 0) {
      Serial.println("Clockwise");
    } else if (uadir == 1) {
      Serial.println("Counterclockwise");
    } else if (uadir == 2) {
      Serial.println("STOPPED");
    }
  } else if (motor == 6) {
    if (w1dir == 0) {
      Serial.println("Clockwise");
    } else if (w1dir == 1) {
      Serial.println("Counterclockwise");
    } else if (w1dir == 2) {
      Serial.println("STOPPED");
    }
  } else if (motor == 7) {
    if (w2dir == 0) {
      Serial.println("Clockwise");
    } else if (w2dir == 1) {
      Serial.println("Counterclockwise");
    } else if (w2dir == 2) {
      Serial.println("STOPPED");
    }
  }
  Serial.print("Hand Status: ");
  if(grab == HIGH && release == LOW){
    Serial.println("GRABBING");
  } else if(release == HIGH && grab == LOW){
    Serial.println("RELEASING");
  } else if(release == LOW && grab == LOW){
    Serial.println("AT REST");
  }
  Serial.println("----------------");


  if (button1 == HIGH) {
    motor++;
  } else if (button2 == HIGH) {
    motor--;
  }

  if (motor > 7) {
    motor = 3;
  }
  if (motor < 3) {
    motor = 7;
  }

  switch (motor) {
    case BASE:
      if (0 <= y && y <= 262) {
        digitalWrite(Motor1a, HIGH);
        digitalWrite(Motor1b, LOW);
        bdir = 0;
      } else if (762 <= y && y <= 1023 ) {
        digitalWrite(Motor1a, LOW);
        digitalWrite(Motor1b, HIGH);
        bdir = 1;
      } else if (262 <= y && y <= 762) {
        digitalWrite(Motor1a, LOW);
        digitalWrite(Motor1b, LOW);
        bdir = 2;
      }
      break;
    case LOWERARM:
      if (0 <= y && y <= 262) {
        digitalWrite(Motor2a, HIGH);
        digitalWrite(Motor2b, LOW);
        ladir = 0;
      } else if (762 <= y && y <= 1023 ) {
        digitalWrite(Motor2a, LOW);
        digitalWrite(Motor2b, HIGH);
        ladir = 1;
      } else if (262 <= y && y <= 762) {
        digitalWrite(Motor2a, LOW);
        digitalWrite(Motor2b, LOW);
        ladir = 2;
      }
      break;
    case UPPERARM:
      if (0 <= y && y <= 262) {
        digitalWrite(Motor3a, LOW);
        digitalWrite(Motor3b, HIGH);
        uadir = 0;
      } else if (762 <= y && y <= 1023 ) {
        digitalWrite(Motor3a, HIGH);
        digitalWrite(Motor3b, LOW);
        uadir = 1;
      } else if (262 <= y && y <= 762) {
        digitalWrite(Motor3a, LOW);
        digitalWrite(Motor3b, LOW);
        uadir = 2;
      }
      break;
    case WRISTONE:
      if (0 <= y && y <= 262) {
        digitalWrite(Motor4a, HIGH);
        digitalWrite(Motor4b, LOW);
        w1dir = 0;
      } else if (762 <= y && y <= 1023 ) {
        digitalWrite(Motor4a, LOW);
        digitalWrite(Motor4b, HIGH);
        w1dir = 1;
      } else if (262 <= y && y <= 762) {
        digitalWrite(Motor4a, LOW);
        digitalWrite(Motor4b, LOW);
        w1dir = 2;
      }
      break;
    case WRISTTWO:
      if (0 <= y && y <= 262) {
        digitalWrite(Motor5a, HIGH);
        digitalWrite(Motor5b, LOW);
        w2dir = 0;
      } else if (762 <= y && y <= 1023 ) {
        digitalWrite(Motor5a, LOW);
        digitalWrite(Motor5b, HIGH);
        w2dir = 1;
      } else if (262 <= y && y <= 762) {
        digitalWrite(Motor5a, LOW);
        digitalWrite(Motor5b, LOW);
        w2dir = 2;
      }
      break;
  }

  if (grab == HIGH && release == LOW) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } else if (release == HIGH && grab == LOW) {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  } else if (release == LOW && grab == LOW){
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}

void basePulse() {
  if (bdir == 1) {
    baseCount++;
  } else if (bdir == 0) {
    baseCount--;
  }
}

void lowerArmPulse() {
  if (ladir == 1) {
    lowerArmCount++;
  } else if (ladir == 0) {
    lowerArmCount--;
  }
}

void upperArmPulse() {
  if (uadir == 1) {
    upperArmCount++;
  } else if (uadir == 0) {
    upperArmCount--;
  }
}



void wrist1Pulse() {
  if (w1dir == 1) {
    wrist1Count++;
  } else if (w1dir == 0) {
    wrist1Count--;
  }
}

void wrist2Pulse() {
  if (w2dir == 1) {
    wrist2Count++;
  } else if (w2dir == 0) {
    wrist2Count--;
  }
}

