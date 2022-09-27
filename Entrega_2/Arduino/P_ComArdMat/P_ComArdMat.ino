#define PIN_LED 13
#define DELAYCONST 1000

char read()
{
   return Serial.read();
}

void flash()
{
  for(int i = 0; i < 5; i++)
  {
  digitalWrite(PIN_LED,HIGH);
  delay(DELAYCONST);
  digitalWrite(PIN_LED,LOW);
  delay(DELAYCONST);
  }
}


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_LED,OUTPUT);
}

void loop()
{
  char car;
  if( Serial.available() > 0 ){
    flash();
    car = read();
    Serial.write(car);
  }
}
