int leerLaser() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);  // Realiza la medición
  if (measure.RangeStatus != 4) {    // Verifica que no haya errores
    return measure.RangeMilliMeter;  // Retorna la distancia en milímetros
  } else {
    return -1; // Retorna -1 en caso de error en la lectura
  }
}

// Función para iniciar el sensor láser
void iniciarLaser() {
  if (!lox.begin()) {
    Serial.println(F("Error al inicializar el VL53L0X"));
    while (1); // Detener si hay un error al inicializar el sensor
  }
}