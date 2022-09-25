#define ENC_A 2 // canal A del encoder
#define ENC_B 3 // canal B del encoder  

volatile long int contador = 0;

//========================RUTINAS DE INTERRUPCION ENCODER ========================================
void Sensor1(){                    // Interrupción del encoder 1
  if(digitalRead(ENC_A) == digitalRead(ENC_B))  contador++;
  else contador--;
}

void Sensor2(){                    // Interrupción del encoder 2
   if(digitalRead(ENC_A) == digitalRead(ENC_B))  contador--;
  else contador++;
}

//=================================================================================================

void setup() {
  pinMode(ENC_A,INPUT_PULLUP);
  pinMode(ENC_B,INPUT_PULLUP);
  attachInterrupt( (digitalPinToInterrupt(ENC_A)),  Sensor1, CHANGE);
  attachInterrupt( (digitalPinToInterrupt(ENC_B)),  Sensor2, CHANGE);
  
  Serial.begin(9600);

}


void loop() {
  Serial.println(contador);
  delay(100);
}
