// pin 2 - L298 in1
// pin 3 - L298 in2

#define CLOSE_TIME 5000
void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    Serial.begin(9600);
    
    neutral();
}

void loop() {
    if (Serial.available() > 0) {
        char c = Serial.read();
        if (c == 'o') {
            Serial.println("Received signal to open");
            delay(300);
            open();

            // wait for limit switch
            while (!digitalRead(4)) {
                delay(10);
            }

            neutral();

            // give the person time to open the door
            delay(5000);

            // close the door (doesn't really matter how far it goes)
            close();
            delay(CLOSE_TIME);
        } else if (c == 'c') { 
            Serial.println("Received signal to close");
            delay(300);
            close();
            delay(CLOSE_TIME);
        }
        neutral();
    }
}

// turn clockwise to open
void open() {
    digitalWrite(2, 0);
    digitalWrite(3, 1);
}

// turn counterclockwise to close
void close() {
    digitalWrite(2, 1);
    digitalWrite(3, 0);
}

// deactivate motor
void neutral() {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
}

