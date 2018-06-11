/*
 * Soil moisture sensor program
 * Kevin Orey
 */

#include <LiquidCrystal.h>

//Defines for lcd screen
#define db7 6
#define db6 7
#define db5 8
#define db4 9
#define rs 12
#define en 11
 
LiquidCrystal lcd(rs,en,db4,db5,db6,db7);

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

#define SLEEP_TIME 5000
#define LCD_SLEEP_TIME 1000

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

int startCounter = 0;

void loop() {
  // put your main code here, to run repeatedly:

  if ( startCounter == 0 )
  {
    lcd.print("Starting program");
    delay(LCD_SLEEP_TIME);
    lcd.clear();
  
    Serial.println(F("Starting of program"));
    startCounter++;
  }

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

  Serial.println(F("Setting digital pin 3 high"));

  //Turn of green led light to indicate a read is taking place
  digitalWrite(GREEN_PIN, HIGH);

  //Turning on moisture sensor power
  digitalWrite(MOISTURE_SENSOR_1, HIGH);
  delay(1000);

  lcd.print("Reading S1");
  delay(LCD_SLEEP_TIME);
  lcd.clear();
  
  //Read moisture sensor from analog pin
  output_value = analogRead(sensor_pin);
  Serial.print("Value read = ");
  Serial.println(output_value);

  lcd.print("Value read = ");
  lcd.print(output_value);
  delay(LCD_SLEEP_TIME);
  lcd.clear();

  //If we get an invalid signal need to turn on red light to indicate an error has occurred
  if ( output_value > NO_MOISTURE )
  {
    Serial.print("INVALID VALUE READ FROM SOIL MOISTURE SENSOR.  VALUE = ");
    Serial.print(output_value);
    digitalWrite(RED_PIN, HIGH);
    delay(SLEEP_TIME);

    digitalWrite(RED_PIN, LOW);
  }
  else
  {

    //Map read value to % of moisture
    output_value = map(output_value, NO_MOISTURE, SATURATED_SOIL, 0, 100);
    Serial.print("Moisture % = ");
    Serial.println(output_value);

    //display values on lcd
    lcd.print("Moisture % = ");
    lcd.print(output_value);
    delay(2000);
    lcd.clear();
  
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
      delay(SLEEP_TIME);

      lcd.clear();

      digitalWrite(BLUE_PIN, LOW);
    }
  }

  //Time to wait until next read of moisture sensor
  lcd.print("Sleeping...");
  delay(SLEEP_TIME);

  lcd.clear();
  lcd.print("Time to read sensors");

  delay(LCD_SLEEP_TIME);
  lcd.clear();
  
}
