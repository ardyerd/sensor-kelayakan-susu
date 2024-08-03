#include <Arduino.h>

// TCS3200
#define S0 26
#define S1 25
#define S2 33
#define S3 32
#define OUT 27

// LM35DZ
#define TEMP_PIN 34

// Sensor Konduktivitas
#define EC_PIN 35

// pH Sensor
#define PH_PIN 36

// Variabel untuk menyimpan nilai sensor
float temperature = 0.0;
float conductivity = 0.0;
float pHValue = 0.0;
int red = 0, green = 0, blue = 0;

void setup() {
  Serial.begin(115200);
  
  // Set pin mode untuk TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  // Set frekuensi skala TCS3200
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  // Baca data dari sensor warna TCS3200
  colorSensorRead();
  
  // Baca data dari sensor suhu LM35DZ
  temperature = readTemperature();

  // Baca data dari sensor konduktivitas
  conductivity = readConductivity();

  // Baca data dari sensor pH
  pHValue = readPH();
  
  // Print nilai sensor ke Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Conductivity: ");
  Serial.print(conductivity);
  Serial.print(" mS/cm, pH: ");
  Serial.print(pHValue);
  Serial.print(", Red: ");
  Serial.print(red);
  Serial.print(", Green: ");
  Serial.print(green);
  Serial.print(", Blue: ");
  Serial.println(blue);

  delay(1000); // Jeda 1 detik
}

// Fungsi untuk membaca data dari sensor warna TCS3200
void colorSensorRead() {
  // Baca merah
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(OUT, LOW);
  
  // Baca hijau
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(OUT, LOW);
  
  // Baca biru
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(OUT, LOW);
}

// Fungsi untuk membaca data dari sensor suhu LM35DZ
float readTemperature() {
  int analogValue = analogRead(TEMP_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float temperatureC = voltage * 100.0;
  return temperatureC;
}

// Fungsi untuk membaca data dari sensor konduktivitas
float readConductivity() {
  int analogValue = analogRead(EC_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float conductivity = voltage * 1000; // Konversi sesuai dengan kalibrasi sensor
  return conductivity;
}

// Fungsi untuk membaca data dari sensor pH
float readPH() {
  int analogValue = analogRead(PH_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float pHValue = 3.5 * voltage + 0.0; // Kalibrasi sesuai dengan datasheet sensor
  return pHValue;
}
