/*
==========CONEXIONES==========
C1 Encoder en Pin 2 (Cable verde)
C2 Encoder en Pin 3 (Cable amarillo) [Sin funcionalidad en este programa]
GND en GND común (Cable azul)
VCC en 5V (Cable negro)

No es necesario alimentar el driver a 6V (2 baterias de 3.7V en nuestro caso) puesto que no moveremos el MOTOR DC.
M1 en OUT1 del driver (Cable blanco)
M2 en OUT2 del driver (Cable rojo)
*/
const int ENCODER = 3; // Encoder en Pin 2
volatile long int contador = 0;

//========================RUTINA DE INTERRUPCION ENCODER ========================================
void LlegaPulso(){                    // Interrupción del encoder 
  contador++;
}

//=================================================================================================

void setup() {
  pinMode(ENCODER,INPUT_PULLUP);
   attachInterrupt( (digitalPinToInterrupt(ENCODER)),  LlegaPulso, CHANGE);
  Serial.begin(9600);

}


void loop() {
  Serial.println(contador);
  delay(100);
}
