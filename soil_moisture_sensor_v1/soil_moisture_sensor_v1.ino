int sensor_pin = A0;
int output_value;

void setup() {
  
  //Setting up serial to port 9600 to help get println for debug
  Serial.begin(9600);

  Serial.println("Setting up pins");

  //Setting up pin 5 for blue led
  pinMode(5, OUTPUT);

  //Setting up pin 4 for red led
  pinMode(4, OUTPUT);

  //Setting up pin 3 for moisture sensor power
  pinMode(3, OUTPUT);

  //Setting up pin A0 for analog moisture sensor reading
  pinMode(sensor_pin, INPUT);

  //Turning off moisture sensor power off by default
  digitalWrite(3, LOW);

  Serial.println("Done setting up pins");

}

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Starting of program");

  while ( count < 5)
  {
    Serial.println("In while loop for lights");
    
    digitalWrite(5, HIGH);
    delay(1000);
  
    digitalWrite(5, LOW);
    delay(1000);
  
    digitalWrite(4, HIGH);
    delay(1000);
 
    digitalWrite(4, LOW);
    delay(1000);

    count++;
  }

  Serial.println("end of setup");

  Serial.println("Setting digital pin 3 high");

  //Turn of red led light to indicate a read is taking place
  digitalWrite(4, HIGH);

  //Turning on moisture sensor power
  digitalWrite(3, HIGH);
  delay(100);

  //Read moisture sensor from analog pin
  output_value = analogRead(sensor_pin);
  Serial.print("Value read = ");
  Serial.println(output_value);

  //Map read value to % of moisture
  output_value = map(output_value, 684, 200, 0, 100);
  Serial.print("Moisture % = ");
  Serial.println(output_value);

  //Turn off moisture power sensor
  digitalWrite(3, LOW);
  delay(2000);

  //Turn off red light
  digitalWrite(4, LOW);

  //Time to wait until next read of moisture sensor
  delay(5000);
}