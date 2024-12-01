#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ArduinoJson.h>

// Definiciones de pines
#define SOIL_MOISTURE_PIN A0 // Pin analógico para el sensor de humedad del suelo
#define SEALEVELPRESSURE_HPA (1013.25) // Ajusta según la presión atmosférica local
// Inicialización de objetos
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Inicializando...");

  // Inicializar LoRa
  LoRa.setPins(10, 9, 2); // NSS = 10, RESET = 9, DIO0 = 2

  if (!LoRa.begin(915E6)) {
    Serial.println("Error inicializando LoRa");
    lcd.clear();
    lcd.print("Error en LoRa");
    while (1);
  }
  Serial.println("LoRa inicializado con éxito");
  lcd.clear();
  lcd.print("LoRa listo");
  

  // Inicializar BMP280
  if (!bmp.begin(0x76)) { // Intenta iniciar con la dirección I2C del sensor
    Serial.println("No se encontró el sensor BMP280.");
    while (1);
  }
}

void loop() {
  // Leer humedad del suelo
  int medicionHumedad = analogRead(SOIL_MOISTURE_PIN);
  int seco = 1023;    // Valor de referencia en seco
  int mojado = 160;   // Valor de referencia en agua

  // Mapea el valor a un porcentaje de humedad
  int porcentajeHumedad = map(medicionHumedad, seco, mojado, 0, 100);

  // Limita los valores de salida para que se mantengan entre 0 y 100%
  porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);

  // Leer temperatura
  float temperatura = bmp.readTemperature();

  // Leer presión
  float presion = bmp.readPressure() / 100.0F; // Convertir a hPa

  // Mostrar datos en el LCD
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.print("C   "); // Espacios en blanco para eliminar caracteres sobrantes

  lcd.setCursor(9, 0);
  lcd.print("H:");
  lcd.print(porcentajeHumedad);
  lcd.print("%     ");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(presion, 1);
  lcd.print("hPa "); // Espacios en blanco para eliminar caracteres sobrantes

  // Enviar datos por LoRa
  StaticJsonDocument<200> doc;
  doc["Id_Modulo"] = 14;
  doc["Temperatura"] = temperatura;
  doc["Presion"] = presion;
  doc["Humedad"] = porcentajeHumedad;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  
  // Imprimir datos en el monitor serial
  Serial.print("Presion: ");
  Serial.print(presion);
  Serial.print(", Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" *C, Humedad: ");
  Serial.print(porcentajeHumedad);
  Serial.println(" %");

   //Enviar paquete
  LoRa.beginPacket();
  LoRa.print(jsonBuffer);
  LoRa.endPacket(); 
  
  
  // Esperar 15 segundos antes de la siguiente lectura
  delay(15000);

  Serial.println("Datos enviados");
}
