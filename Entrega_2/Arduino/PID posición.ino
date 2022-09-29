//Declaramos librerias

//-----------------------//

//Definir Pines Respuesta

#define PIN_LED 13

//Definir Pines Motor
#define MOTOR_PWM 6
#define INA1 7
#define INA2 8


//Definir Pines Encoder
#define ENC_A 2
#define ENC_B 3

//Definir Pines Sensores
#define PIN_FIN_DE_CARRERA 5

//VARIABLE PARA EL ENVÍO
long int LastEnviado = millis();

//SALIDA Y MEDIDAS DE POSICIÓN
int Salida = 0;
long int Pulsos = 0;
float Pos_Vu = 0;

//Variables utilizadas en el controlador PID.
unsigned long lastTime = 0;
double Input = 0, Output = 0, Setpoint = 0;
double errSum = 0, lastErr = 0;
double kp = 0, ki = 0, kd = 0;
int SampleTime = 1000; // Seteamos el tiempo de muestreo en 1 segundo.
int OutputDef = 0;
//----------------------//
//Declaramos funciones de trabajo
void Sensor1()
{
  if (digitalRead(ENC_A) == digitalRead(ENC_B)) Pulsos++;
  else Pulsos--;
}
void Sensor2()
{
  if (digitalRead(ENC_A) == digitalRead(ENC_B)) Pulsos--;
  else Pulsos++;
}

void Compute()
{
    unsigned long now = millis();
    int timeChange = (now - lastTime);
    // Determina si hay que ejecutar el PID o retornar de la función.
    if(timeChange>=SampleTime)
    {
      // Calcula todas las variables de error.
      double error = Setpoint - Input;
      errSum += error;
      double dErr = (error - lastErr);
      // Calculamos la función de salida del PID.
      Output = kp * error + ki * errSum + kd * dErr;
      // Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
      lastErr = error;
      lastTime = now;
    }
    //Establecemos límites
  if (Output >= 255) Output = 255;
  if (Output < -255) Output = -255;

  //AJUSTAMOS LA POLARIDAD DEL MOTOR
  if (Output > 0)
  {
    OutputDef = round(Output);
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, HIGH);
  }
  else
  {
    OutputDef = (-1) * round(Output);
    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, LOW);
  }

}

void SetTunings(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp = Kp;
  ki = Ki * SampleTimeInSec;
  kd = Kd / SampleTimeInSec;
}

void enviarPos()
{
  //ENVIAMOS POSICIÓN REAL CADA X ms
  if (millis() - LastEnviado > 200)
  {
    Serial.print("Real: ");
    Serial.print(Pos_Vu);
    Serial.print("  Deseada: ");
    Serial.print(Setpoint);
    Serial.print("    ");

    LastEnviado = millis();
  }
}

void flash()
{
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(PIN_LED,HIGH);
    delay(500);
    digitalWrite(PIN_LED,LOW);
    delay(500);
  }
}

void enviarPosicion(int pos){
  Serial.println(String(pos));
}

int recibirParametro(){
  while(Serial.available() == 0){}; //Esperamos a recibir parametro
  return Serial.readString().toInt(); //Leemos y adaptamos el valor a int
}

void ControlVelocidad(){
  int rpm = recibirParametro();

  //Codigo PID CARLOS
 
    //CODIGO CONTROL MOTOR
  
}

void ControlPosicion(){
  int Setpoint = recibirParametro();

  //Codigo PID CARLOS
  Compute();
  
    //CODIGO CONTROL POSICION
        //CODIGO MANDAR POSICION
        enviarPos();
  
}

void Saludo(){
  Serial.println("S");
  flash();
}

//---------------------//
void setup() {
  //Establecemos modo de los pines
    //Pines Motor
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(INA1, OUTPUT);  
    pinMode(INA2, OUTPUT);  
    //Pines Sensores
    pinMode(PIN_FIN_DE_CARRERA,INPUT_PULLUP);
    //Pines Encoder
    pinMode(ENC_A,INPUT_PULLUP);
    pinMode(ENC_B,INPUT_PULLUP);
    //Pines Respuesta
    pinMode(PIN_LED,OUTPUT);
    attachInterrupt( (digitalPinToInterrupt(ENC_A)),  Sensor1, CHANGE);
    attachInterrupt( (digitalPinToInterrupt(ENC_B)),  Sensor2, CHANGE);
    digitalWrite(INA1,LOW);  
    digitalWrite(INA2,LOW);
  //Establecemos comunicación serie
    Serial.begin(9600); //9600 baudios es una frecuencia adecuada para los interlocutores planteados.
}

void loop() {
  if(Serial.available() > 0){
    String codigo = Serial.readString();
    switch(codigo[0]){
      case 'S':
        digitalWrite(PIN_LED,HIGH);//Modo activo visual
        Saludo();
        flash(); //Usamos el flash para visualizar si hemos entrado en un modo especifico
        break;
      case 'P':
        digitalWrite(PIN_LED,HIGH);//Modo activo visual
        ControlPosicion();
        break;
      case 'V':
        digitalWrite(PIN_LED,HIGH);//Modo activo visual
        ControlVelocidad();
        break;
      default:
        digitalWrite(PIN_LED,LOW);//Modo inactivo visual
    }
  }

}
