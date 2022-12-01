// Motor A, TivaC and L298N connections
int enA = 26;   //ENABLE pin (PD3) for Motor A to provide PWM 
int in1 = 11;   //IN1 pin (PA2) for Motor A for direction
int in2 = 12;   //IN2 pin (PA3) for Motor A for direction

// Motor B, TivaC and L298N connections
int enB = 25;   //ENABLE pin (PD2) for Motor B to provide PWM 
int in3 = 29;   //IN3 pin (PE3) for Motor B for direction
int in4 = 28;   //IN4 pin (PE2) for Motor B for direction
  
const int SW2 = 17;   //Pin number for Switch SW2
bool direction_forw_back = true;  //Flag for clockwise or anti-clockwise direction

void setup() {
  Serial.begin(115255); //Serial initializing for Debugging
  
  //Specify pinModes for enA, in1 and in2 below
  // MOTOR A
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);

  // MOTOR B
  pinMode(enB,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  //Initialize SW2 Switch as Input
  pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
}

void loop() {
    // Make the motor run clockwise direction using in1 and in2 states below
//    changeDirection();
//    digitalRead(SW2)
//spin_anticlockwise();
changeDirection();

}

// task 3
void changeDirection(){
//  Serial.println(digitalRead(SW2));
    if(digitalRead(SW2) == 0){
//      move_right();
//      move_left();
 move_forward();
  delay(2000);
  move_backward();
 delay(2000);
//spin_anticlockwise();
// delay(2000);
 move_right();
   delay(2000);
    move_left();
   
     delay(2000);
     spin_clockwise();
     delay(2000);
     
//      if(direction_forw_back==true){       
////        for(int k=0; k<3;k++){
//          move_forward();
////          delay(2550);
//          move_right();
////          delay(2550);
////          move_left();
////          delay(2550);
////        }       
//        direction_forw_back = false;
//      }
//    else if(direction_forw_back==false){
////      move_backward();
////      delay(2550);
//      direction_forw_back = true;
//    }
    
   }
}

void move_forward(){
    // MOTOR A
    analogWrite(in1, 0);
    analogWrite(in2, 255);
    // MOTOR B
    analogWrite(in4, 0);
    analogWrite(in3, 255);
    for (int i=0; i<100; i++){//for 50 Hz
        analogWrite(enA, 255);//100% duty cycle
        analogWrite(enB, 255);//100% duty cycle
    }
}

void move_backward(){
    // MOTOR A
    analogWrite(in1, 255);
    analogWrite(in2, 0);
    // MOTOR B
    analogWrite(in4, 255);
    analogWrite(in3, 0);
    for (int i=0; i<100; i++){//for 50 Hz
        analogWrite(enA, 255);//100% duty cycle
        analogWrite(enB, 255);//100% duty cycle
    }
}

void move_left(){
    // MOTOR A
    analogWrite(in2, 0);
    analogWrite(in1, 255);
    // MOTOR B
    analogWrite(in3, 0);
    analogWrite(in4, 255);
    for (int i=0; i<200; i++){//for 50 Hz
        analogWrite(enA, 255);//100% duty cycle
        analogWrite(enB, 100);//100% duty cycle
    }
}

void move_right(){
    // MOTOR A
    analogWrite(in2, 0);
    analogWrite(in1, 255);
    // MOTOR B
    analogWrite(in3, 0);
    analogWrite(in4, 255);
    for (int i=0; i<200; i++){//for 50 Hz
        analogWrite(enB, 255);//100% duty cycle
        analogWrite(enA, 100);//100% duty cycle
    }
}

void spin_anticlockwise(){

    // MOTOR A
    analogWrite(in2, 0);
    analogWrite(in1, 255);
    // MOTOR B
    analogWrite(in3, 0);
    analogWrite(in4, 255);
    for (int i=0; i<50; i++){//for 50 Hz
        analogWrite(enB, 255);//100% duty cycle
        analogWrite(enA, 0);//100% duty cycle
    }
}
void spin_clockwise(){
     // MOTOR A
    analogWrite(in2, 0);
    analogWrite(in1, 255);
    // MOTOR B
    analogWrite(in3, 0);
    analogWrite(in4, 255);
    for (int i=0; i<50; i++){//for 50 Hz
        analogWrite(enB, 0);//100% duty cycle
        analogWrite(enA, 255);//100% duty cycle
    }
}
