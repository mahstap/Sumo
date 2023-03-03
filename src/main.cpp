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

float dist1; // Variavel de leitura da distancia
float dist2; // Variavel de leitura da distancia
float dist3; // Variavel de leitura da distancia

void leitura(); // Funçao de leitura da distancia
void loc(); // Funçao de reação dos motores

void setup(){
  Serial.begin(9600); // Inicia a comunicação serial

  pinMode(S1, OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  digitalWrite(S1, LOW); // Inicia com o pino em nível baixo
  digitalWrite(S2, LOW); // Inicia com o pino em nível baixo
  digitalWrite(S3, LOW); // Inicia com o pino em nível baixo
  
}

void loop(){
  leitura();
  loc();

  dist1 = dist1/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist2 = dist2/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist3 = dist3/2; // Divide por 2 pois esse e o tempo da onda ir e voltar
  dist1 = dist1*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  dist2 = dist2*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  dist3 = dist3*0.034029; // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)

  Serial.print("Dist1 em cm: ");
  Serial.print("Dist2 em cm: ");
  Serial.print("Dist3 em cm: ");
  Serial.println(dist1);
  Serial.println(dist2);
  Serial.println(dist3);
}



}

void leitura(){
  pinMode(S1, OUTPUT); // Define o pino como saida
  pinMode(S2, OUTPUT); // Define o pino como saida
  pinMode(S3, OUTPUT); // Define o pino como saida
  digitalWrite(S1, HIGH); // Manda um sinal de nível alto por 5 microssegundos
  digitalWrite(S2, HIGH); // Manda um sinal de nível alto por 5 microssegundos
  digitalWrite(S3, HIGH); // Manda um sinal de nível alto por 5 microssegundos
  delayMicroseconds(5);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  pinMode(S1, INPUT); // Define o pino como entrada para fazer a leitura
  pinMode(S2, INPUT); // Define o pino como entrada para fazer a leitura
  pinMode(S3, INPUT); // Define o pino como entrada para fazer a leitura
  dist1 = pulseIn(S1, HIGH); // Le o comprimento de onda em alta
  dist2 = pulseIn(S2, HIGH); // Le o comprimento de onda em alta
  dist3 = pulseIn(S3, HIGH); // Le o comprimento de onda em alta
}
void loc(){
  if(dist1 <= 100 && dist2 >= 100 && dist3 >= 100) //curva esq.
 { }
  else if(dist1 <= 100 && dist2 <= 100 && dist3 >= 100) //curva suave esq.
 { }
 else if(dist1 >= 100 && dist2 >= 100 && dist3 <= 100)   //curva dir.
 { }
 else if(dist1 >= 100 && dist2 <= 100 && dist3 <= 100)  //curva suave dir.
 { }
 else if(dist1 >= 100 && dist2 <= 100 && dist3 >= 100)  //para frente
 { }
}