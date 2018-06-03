/*
 * Soil moisture sensor program
 * Kevin Orey
 */

 #include <LiquidCrystal.h>
 LiquidCrystal lcd(12,11,6,7,8,9);

#define sensor_pin A0
int output_value;

/*
 * Use defines to save 4 bytes of int
 */
#define RED_PIN 4
#define BLUE_PIN 5
#define GREEN_PIN 2
#define MOISTURE_SENSOR_1 3
#define NO_MOISTURE 1003
#define SATURATED_SOIL 200
#define NEED_TO_WATER_LEVEL 50

void setup() {

  //Setup lcd screen
  lcd.begin(16,2);
  lcd.print("Starting program");
  
  //Setting up serial to port 9600 to help get println for debug
  Serial.begin(9600);

  Serial.println(F("Setting up pins"));

  //Setting up pin 5 for blue led
  pinMode(BLUE_PIN, OUTPUT);

  //Setting up pin 4 for red led
  pinMode(RED_PIN, OUTPUT);

  //Setting up pin 3 for moisture sensor power
  pinMode(MOISTURE_SENSOR_1, OUTPUT);

  //Setting up pin 2 for green led
  pinMode(GREEN_PIN, OUTPUT);

  //Setting up pin A0 for analog moisture sensor reading
  pinMode(sensor_pin, INPUT);

  //Turning off all by default
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(MOISTURE_SENSOR_1, LOW);
  digitalWrite(GREEN_PIN, LOW);


  Serial.println(F("Done setting up pins"));

  lcd.clear();
  lcd.print("Done setting up pins");

}

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:

  lcd.print("Starting program");
  delay(100);
  lcd.clear();
  
  Serial.println(F("Starting of program"));

  while ( count < 2)
  {
    Serial.println(F("In while loop for lights"));
    
    digitalWrite(BLUE_PIN, HIGH);
    delay(1000);
  
    digitalWrite(BLUE_PIN, LOW);
    delay(1000);
  
    digitalWrite(RED_PIN, HIGH);
    delay(1000);
 
    digitalWrite(RED_PIN, LOW);
    delay(1000);

    digitalWrite(GREEN_PIN, HIGH);
    delay(1000);

    digitalWrite(GREEN_PIN, LOW);
    delay(1000);

    count++;
  }


  lcd.print("Done starting program");
  delay(100);
  lcd.clear();

  Serial.println(F("end of setup"));

  Serial.println(F("Setting digital pin 3 high"));

  //Turn of green led light to indicate a read is taking place
  digitalWrite(GREEN_PIN, HIGH);

  //Turning on moisture sensor power
  digitalWrite(MOISTURE_SENSOR_1, HIGH);
  delay(100);

  lcd.print("Reading sensor 1");
  delay(100);
  lcd.clear();
  
  //Read moisture sensor from analog pin
  output_value = analogRead(sensor_pin);
  Serial.print("Value read = ");
  Serial.println(output_value);

  lcd.print("Value read = ");
  lcd.print(output_value);
  delay(1000);
  lcd.clear();

  //If we get an invalid signal need to turn on red light to indicate an error has occurred
  if ( output_value > NO_MOISTURE )
  {
    Serial.print("INVALID VALUE READ FROM SOIL MOISTURE SENSOR.  VALUE = ");
    Serial.print(output_value);
    digitalWrite(RED_PIN, HIGH);
    delay(5000);

    digitalWrite(RED_PIN, LOW);
  }
  else
  {

    //Map read value to % of moisture
    output_value = map(output_value, NO_MOISTURE, SATURATED_SOIL, 0, 100);
    Serial.print("Moisture % = ");
    Serial.println(output_value);
  
    //Turn off moisture power sensor
    digitalWrite(MOISTURE_SENSOR_1, LOW);
    delay(1000);
  
    //Turn off red light
    digitalWrite(GREEN_PIN, LOW);

    //Check to see if we need to water or not
    //if less than NEED_TO_WATER_LEVEL turn on blue light to indicate water is needed
    if ( output_value < NEED_TO_WATER_LEVEL )
    {
      Serial.println(F("Time to water"));
      digitalWrite(BLUE_PIN, HIGH);

      lcd.print("Time to water!!");
      delay(5000);

      lcd.clear();

      digitalWrite(BLUE_PIN, LOW);
    }
  }

  //Time to wait until next read of moisture sensor
  delay(5000);
}
