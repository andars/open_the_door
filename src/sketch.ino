// pin 2 - L298 in1
// pin 3 - L298 in2

// start with clockwise
uint8_t in1 = 0;
uint8_t in2 = 1;

#define CLOSE_TIME 5000

// improvements:
// - limit switches

void open() {
    digitalWrite(2, 0);
    digitalWrite(3, 1);
}

void close() {
    digitalWrite(2, 1);
    digitalWrite(3, 0);
}

void neutral() {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
}

void setup()
{
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    Serial.begin(9600);
    
    digitalWrite(2, 0);
    digitalWrite(3, 0);
}

void loop()
{
    if (Serial.available() > 0) {
        char c = Serial.read();
        if (c == 'o') {
            // open by turning clockwise
            Serial.println("Received signal to open");
            delay(300);
            open();

            while (!digitalRead(4)) {
                delay(10);
            }


            neutral();
            delay(5000);
            close();
            delay(CLOSE_TIME);
        } else if (c == 'c') { 
            // close by turning counterclockwise
            Serial.println("Received signal to close");
            delay(300);
            digitalWrite(2, 1);
            digitalWrite(3, 0);
            delay(CLOSE_TIME);
        }
        neutral();
    }
    /*
    in1 = !in1;
    in2 = !in2;

    digitalWrite(2, in1);
    digitalWrite(3, in2);
    delay(1500);
    */
}
