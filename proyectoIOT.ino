//LIBRERÍAS
// SoftwareSerial: permite comunicación serial por pines digitales
#include <SoftwareSerial.h>
// Servo: controla servomotores
#include <Servo.h>

/*ESP8266*/
// Comunicación serial con el ESP8266 usando pines 11 (RX) y 12 (TX)
SoftwareSerial esp8266(11, 12);

// Credenciales WiFi
String ssid     = "CNT_QUEVEDO_2.4G";
String password = "QUEVEDO2473";

// API Key de ThingSpeak
String apiKey   = "OHTQG3HT6U946GX1";

// Host de ThingSpeak
String host     = "api.thingspeak.com";

/*PINES*/
// Sensor ultrasónico
#define TRIG_PIN 2
#define ECHO_PIN 3

// Servomotores
#define SERVO_PUERTA_PIN 8
#define SERVO_LLUVIA_PIN 10

// Sensor de lluvia (digital y analógico)
#define PIN_LLUVIA_DO 9
#define PIN_LLUVIA_AO A0

// LEDs y sensor de sonido
#define LED_PIN 7
#define SOUND_PIN 6
#define LED_PUERTA 13

/* OBJETOS */
// Objeto servo para la puerta
Servo servoPuerta;
// Objeto servo para el sensor de lluvia
Servo servoLluvia;

/* VARIABLES */
// Estado actual del LED controlado por aplausos
bool estadoLED = false;

// Estado anterior del sensor de sonido (para detectar flancos)
bool sonidoAnterior = LOW;

// Estado de lluvia detectada
bool estaLloviendo = false;

// Marca de tiempo de la última detección de lluvia
unsigned long ultimoDetectadoLluvia = 0;

// Marca de tiempo del último aplauso detectado
unsigned long ultimoAplauso = 0;

// Marca de tiempo de la última lectura de sensores
unsigned long ultimaLectura = 0;

/*  CONSTANTES  */
// Tiempo antirebote para aplausos
const unsigned long TIEMPO_REBOTE = 600;

// Intervalo entre lecturas de sensores
const unsigned long INTERVALO_SENSORES = 300;

// Tiempo considerado sin lluvia
const unsigned long TIEMPO_SIN_LLUVIA = 2000;

/*TIEMPO ENVÍO */
// Intervalo de envío de datos a ThingSpeak (5 minutos)
const unsigned long INTERVALO_ENVIO = 300000;
unsigned long ultimoEnvio = 0;

/* ACUMULADORES */
// Acumuladores para promedios
long sumaDistancia = 0;
long sumaLluvia = 0;
int conteoLecturas = 0;

// Contador de aplausos detectados
int contadorAplausos = 0;

/* ULTRASONICO*/
// Función para medir distancia usando el sensor HC-SR04
long medirDistancia() {
  // Pulso bajo inicial
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Pulso alto de 10 microsegundos
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Se mide la duración del eco
  long duracion = pulseIn(ECHO_PIN, HIGH, 30000);

  // Conversión de tiempo a distancia en cm
  return duracion * 0.034 / 2;
}

/* PUERTA*/
// Controla la apertura/cierre de la puerta según la distancia
void controlarPuerta(long distancia) {
  // Si el objeto está dentro del rango permitido
  if (distancia >= 10 && distancia <= 17) {
    servoPuerta.write(90);          // Abre la puerta
    delay(5000);                    // Mantiene abierta 5 segundos
    digitalWrite(LED_PUERTA, LOW);  // Apaga LED indicador
  } else {
    servoPuerta.write(0);           // Cierra la puerta
    digitalWrite(LED_PUERTA, HIGH); // Enciende LED indicador
  }
}
/*LLUVIA */
// Controla el servo según el nivel de humedad detectado
void controlarLluvia(int lluviaDigital, int lluviaAnalogica) {

  unsigned long ahora = millis();

  // Mostrar valores del sensor
  Serial.print("Lluvia DO: ");
  Serial.println(lluviaDigital);
  Serial.print(" | Lluvia AO: ");
  Serial.println(lluviaAnalogica);

  // Rango donde se considera lluvia
  if (lluviaAnalogica >= 0 && lluviaAnalogica <= 500) {
    estaLloviendo = true;
    ultimoDetectadoLluvia = ahora;
    servoLluvia.write(0);  // Cierra protección
    Serial.println(" --> Lluvia detectada, servo a 0°");
  } else {
    // Sensor completamente seco
    if (lluviaAnalogica > 600) {
      estaLloviendo = false;
      servoLluvia.write(90); // Abre protección
      Serial.println(" --> Sensor seco (AO > 600), servo a 90°");
    } else {
      // Zona intermedia (húmedo)
      Serial.println(" --> Aún húmedo, servo sin cambios");
    }
  }
}