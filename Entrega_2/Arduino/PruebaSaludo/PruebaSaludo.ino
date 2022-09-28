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

int saludo()
  {
    if(Serial.available() > 0);
      String data = Serial.readString();
      if( data == "S0" ){
        Serial.println("S1");
        flash();
        return 1;
      }
      else return 0;
  }
void setup()
{
  Serial.begin(9600);
  pinMode(PIN_LED,OUTPUT);
}

void loop()
{
  if( saludo() == 1) 
    digitalWrite(PIN_LED,HIGH); 
}
