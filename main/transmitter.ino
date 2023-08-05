
const int trigpin = 14;
const int echopin = 12;
long duration;
float distance;
float combined_distance = 0;
float current_distance = 0;
float absolute_current_distance = 0;
float difference_distance = 0;
float transmitted = 0;
int looping = 15;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(echopin, INPUT);     // GPIO 12 Input ECHO Pin
  pinMode(trigpin, OUTPUT);     // GPIO 14 Output TRIG Pin
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(trigpin, HIGH);
  delayMicroseconds (15);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin,HIGH);
  distance = duration*0.034/2;
  combined_distance = combined_distance + distance;
//  Serial.println(distance);
  looping=looping-1;
  if (looping<1){
    looping=15;
    current_distance = combined_distance/looping;
    absolute_current_distance = abs(current_distance);
    difference_distance = transmitted - absolute_current_distance;
    if (difference_distance > 0.3){             // if the difference in water level is 0.3mm we make a entry
      transmitted = absolute_current_distance;
      Serial.println(transmitted); //sending data to serial for broadcast
      }
    combined_distance = 0;
//  Serial.println("COMBINED DISTANCE");
    Serial.println(transmitted);    
    }
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(50);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(950);                      // Wait for two seconds (to demonstrate the active low LED)
}
