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

  //Setting up pin 2 for green led
  pinMode(2, OUTPUT);

  //Setting up pin A0 for analog moisture sensor reading
  pinMode(sensor_pin, INPUT);

  //Turning off all by default
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);


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

    digitalWrite(2, HIGH);
    delay(1000);

    digitalWrite(2, LOW);
    delay(1000);

    count++;
  }

  Serial.println("end of setup");

  Serial.println("Setting digital pin 3 high");

  //Turn of green led light to indicate a read is taking place
  digitalWrite(2, HIGH);

  //Turning on moisture sensor power
  digitalWrite(3, HIGH);
  delay(100);

  //Read moisture sensor from analog pin
  output_value = analogRead(sensor_pin);
  Serial.print("Value read = ");
  Serial.println(output_value);

  //If we get an invalid signal need to turn on red light to indicate an error has
  //occurred//

  if ( output_value > 1003 )
  {
    Serial.print("INVALID VALUE READ FROM SOIL MOISTURE SENSOR.  VALUE = ");
    Serial.print(output_value);
    digitalWrite(4, HIGH);
    delay(5000);

    digitalWrite(4, LOW);
  }
  else
  {

    //Map read value to % of moisture
    output_value = map(output_value, 1003, 271, 0, 100);
    Serial.print("Moisture % = ");
    Serial.println(output_value);
  
    //Turn off moisture power sensor
    digitalWrite(3, LOW);
    delay(1000);
  
    //Turn off red light
    digitalWrite(2, LOW);
  }

  //Time to wait until next read of moisture sensor
  delay(5000);
}
