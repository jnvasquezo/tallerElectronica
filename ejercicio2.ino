int s1 = 30;  // Sensor 1
int s2 = 31;  // Sensor 2
int s3 = 32;  // Sensor 3
int s4 = 33;  // Sensor 4
int startPin = 34;  // Pin del boton de start
int stopPin = 35;  // Pin del boton de stop

int der = 22;  // Motor a la derecha
int izq = 23;  // Motor a la izquierda

bool start = false;  // Variable para controlar el inicio
bool stop = false;   // Variable para controlar el stop
// Contador de ciclos entre s4 y s2
int cycleCount = 0;
bool reachedS3 = false;  // Para saber si ya se llego a s3

void setup() {
  // Configuracion de los pines de los sensores y botones como entradas
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);

  // Configuracion de los pines del motor como salidas
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);

  // Iniciar comunicacion serial para monitorear el proceso
  Serial.begin(115200);
}

// Funcion para mover a la derecha
void moveRight() {
  digitalWrite(der, HIGH);
  digitalWrite(izq, LOW);
  Serial.println("Moviendo a la derecha...");
}

// Funcion para mover a la izquierda
void moveLeft() {
  digitalWrite(der, LOW);
  digitalWrite(izq, HIGH);
  Serial.println("Moviendo a la izquierda...");
}

// Funcion para detener la cinta
void stopBelt() {
  digitalWrite(der, LOW);
  digitalWrite(izq, LOW);
  Serial.println("Cinta detenida...");
}

void loop() {
  // Leer los botones de start y stop
  start = digitalRead(startPin);
  stop = digitalRead(stopPin);

  // Si se presiona stop, se detiene todo
  if (stop) {
    stopBelt();
    return;
  }

  // Si se presiona start, y aun no llegamos a s3
  if (start && !stop && !reachedS3) {
    // Si no hay nada en s1 ni s3, movemos a la derecha
    if (digitalRead(s1) == LOW && digitalRead(s3) == LOW) {
      moveRight();
    }

    // Si ya hay algo en s1, paramos y esperamos
    if (digitalRead(s1) == HIGH) {
      stopBelt();
      Serial.println("Esperando 3 segundos...");
      delay(3000);
      moveLeft();

      // Movemos hacia s4
      while (digitalRead(s4) == LOW && !stop) {
        if (digitalRead(stopPin)) {
          stopBelt();
          return;
        }
      }

      // Si llegamos a s4, movemos hacia s2
      if (digitalRead(s4) == HIGH) {
        stopBelt();
        Serial.println("Pieza en S4, moviendo a la derecha hacia S2...");
        moveRight();

        // Movemos hasta s2
        while (digitalRead(s2) == LOW && !stop) {
          if (digitalRead(stopPin)) {
            stopBelt();
            return;
          }
        }

        // Iniciamos el ciclo entre s4 y s2
        if (digitalRead(s2) == HIGH) {
          stopBelt();
          Serial.println("Pieza en S2, comenzando ciclos entre S4 y S2...");
          
          while (cycleCount < 3 && !stop) {
            moveLeft();
            while (digitalRead(s4) == LOW && !stop) {
              if (digitalRead(stopPin)) {
                stopBelt();
                return;
              }
            }
            stopBelt();
            Serial.println("Pieza en S4, ciclo completo.");
            
            moveRight();
            while (digitalRead(s2) == LOW && !stop) {
              if (digitalRead(stopPin)) {
                stopBelt();
                return;
              }
            }
            stopBelt();
            cycleCount++;
            Serial.println("Pieza en S2, ciclo completo.");
          }

          // Si los ciclos se completan, movemos a s3
          if (cycleCount == 3) {
            Serial.println("Ciclos completados, moviendo a S3...");
            moveLeft();
            while (digitalRead(s3) == LOW && !stop) {
              if (digitalRead(stopPin)) {
                stopBelt();
                return;
              }
            }

            // Si llegamos a s3, el proceso termina
            if (digitalRead(s3) == HIGH) {
              stopBelt();
              Serial.println("Pieza en S3, proceso completado.");
              reachedS3 = true;
            }
          }
        }
      }
    }
  }
}
