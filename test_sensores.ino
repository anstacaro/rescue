#include <QTRSensors.h>
#include "BluetoothSerial.h"
const uint8_t SensorCount = 8; 

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial SerialBT;
QTRSensors siguelineas;
uint16_t sensorValues[SensorCount]; 
uint16_t umbralValues[SensorCount];


void setup() { 
  Serial.begin(115200); 
  siguelineas.setTypeAnalog();
  siguelineas.setSensorPins((const uint8_t[]) {26, 25, 33, 32, 35, 34, 39, 36}, SensorCount);
  siguelineas.setEmitterPin(27);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("blutut activado :)");

  for (int i = 0; i < 400; i++) {
    siguelineas.calibrate();
  }
  for (int i=0;i<SensorCount;i++){
    umbralValues[i] = ((siguelineas.calibrationOn.minimum[i]+siguelineas.calibrationOn.maximum[i])/2);
  }

}
void loop() {
  int estado = casos(); 
  if(estado == 1){
    SerialBT.print("intersección");

  }else if(estado == 2){
    SerialBT.print("gap");

  }else if(estado == 3){
    SerialBT.print("girar izquierda");

  }else if(estado == 4){
    SerialBT.print("girar derecha");
  }else{
    SerialBT.print("linea recta --> avanzar");
  }
  delay(200); 
  // put your main code here, to run repeatedly:

}
