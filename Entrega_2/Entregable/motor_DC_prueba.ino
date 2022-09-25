/*

Movimiento oscilatorio: completa una vuelta de giro y cambia su sentido. 
Abrir Herramientas>>SerialPlotter para visualizar movimiento

===========CONEXIONES===========
Motor: 
Mismas conexiones en motor encoder_prueba.ino alimentando M1 y M2.
Driver: 
VCC en positivo pila (Cable verde)
GND en negativo pila( (Cable azul)
GND driver en protoboard GNDs arduino (Cable carne)
ENA MOTOR_pwm en Pin6 (Cable azul)
IN1 en Pin7 (Cable lila)
IN2 en Pin8 (Cable gris)

*/

#define MOTOR_PWM 6
#define INA1 7
#define INA2 8
#define ENC_A 2
#define ENC_B 3

volatile long int contador = 0;
int Max_contador =298; //Pasos 1 vuelta
int VEL=70; //VEL Mínima vencer inercias: 64

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
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(INA1, OUTPUT);  
  pinMode(INA2, OUTPUT);  
  pinMode(ENC_A,INPUT_PULLUP);
  pinMode(ENC_B,INPUT_PULLUP);
  attachInterrupt( (digitalPinToInterrupt(ENC_A)),  Sensor1, CHANGE);
  attachInterrupt( (digitalPinToInterrupt(ENC_B)),  Sensor2, CHANGE);
  
  Serial.begin(9600);

      digitalWrite(INA1,LOW);  
      digitalWrite(INA2,HIGH);
}


void loop() {
  
  if (contador>Max_contador){
      digitalWrite(INA1,HIGH);  
      digitalWrite(INA2,LOW);

  }   
  if (contador<-Max_contador){
      digitalWrite(INA1,LOW);  
      digitalWrite(INA2,HIGH);
