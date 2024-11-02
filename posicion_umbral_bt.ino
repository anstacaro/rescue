//umbral y rpomedio con blutu

#include "BluetoothSerial.h"
#include <QTRSensors.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial SerialBT;

#define SensorCount 8 
QTRSensors siguelineas;
uint16_t sensorValues[SensorCount]; 
uint16_t sensorThresholds[SensorCount];  // Arreglo para almacenar los umbrales

void setup() {

  Serial.begin(115200); 
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("blutut activado :)");



  // Configurar los pines de los sensores
  siguelineas.setTypeAnalog();
  siguelineas.setSensorPins((const uint8_t[]) {26, 25, 33, 32, 35, 34, 39, 36}, SensorCount);
  siguelineas.setEmitterPin(27);

  // Realizar la calibración de los sensores
  for (int i = 0; i < 400; i++) {
    siguelineas.calibrate();
  }

  // Calcular los umbrales como el promedio entre los valores máximos y mínimos de cada sensor
  for (int i = 0; i < SensorCount; i++) {
    sensorThresholds[i] = (siguelineas.calibrationOn.maximum[i] + siguelineas.calibrationOn.minimum[i]) / 2;
  }

  Serial.println("Calibración lista y umbrales calculados:");

  // Imprimir los umbrales de cada sensor
  for (int i = 0; i < SensorCount; i++) {
    SerialBT.print("Umbral del sensor ");
    SerialBT.print(i);
    SerialBT.print(": ");
    SerialBT.println(sensorThresholds[i]);
  }

  delay(1000);  // Pausa para permitir la lectura de los umbrales
}

void loop() {

  // Leer los valores calibrados de los sensores
  int posicion = siguelineas.readLineBlack(sensorValues);

  // Mapear la posición a un valor entre -255 y 255
  posicion = map(posicion, 0, 7000, -255, 255);

  // Imprimir los valores de los sensores y la posición estimada
  SerialBT.print("Sensores: ");
  for (int i = 0; i < SensorCount; i++) {
    SerialBT.print(sensorValues[i]);
    SerialBT.print(" (Umbral: ");
    SerialBT.print(sensorThresholds[i]);
    SerialBT.print(") | ");
  }

  // Imprimir la posición
  SerialBT.print("Posición: ");
  SerialBT.println(posicion); 

  delay(100); 
}