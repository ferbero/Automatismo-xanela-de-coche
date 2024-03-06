/* Programa para controlar a ventá dun coche.
 * Disponse dun pulsador que activa un de dous motores.
 * Outros dous pulsadores simularán dous finais de carreira da ventá.
 * O primeiro motor fai subir a ventá.
 * O sengundo motor fai baixar a venta.
 * Os motores son activados a través de cadanseu relé.
 * Arduino manda os sinais correspondentes ós relés dependendo do
 * comportamento desexado.
 *
 * Comportamento ao premer pulsador
 * 	- se a ventá está subindo, detense
 *	- se a ventá está parada, actívase a acción contraria á acción previa.
 *
 * Comportamento ao premer o pulsador que simula o Fin de Carreira Superior:
 *  - se a ventá está subindo, páraa.
 * Comportamento ao premer o pulsador que simula o Fin de Carreira Inferior:
 *  - se a ventá está baixando, páraa.
 *
 * Se non se preme ningún pulsador, a ventá sigue en movemento durante 7 segundos.
 *
 * Úsase o pin 6 para simular o fin de carreira inferior
 * Úsase o pin 7 para simular o fin de carreira superior
 * Úsase o pin 8 para conectar o pulsador
 * Úsase o pin 9 para conectar o relé que activa a subida da ventá
 * Úsase o pin 10 para conectar o relé que activa a baixada da ventá
 * Autor: Fer
 * Data: 07-03-2024
 *
 */

// Definición de entradas e saídas
#define PULSADOR 8
#define FC_ARRIBA 7
#define FC_ABAIXO 6
#define RELE_SUBIDA 10
#define RELE_BAIXADA 9
// Definición do tempo que desexamos que transcurra entre una lectura do pulsador e a seguinte
#define TEMPO_LECTURA 10

// Declaración de variables globais
int tempoEncendido = 7000; // Tempo total que debe estar a ventá en movemento
int tempoRestante = 0; // Tempo restante durante o cal a ventá seguirá en movemento
byte motorActivo = RELE_BAIXADA; // Pin do último motor activado

void setup()
{
  // Establécese o modo de funcionamento dos pins usados
  pinMode(FC_ARRIBA, INPUT);
  pinMode(FC_ABAIXO, INPUT);
  pinMode(PULSADOR, INPUT);
  pinMode(RELE_SUBIDA, OUTPUT);
  pinMode(RELE_BAIXADA, OUTPUT);
}


/* Loop
   En cada ciclo de execución:
   - Lectura dos pulsadores.
   - Activación ou desactivación do motor.
   - Pequena espera antes de seguinte ciclo.
*/
void loop()
{
  // Xestión das entradas:
  if (digitalRead(PULSADOR)) xestionarPulsador();
  if (digitalRead(FC_ARRIBA)) xestionarFinCarrera(RELE_SUBIDA); // Se se detecta o FC superior, compróbase o motor de subida
  if (digitalRead(FC_ABAIXO)) xestionarFinCarrera(RELE_BAIXADA); // Se se detecta o FC iferior, compróbase o motor de baixada
  // Xestión da saída:
  moverXanela();
  // Xestión do tempo de execución
  esperarFinPulsacion();
  delay(TEMPO_LECTURA);
}

// Función que xestiona o pulsador principal:
void xestionarPulsador()
{
  if (tempoRestante > 0) { // Cúmprese cando algún  motor está activo
    tempoRestante = 0; // Establece o tempo a 0 para que o motor pare
  } else {
    motorActivo = motorActivo == RELE_BAIXADA? RELE_SUBIDA: RELE_BAIXADA; // Cambia o motor activo
    tempoRestante = tempoEncendido; // Pon o tempo ó máximo para que o motor se mova
  }
}


// Función que xestiona a detección dun Fin de Carreira
// releAComporobar: pin do relé que queremos comprobar se está activando o seu motor
void xestionarFinCarrera(int releAComprobar)
{
  if (tempoRestante > 0 && (motorActivo == releAComprobar)) {
    tempoRestante = 0; // Parada do motor
  }
}

// Función que xestiona o movemento da ventá
void moverXanela()
{
  if (tempoRestante > 0) { // Se queda tempo, a ventá móvese
    tempoRestante -= TEMPO_LECTURA; // Réstase tempo de activación.
    digitalWrite(motorActivo, HIGH); // Asegúrase que o motor correspondente esté activo
  }
  else digitalWrite(motorActivo, LOW); // Asegúrase que o motor está desactivado
}

// Fución que espera a que o Pulsador deixe de estar premido
void esperarFinPulsacion()
{
  while(digitalRead(PULSADOR)) delay(TEMPO_LECTURA);
}
