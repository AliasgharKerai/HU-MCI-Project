void Update_Ultra_Sonic()
{
    // Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
    unsigned long currentMillis = millis();
    // Serial.println(currentMillis-start);

    if ((currentMillis - start >= 0) && (currentMillis - start <= low_time))
    {
        if (ultrasonic_flag == 1)
        {
            digitalWrite(Trig, LOW);
        }
        else if (ultrasonic_flag == 2)
        {
            digitalWrite(Trig2, LOW);
        }
        trig_flag = LOW;
    }
    else if ((currentMillis - start > low_time) && (currentMillis - start <= high_time))
    {
        if (ultrasonic_flag == 1)
        {
            digitalWrite(Trig, HIGH);
        }
        else if (ultrasonic_flag == 2)
        {
            digitalWrite(Trig2, HIGH);
        }
    }
    else if (currentMillis - start > high_time)
    {
        if (ultrasonic_flag == 1)
        {
            digitalWrite(Trig, LOW);
        }
        else if (ultrasonic_flag == 2)
        {
            digitalWrite(Trig2, LOW);
        }
        trig_flag = HIGH;
    }
    if (trig_flag == HIGH)
    {
        if (ultrasonic_flag == 1)
        {
            duration = pulseIn(echo, HIGH);
            cm = microsecondsToCentimeters(duration);
            if (cm < 15) // idea here is to basically turn around if someone gets to close and hit them
            {
                // moveForward();
                // delay(500); // need to change delay to ensure that 180 rotation is happening
                // stopper();
                attack();
            }
            // Serial.print("cm1 =");
            // Serial.println(cm);
            ultrasonic_flag = 2;
        }
        else if (ultrasonic_flag == 2)
        {
            duration2 = pulseIn(echo2, HIGH);
            cm2 = microsecondsToCentimeters(duration2);
            if (cm2 < 15)
            {
                turn_right_one();
                delay(2000);
                stopper();
            }
            // Serial.print("cm2 =");
            // Serial.println(cm2);
            ultrasonic_flag = 1;
        }
        trig_flag = LOW;
        start = millis();
        // Serial.print("Distance=");
        // Serial.print("\t");
        // Serial.print(cm);
        // Serial.print("\n");
    }
}