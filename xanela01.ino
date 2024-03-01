/* Programa para controlar a ventá dun coche.
 * Disponse dun pulsador que activa un de dous motores.
 * O primeiro motor fai subir a ventá.
 * O sengundo motor fai baixar a venta.
 * Os motores son activados a través de cadanseu relé.
 * Arduino manda os sinais correspondentes ós relés dependendo do
 * comportamento desexado.
 * Comportamento ao premer pulsador
 * 	- se a ventá está subindo, actívase o descenso da ventá.
 *	- se a ventá está baixando, actívase a elevación da ventá.
 *	- se a ventá está parada, actívase a acción contraria á acción previa.
 * Se non se preme o pulsador, a ventá sigue en movemento durante 7 segundos
 *
 * Úsase o pin 8 para conectar o pulsador
 * Úsase o pin 9 para conectar o relé que activa a subida da ventá
 * Úsase o pin 10 para conectar o relé que activa a baixada da ventá
 * Autor: Eu
 * Data: 26-02-2024
 *
 */

// Definición de entradas e saídas
#define PULSADOR 8
#define RELE_SUBIDA 9
#define RELE_BAIXADA 10
// Definición do tempo que desexamos que transcurra entre una lectura do pulsador e a seguinte
#define TEMPO_LECTURA 10

// Declaración de variables globais
int tempoEncendido = 7000; // Tempo total que debe estar a ventá en movemento
int tempoRestante = 0; // Tempo restante durante o cal a ventá seguirá en movemento
byte motorActivo = RELE_BAIXADA; // Pin do último motor activado

void setup()
{
  // Establécese o modo de funcionamento dos pins usados
  pinMode(PULSADOR, INPUT);
  pinMode(RELE_SUBIDA, OUTPUT);
  pinMode(RELE_BAIXADA, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Comprobar se o pulsador está activado:
  if (digitalRead(PULSADOR))
  { // Asegura que o último motor activado estea parado:
    digitalWrite(motorActivo, LOW);
    // Cambia de motor activo:
    motorActivo = motorActivo == RELE_BAIXADA? RELE_SUBIDA: RELE_BAIXADA;
    // Resetea o tempo que debe estar encendido o motor:
    tempoRestante = tempoEncendido;
  }

  // Se índa queda tempo en tempoRestante...
  if (tempoRestante > 0)
  {
    // Restamoslle a ese tempo a pequena cantidade de tempo que dura o loop:
    tempoRestante -= TEMPO_LECTURA;
    // Asegurámonos de que o pin do motor activo teña un valor alto:
    digitalWrite(motorActivo, HIGH);
  }
  // Se xa non queda tempo en tempoRestante, asegurámonos de que o motor pare:
  else digitalWrite(motorActivo, LOW);
  
  // Ignoramos o tempo durante o cal o pulsador segue en valor alto
  // para non volver a cambiar de motor durante a mesma pulsación:
  while (digitalRead(PULSADOR)) delay(TEMPO_LECTURA);
  // Dámoslle un pequeno descanso ó Arduino antes da seguinte execución do loop:
  delay(TEMPO_LECTURA);
}
