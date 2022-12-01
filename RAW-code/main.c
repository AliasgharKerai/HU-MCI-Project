// Motor A, TivaC and L298N connections
int enA = 26; // ENABLE pin (PD3) for Motor A to provide PWM
int in1 = 11; // IN1 pin (PA2) for Motor A for direction
int in2 = 12; // IN2 pin (PA3) for Motor A for direction

// Motor B, TivaC and L298N connections
int enB = 25; // ENABLE pin (PD2) for Motor B to provide PWM
int in3 = 29; // IN3 pin (PE3) for Motor B for direction
int in4 = 28; // IN4 pin (PE2) for Motor B for direction

// Motor C,
int enC = 24; // ENABLE pin (PD1) for Motor B to provide PWM
int in5 = 9;  // IN3 pin (PA6) for Motor B for direction
int in6 = 10; // IN4 pin (PA7) for Motor B for direction

// Motor D
int enD = 32; // ENABLE pin (PD7) for Motor B to provide PWM
int in7 = 3;  // IN3 pin (PB0) for Motor D for direction
int in8 = 4;  // IN4 pin (PB1) for Motor D for direction

// Motor E - Front Attack
int enE = 23;  // ENABLE pin (PD0) for Motor B to provide PWM
int in9 = 15;  // IN3 pin (PB7) for Motor D for direction
int in10 = 14; // IN4 pin (PB6) for Motor D for direction

// Motor F - Back Attack
int enF = 19;  // ENABLE pin (PB2) for Motor B to provide PWM
int in11 = 31; // IN3 pin (PF4) for Motor D for direction
int in12 = 30; // IN4 pin (PF1) for Motor D for direction

// Ultrasonic - front
int echo1 = 37; // PC4
int trig1 = 38; // PB3

//
// Ultrasonic - back
int echo2 = 6; // PE5
int trig2 = 5; // PE4
//
// IRs
int IR = 36;  // PC5 - back
int IR2 = 35; // PC6 - front

////////////////////////////////////////////////////
// Time Update Variables

// To measure pulse width and distance in cm
unsigned long duration = 0, cm = 0;

void setup()
{
    // Initialize Baud Rate at 9600 below
    Serial.begin(9600);

    // MOTOR A
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    // MOTOR B
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // MOTOR C
    pinMode(enC, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);

    // MOTOR D
    pinMode(enD, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);

    // MOTOR E
    pinMode(enE, OUTPUT);
    pinMode(in9, OUTPUT);
    pinMode(in10, OUTPUT);

    // MOTOR F
    pinMode(enF, OUTPUT);
    pinMode(in11, OUTPUT);
    pinMode(in12, OUTPUT);

    // Ultrasonic 1
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT);

    // Ultrasonic 2
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT);

    //  // IR 1
    pinMode(IR, INPUT);
    pinMode(IR2, INPUT);

    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
}

long ultrasonicFront = 0, ultrasonicBack = 0;
int IRFront = 0, IRBack = 0;
int frontAttack = 0, backAttack = 0;

int ultrasonicState = 0;

void loop()
{

    //    delay(400);
    if (Serial.available() > 0)
    {
        //        Serial.println("Receinving ");
        char received = char(Serial.read());

        //        Serial.println(received);

        enableMovement(received);
    }

    if (!ultrasonicState)
    {
        ultrasonicFront = ultraSonicFrontCheck();
        IRFront = digitalRead(IR2);

        ultrasonicState = 1;
    }
    else
    {
        ultrasonicBack = ultraSonicBackCheck();
        IRBack = digitalRead(IR);
        ultrasonicState = 0;
    }

    //    if (!IRFront)
    //    {
    //
    //        Serial.println("Run front");
    //        frontAttack++;
    //         stopBack();
    //                 runFrontAttack();
    //    }
    if (ultrasonicBack < 30 && !IRBack)
    {

        //        Serial.println("Run Back");
        backAttack++;
        stopFront();
        runBackAttack();
    }
    else if (!IRFront)
    {
        //        Serial.println("Stop");
        //        stopAttack();
        // Serial.println("Run front");
        frontAttack++;
        stopBack();
        runFrontAttack();
    }
    else
    {
        stopAttack();
    }

    //    Serial.print("IR front: ");
    //    Serial.print(IRFront);
    //    Serial.print(", IR back: ");
    //    Serial.println(IRBack);
    //

    if (frontAttack + backAttack >= 500)
    {

        Serial.print("Front attack: ");
        Serial.print(frontAttack);
        Serial.print(" - Back attack: ");
        Serial.print(backAttack);
        Serial.print(" - Total attack: ");
        Serial.println(frontAttack + backAttack);
    }
}

void stopFront()
{
    digitalWrite(in9, LOW);
    digitalWrite(in10, LOW);
    analogWrite(enE, 0);
}

void stopBack()
{
    digitalWrite(in11, LOW);
    digitalWrite(in12, LOW);
    analogWrite(enF, 0);
}

void stopAttack()
{
    digitalWrite(in9, LOW);
    digitalWrite(in10, LOW);
    digitalWrite(in11, LOW);
    digitalWrite(in12, LOW);

    analogWrite(enE, 0);
    analogWrite(enF, 0);
}

void runBackAttack()
{

    digitalWrite(in11, LOW);
    digitalWrite(in12, HIGH);
    analogWrite(enF, 255);
}

void runFrontAttack()
{

    digitalWrite(in9, LOW);
    digitalWrite(in10, HIGH);
    analogWrite(enE, 255);
}

void enableMovement(char detect)
{

    //  Serial.println(detect);
    if (detect == 'F')
    {
        //        Serial.println("Move forward");
        moveForward();
    }
    else if (detect == 'B')
    {
        //        Serial.println("Move Backward");
        moveBackward();
    }

    else if (detect == 'R')
    {
        //        Serial.println("Move right");
        moveRight();
    }
    else if (detect == 'L')
    {
        //        Serial.println("Move left");
        moveLeft();
    }

    else
    {
        //        Serial.println("Stop");
        stopMovement();
    }
}

void stopMovement()
{
    // MOTOR A
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(enA, 0);
    // MOTOR B
    analogWrite(in4, 0);
    analogWrite(in3, 0);
    analogWrite(enB, 0);

    // MOTOR C
    analogWrite(in5, 0);
    analogWrite(in6, 0);
    analogWrite(enC, 0);

    // MOTOR D
    analogWrite(in7, 0);
    analogWrite(in8, 0);
    analogWrite(enD, 0);
}

void moveForward()
{

    // MOTOR A
    analogWrite(in1, 255);
    analogWrite(in2, 0);
    // MOTOR B
    analogWrite(in4, 0);
    analogWrite(in3, 255);

    // Motor C
    analogWrite(in5, 255);
    analogWrite(in6, 0);

    // MOTOR D
    analogWrite(in7, 0);
    analogWrite(in8, 255);
    //

    analogWrite(enA, 255); // 100% duty cycle
    analogWrite(enB, 255); // 100% duty cycle
    analogWrite(enC, 255); // 100% duty cycle
    analogWrite(enD, 255); // 100% duty cycle
}

void moveBackward()
{
    // MOTOR A
    analogWrite(in1, 0);
    analogWrite(in2, 255);
    // MOTOR B
    analogWrite(in4, 255);
    analogWrite(in3, 0);

    // Motor C
    analogWrite(in5, 0);
    analogWrite(in6, 255);

    // MOTOR D
    analogWrite(in7, 255);
    analogWrite(in8, 0);
    //

    analogWrite(enA, 255); // 100% duty cycle
    analogWrite(enB, 255); // 100% duty cycle
    analogWrite(enC, 255); // 100% duty cycle
    analogWrite(enD, 255); // 100% duty cycle
}

void moveRight()
{

    // MOTOR A - BACK
    analogWrite(in1, 255);
    analogWrite(in2, 0);
    // MOTOR B
    analogWrite(in4, 255);
    analogWrite(in3, 0);

    // Motor C
    analogWrite(in5, 0);
    analogWrite(in6, 255);

    // MOTOR D
    analogWrite(in7, 255);
    analogWrite(in8, 0);

    analogWrite(enA, 255); // 100% duty cycle
    analogWrite(enB, 255); // 100% duty cycle
    analogWrite(enC, 255); // 100% duty cycle
    analogWrite(enD, 255); // 100% duty cycle
}

void moveLeft()
{
    // MOTOR A
    analogWrite(in1, 0);
    analogWrite(in2, 255);
    // MOTOR B - BACK
    analogWrite(in4, 0);
    analogWrite(in3, 255);

    // Motor C
    analogWrite(in5, 0);
    analogWrite(in6, 255);

    // MOTOR D
    analogWrite(in7, 255);
    analogWrite(in8, 0);

    analogWrite(enA, 255); // 100% duty cycle
    analogWrite(enB, 255); // 100% duty cycle
    analogWrite(enC, 255); // 100% duty cycle
    analogWrite(enD, 255); // 100% duty cycle
}

long ultraSonicBackCheck()
{
    //  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    duration = pulseIn(echo2, HIGH);          // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
    cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
    // Sending through serial port to print on Monitor
    //    Serial.print("Distance - back =  ");
    //    Serial.print(cm);
    //    Serial.print("\n");
    return cm;
}

long ultraSonicFrontCheck()
{
    // Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
    digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);

    duration = pulseIn(echo1, HIGH);          // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
    cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
    // Sending through serial port to print on Monitor
    //    Serial.print("Distance - front =  ");
    //    Serial.print(cm);
    //    Serial.print("\n");

    return cm;
}

////////////////////////////////////////////////////
// Conversion of microsecond to centimeter
long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // convert speed of sound from m/s to cm/us
    unsigned long distance = 0.034 * microseconds;

    // We take half of the distance travelled since its a reflected wave
    return distance / 2;
}