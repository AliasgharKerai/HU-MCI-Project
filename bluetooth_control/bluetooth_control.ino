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
// bluetooth implementation
int command_detect=0;     //For different color detection
char received;         //Characters to be send/receieve on UART
// IR sensor implementation
int IRSensor = 27; // connect IR sensor module to TIVA E1
int front_IR = 0;
boolean dodged_it = false;

void setup() {
  Serial.begin(9600); //Serial initializing for Debugging
  
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

  // IR sensor
  pinMode(IRSensor, INPUT);
}

void loop() {
   dodged_it = false;
  //Following Condition is true whenever we send a command from Bluetooth Terminal App
  if(Serial.available()>0){
     command_detect=Serial.read();
    //Read the bluetoot data and store it in colorDetect variable using Serial.read() command here


    //Following lines help debugging by printing whatever character recieved on Serial Monitor
    char Rec = char(command_detect);
    if (Rec != '0')
    {
    Serial.println(Rec); //This is to visualise the received character on the serial monitor
    }  
  }
  
  front_IR = digitalRead(IRSensor);//Front IR sensor
  Serial.println(front_IR);
  
  if(front_IR == 0 && dodged_it != true){
    //rotate_right_360();
    move_backward();
    delay(200);
    rotate_right_360();
    delay(450);
    Serial.println("ROTATES!");
    changeDirection(command_detect);  
  }

  else if((front_IR == 1)){
    changeDirection(command_detect);  
  }
}

// task 3
void changeDirection(char c){


  //To be used for task03 only
   // move_forward();
   // delay(700);
   // move_backward();
   // delay(700);
   // move_right_360();
   // delay(700);
   // move_left_360();
   // delay(700);
   // rotate_right_360();
   // delay(4000);
   // rotate_left_360();
  //  delay(4000);
   // rotate_right_in_circle();
   // delay(4000);
  //  rotate_left_in_circle();
   // delay(4000);
   // stop_motion();   
   // delay(4000); 
//if(front_IR > 550){
if (c=='F')
{
move_forward();
Serial.println("forward is called!");
}

else if (c=='B')
{

move_backward();
Serial.println("backward is called!");
}


else if (  c=='R')
{
move_right_360();
Serial.println("right is called!");
}

else if (c=='L')
{
move_left_360();
Serial.println("left is called!");
}

else if (c=='S')

{

stop_motion();

}
}

void move_forward(){
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 175);//69%% duty cycle
    
    //motB
    analogWrite(enB, 175);//69%% duty cycle
}

void move_backward(){
    // MOTOR A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // MOTOR B
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    //motA
    analogWrite(enA, 175);//69%% duty cycle
    
    //motB
    analogWrite(enB, 175);//69%% duty cycle
}

void move_left_360(){
// B motor will be accelerating faster than A, hence the car will turn left
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 50);//1.96% duty cycle
      
    //motB
    analogWrite(enB, 200);//100% duty cycle
}

void rotate_right_in_circle(){
// A motor will be accelerating faster than B, hence the car will turn right
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 255);//68.6% duty cycle
      
    //motB
    analogWrite(enB, 125);//39.2% duty cycle
}

void rotate_left_in_circle(){
// A motor will be accelerating faster than B, hence the car will turn right
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 125);//68.6% duty cycle
      
    //motB
    analogWrite(enB, 255);//39.2% duty cycle
}

void rotate_right_360(){
// A motor will be accelerating faster than B, hence the car will turn right
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    //motA
    analogWrite(enA, 255);//68.6% duty cycle
      
    //motB
    analogWrite(enB, 255);//39.2% duty cycle
}

void rotate_left_360(){
// A motor will be accelerating faster than B, hence the car will turn right
    // MOTOR A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 255);//68.6% duty cycle
      
    //motB
    analogWrite(enB, 255);//39.2% duty cycle
}

void move_right_360(){
// A motor will be accelerating faster than B, hence the car will turn right
    // MOTOR A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 200);//100% duty cycle
      
    //motB
    analogWrite(enB, 50);//1.96% duty cycle
}

void stop_motion(){
    // MOTOR A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // MOTOR B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    //motA
    analogWrite(enA, 0);//100% duty cycle
      
    //motB
    analogWrite(enB, 0);//10% duty cycle
}
