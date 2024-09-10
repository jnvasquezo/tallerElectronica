const int pinRojo = 27;  // LED Rojo
const int pinVerde = 26;  // LED Verde
const int pinAzul = 25;  // LED Azul

const int sensorPin = 34;  // Pin para el sensor de temperatura

float temperatura = 0.0;  // Variable para almacenar la temperatura medida

void setup() {
  // Configuracion de los pines de los LEDs como salidas
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  
  // Iniciar la comunicacion serial para monitorear la temperatura
  Serial.begin(115200);
}

void loop() {
  // Leer el valor del sensor de temperatura (LM35)
  int valorLM35 = analogRead(sensorPin);

  // Convertir el valor leido a voltaje (para un ESP32 alimentado a 3.3V)
  float voltaje = valorLM35 * (3.3 / 4095.0);
  
  // Convertir el voltaje en grados Celsius
  temperatura = voltaje * 100.0;

  // Mostrar la temperatura en el monitor serial
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // Cambiar el color del LED segun la temperatura
  if (temperatura >= 15 && temperatura <= 17) {
    // Azul si la temperatura esta entre 15 y 17 grados
    setColor(0, 0, 255);
  } else if (temperatura > 18 && temperatura <= 20) {
    // Naranja si esta entre 18 y 20 grados
    setColor(255, 165, 0);
  } else if (temperatura > 20) {
    // Rojo si es mayor a 20 grados
    setColor(255, 0, 0);
  }

  // Esperar un segundo antes de la siguiente lectura
  delay(1000);
}

// Funcion para controlar los colores de los LEDs
void setColor(int rojo, int verde, int azul) {
  // Ajustar el brillo de cada LED con PWM
  analogWrite(pinRojo, rojo);
  analogWrite(pinVerde, verde);
  analogWrite(pinAzul, azul);
}
