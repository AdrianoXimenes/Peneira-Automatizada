/*   Peneira Automatizada
    Autor:: Adriano Ximenes
      Data:08/10/2020   */
//Leitura de distância com o sensor HC-SR04
#include <Ultrasonic.h>
Ultrasonic ultrassom1(8, 7); // define o nome do sensor(ultrassom) e onde esta ligado o trig(8) e o echo(7) respectivamente
float distancia;
float altura;
float volume;
int qtd;
int motor = 6;

void setup() {
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
  Serial.println("Digite qual a quantidade deseja peneirar:");
}

// Função que se repete infinitamente quando a placa é ligada
void loop() {
  if (Serial.available() > 0) {    // vai ler e armazenar é digitado no serial
    qtd = Serial.read();
  }
  distancia = ultrassom1.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
  altura = 74 - distancia; //74 é altura do sensor até o fundo da peneira
  volume = 2 * 4 * (altura / 100);

  if (Serial.available() > 0) {    // vai ler e armazenar o estado do bluetooth
    qtd = Serial.read();
  }

  if ( qtd >= '3') {
    digitalWrite(motor, HIGH);
    Serial.println("Peneiramento Iniciado");
    Serial.print("volume:");
    Serial.print(volume);
    Serial.println("M³");
    delay(1000);
    if ( volume >= 3.00) {
      digitalWrite(motor, LOW);
      Serial.println("Peneiramento Terminado");
      delay(1000);
    }
  }
    if ( qtd >= 'D') {
    digitalWrite(motor, LOW);
    Serial.println("Desligando...");
    delay(100);
    Serial.println("Desligado");
    delay(1000);
    }
  
}
