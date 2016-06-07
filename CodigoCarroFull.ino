#define TRIGGER_PIN  7//definiendo pin 7 para trigguer
#define ECHO_PIN     6//Definiendo pin 6 para el echo
#include <Ultrasonic.h>
#include <IRremote.h>

int led = 13;
float cmMsec,inMsec;
long microsec;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
long distancia;//variable que me almacenara la distancia calculada en base al tiempo
long tiempo;//Variable que me almacenara el tiempo retornado por el sensor de ultrasonido
int PINREC = 13; //define input pin on Arduino
int pin11M1 = 11;//pines definidos para el motor 1 que son 11 y 10
int pin10M1 = 10;
int pin9M2 = 9;//Definir pines del motor 2
int pin8M2 = 8;
int pin5 =5;//Para acelerar el primer motor
int pin4 = 4;//Para acelerar el segundo motor
int Acelerar=100;//Aumentara en 5 cuando se presiona el boton de subir
boolean cambio=true;
IRrecv irrecv(PINREC);
decode_results results;
int valorIR;
void setup()
{
  pinMode(pin11M1,OUTPUT);//Habilita el pin11 como salida del motor 1
  pinMode(pin10M1,OUTPUT);//Habilita el pin10 como salida del motor 1
  pinMode(pin5,OUTPUT);//Habilita el el pin 5 para acelerar el motor 1
  pinMode(pin9M2,OUTPUT);//Habilita el pin 9 como salida del motor 2
  pinMode(pin8M2,OUTPUT);//Habilita el pin 8 como salida del motor 2
  pinMode(pin4,OUTPUT);//Habilita el el pin 4 para acelerar el motor 2
  //Habilitando pines de Ultrasonido
  digitalWrite(pin5, HIGH);//Inicializando el pin5 de aceleracion con un valor alto
  digitalWrite(pin4, HIGH);//Inicializando el pin4 de bajar aceleracion con un valor alto
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value );
    irrecv.resume(); // Receive the next value
  }
  SenalUltraSonic();
  Serial.println("CM");
  Serial.println(cmMsec);
  if(cmMsec<=45){//si el carro esta a una distancia menor o igual que 45cm el carrito se detiene 
    detener();
  }else{
    MoverAcer(results.value);//Llama a la funcion de movimiento en caso de que la distancia sea mayor que 45 para poder moverse 
  }
}
void MoverAcer(int valor){
  switch(valor){
    
      case 22561://Boton Encender del control que hara que giren a velocidad normal los dos motores
          avanzar();
          break;
      case 26145://Boton PARA AVANZAR del control que hara que giren a velocidad normal los dos motores
          avanzar();
          break;
          
      case 9761://Retroceder en velocidad normal con el boton de retroceder
          retroceder();
          break;
      case 5665://Mover a la derecha 
          //digitalWrite(pin9M2,LOW);
          //digitalWrite(pin8M2,LOW);
          derecha();
          break;
       case 22049://Mover a la Izquierda
           izquierda();
          //digitalWrite(pin9M2,LOW);
         // digitalWrite(pin8M2,LOW);
          break;
       case 5153://Detener Motores
           detener();
          break;
          
      case 9249://Subir Volumen para acelerar los motores 
          Acelerar+=5;
          if(Acelerar>=0 && Acelerar<255){
            Serial.println("Aecelerar");
            Serial.println(Acelerar);
            acelerar();
          }else{
            Serial.println("No se puede acelerar mas");
          }
          break;
    
      case 25633://Bajar volumen y para acelerar los motores hacia atra
          Acelerar-=5;
          Serial.println(Acelerar);
          if(Acelerar>=0 && Acelerar <=255){
          acelerar();
          }else{
            Serial.println("No se puede bajar mas!!");
          }
          break;
  
  }
  
}
  void SenalUltraSonic(){
  
    microsec = ultrasonic.timing();
  
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
    inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

    
  }
void avanzar(){
  digitalWrite(pin9M2,HIGH);
  digitalWrite(pin8M2,LOW);
  //Velocidad inicial
  analogWrite(pin9M2,200);
}
void retroceder(){
  digitalWrite(pin9M2,LOW);
  digitalWrite(pin8M2,HIGH);
  analogWrite(pin8M2,200);  
}
void derecha(){
  digitalWrite(pin11M1,LOW);
  digitalWrite(pin10M1,HIGH);
  digitalWrite(pin9M2,HIGH);
  digitalWrite(pin8M2,LOW);
}
void izquierda(){
  digitalWrite(pin9M2,HIGH);
  digitalWrite(pin8M2,LOW);
  digitalWrite(pin11M1,HIGH);
  digitalWrite(pin10M1,LOW);
}
void detener(){
  digitalWrite(pin11M1,LOW);
  digitalWrite(pin10M1,LOW);
  digitalWrite(pin9M2,LOW);
}
void acelerar(){
  analogWrite(pin9M2,Acelerar);
}


