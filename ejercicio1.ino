// Definicion de pines para los LEDs y el sensor de fuerza
const int ledRojo = 23;
const int ledAmarillo = 25;
const int ledAzul = 27;
const int ledVerde = 29;
const int sensorFuerza = A0;

void setup() {
  // Configuramos los pines de los LEDs como salida
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Arrancamos la comunicacion serial para ver datos en el monitor
  Serial.begin(115200);
}

void loop() {
  // Leemos el valor que viene del sensor de fuerza
  int lecturaSensor = analogRead(sensorFuerza);

  // Aqui convertimos la lectura a voltaje, ya que el sensor da valores entre 0 y 1023
  float voltaje = lecturaSensor * (5.0 / 1023.0);

  // Enviamos el voltaje al monitor serial para ver que estamos leyendo
  Serial.print("Voltaje del sensor: ");
  Serial.println(voltaje);

  // Apagamos todos los LEDs para empezar limpio en cada loop
  apagarTodosLosLeds();

  // Dependiendo de la fuerza leida, encendemos los LEDs
  if (lecturaSensor >= 0 && lecturaSensor <= 255) {
    digitalWrite(ledRojo, HIGH);  // Si es bajo, solo el rojo
  }
  else if (lecturaSensor > 255 && lecturaSensor <= 511) {
    digitalWrite(ledRojo, HIGH);  // Rojo
    digitalWrite(ledAmarillo, HIGH);  // y amarillo
  }
  else if (lecturaSensor > 511 && lecturaSensor <= 767) {
    digitalWrite(ledRojo, HIGH);  // Rojo
    digitalWrite(ledAmarillo, HIGH);  // Amarillo
    digitalWrite(ledAzul, HIGH);  // y azul tambien
  }
  else if (lecturaSensor > 767 && lecturaSensor <= 1023) {
    digitalWrite(ledRojo, HIGH);  // Rojo
    digitalWrite(ledAmarillo, HIGH);  // Amarillo
    digitalWrite(ledAzul, HIGH);  // Azul
    digitalWrite(ledVerde, HIGH);  // y verde al final
  }

  // Hacemos una pausa antes de leer de nuevo
  delay(100);
}

// Apagamos todos los LEDs para no dejar ninguno encendido por error
void apagarTodosLosLeds() {
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
}
