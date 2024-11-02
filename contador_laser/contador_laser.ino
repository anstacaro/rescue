
//contador laser 

#include <Wire.h>
#include <Adafruit_VL53L0X.h>


Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void setup() {
  Serial.begin(115200);
  iniciarLaser();
}

void loop() {
  int distancia = leerLaser();  // Lee la distancia

  if (distancia != -1) {  // Si la lectura es válida
    Serial.print("Distancia medida: ");
    Serial.print(distancia);
    Serial.println(" mm");

    // Si hay un obstáculo a menos de 100 mm
    if (distancia < 100) {
      Serial.println("¡Obstáculo detectado!");
    }
  } else {
    Serial.println("Error en la lectura del sensor.");
  }

  delay(500);  
}