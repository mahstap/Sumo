#include <Arduino.h>

// C++ code 

//pinos motor 1 definidos
#define IN1 10
#define IN2 9
#define EN1 8

//pinos motor 2 definidos
#define IN3 6
#define IN4 5
#define EN2 4

//pinos dos sensores definidos
#define S1 A1         // sensor esquerdo
#define S2 A2         // sensor frontal
#define S3 A3         // sensor direito

// pino do botao fail safe definido
#define FS 2

//variavel de distancia dos sensores
float dist1; 
float dist2; 
float dist3; 

//funçao de leitura dos sensores
void leitura1();
void leitura2();
void leitura3(); 

//funçao de reaçao dos motores
void loc(); 

void setup(){
  Serial.begin(9600); // Inicia a comunicação serial

  //declarando pinos de saida dos motores
  pinMode (IN1,OUTPUT); 
  pinMode (IN2,OUTPUT);
  pinMode (IN3,OUTPUT);
  pinMode (IN4,OUTPUT);

  //declarando pinos dos sensores 
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  pinMode (S3, OUTPUT);

  //pinos em nivel baixo
  digitalWrite (S1, LOW); 
  digitalWrite (S2, LOW); 
  digitalWrite (S3, LOW); 

  //enviando sinal logico
   digitalWrite (EN1,HIGH);
   digitalWrite (EN2,HIGH);
   digitalWrite (IN1,LOW);
   digitalWrite (IN2,LOW);
   digitalWrite (IN3,LOW);
   digitalWrite (IN4,LOW);
}

void loop(){
  
   //funçoes a serem executadas
  leitura1();
  leitura2();
  leitura3();

  dist1 = dist1/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist1 = dist1*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  
  dist2 = dist2/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist2 = dist2*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  
  dist3 = dist3/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist3 = dist3*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)

   Serial.print("Dist1 em cm: ");
  Serial.println(dist1);
  Serial.print("Dist2 em cm: ");
  Serial.println(dist2);
  Serial.print("Dist3 em cm: ");
  Serial.println(dist3);
  
  //funçoes a serem executadas
  loc();

  
}


void leitura1(){

//definir como pinos de saída
  pinMode(S1, OUTPUT); 
  
  pinMode(S3, OUTPUT); 

  //sinal de nivel alto por 5 microssegundos
  digitalWrite(S1, HIGH); 
  
  delayMicroseconds(5);

  //definir pinos como baixo
  digitalWrite(S1, LOW);

//definir pinos como entrada para fazer a leitura
  pinMode(S1, INPUT); 

  //le comprimento de onda em alta
  dist1 = pulseIn(S1, HIGH);
}

void leitura2(){
  pinMode(S2, OUTPUT); 

digitalWrite(S2, HIGH); 

 delayMicroseconds(5);

 digitalWrite(S2, LOW);

pinMode(S2, INPUT); 

 dist2 = pulseIn(S2, HIGH); 
}

void leitura3(){
  pinMode(S3, OUTPUT); 

digitalWrite(S3, HIGH); 

 delayMicroseconds(5);

 digitalWrite(S3, LOW);

pinMode(S3, INPUT); 

 dist3 = pulseIn(S3, HIGH); 
}


void loc(){
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, LOW);
  
  if(dist1 <= 100 && dist2 >= 100 && dist3 >= 100) //curva esq.
   { 
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN4,HIGH);
   }
  else if(dist1 <= 100 && dist2 <= 100 && dist3 >= 100) //curva suave esq.
 { 
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN4,HIGH);
 }
 else if(dist1 >= 100 && dist2 >= 100 && dist3 <= 100)   //curva dir.
 { 
   digitalWrite(IN1,HIGH);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,HIGH);
 }
 else if(dist1 >= 100 && dist2 <= 100 && dist3 <= 100)  //curva suave dir.
 {
   digitalWrite(IN1,HIGH);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,HIGH);
  }
 else if(dist1 >= 100 && dist2 <= 100 && dist3 >= 100)  //para frente
 {
   digitalWrite(IN1,HIGH);
   digitalWrite(IN4,HIGH);
  }
 else{
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,HIGH);
 }
}
