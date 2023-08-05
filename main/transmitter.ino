// changing the difference from percentage to cm
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
int reading_count = 0;
int two_minutes = 8;



// average refill rate is about 0.25cm per minute

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
  if(transmitted==0){
    combined_distance = combined_distance + distance;
    reading_count=reading_count+1;
  }


  float cm_difference = (abs(distance - transmitted));
//   Serial.println("percentage_difference:");
//   Serial.println(percentage_difference);
  if(cm_difference<1){  //if readings are transmitted every 15 seconds difference should not be more than 1cm
    combined_distance = combined_distance + distance;
    reading_count=reading_count+1;
  }
  
//  Serial.println(distance);
  if (looping<1){
    // Serial.println("Last Transmitted:");
    // Serial.println(transmitted);
    looping=15;
    current_distance = combined_distance/reading_count;
    absolute_current_distance = abs(current_distance);
    float transmit_cm_difference = (abs(absolute_current_distance - transmitted));
//     Serial.println("transmit_percentage_difference:");
//     Serial.println(transmit_percentage_difference);    
    if(transmit_cm_difference < 1 && transmit_cm_difference > 0.3){
      transmitted = absolute_current_distance;
      // Serial.println("Absolute DISTANCE");
      Serial.println(transmitted);
      two_minutes=8;   //resetting the two minute counter if data transmitted
    }
    else if(transmitted==0){
      transmitted = absolute_current_distance; // We are not transmitting, just setting transmitted to a referencable value.
      // Serial.println("Initial DISTANCE");
      Serial.println(transmitted);
      two_minutes=8; //resetting the two minute counter if data transmitted
    }
    else if(two_minutes<1){
      transmitted = absolute_current_distance; // We are not transmitting, just setting transmitted to a referencable value.
      if (isnan(transmitted)) {       //if reading is totally out of specs we reset the caliberation.
        // Serial.println("Resetting / Re-Caliberating");
        transmitted=0;
      } 
      else {
        // Serial.println("Every Two Minute Transmission");
        Serial.println(transmitted);
        // Serial.println("combined_distance");
        // Serial.println(combined_distance);
        // Serial.println("reading_count");
        // Serial.println(reading_count);
        two_minutes=8;
      }
      
    }
    two_minutes=two_minutes-1;
    combined_distance = 0;
    reading_count = 0;   
    }  
  looping=looping-1;
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(50);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(950);                      // Wait for two seconds (to demonstrate the active low LED)
}
