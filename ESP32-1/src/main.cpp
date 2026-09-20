/*
  ESP PERTAMA
*/
#include <Arduino.h>
#include "DHTesp.h"

// Pin DHT11
#define DHT_PIN 18

// Membuat objek DHT
DHTesp dht;

void setup() {

  // Serial Monitor
  Serial.begin(115200);

  // UART2
  // RX2 = GPIO16
  // TX2 = GPIO17
  Serial2.begin(115200);

  // Inisialisasi DHT11
  dht.setup(DHT_PIN, DHTesp::DHT11);

  Serial.println("ESP32-1 siap.");
  Serial.println("Membaca DHT11 setiap 5 detik...");
}

void loop() {

  // Membaca data dari DHT11
  TempAndHumidity data = dht.getTempAndHumidity();

  // Cek apakah pembacaan berhasil
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Gagal membaca DHT11!");
    delay(5000);
    return;
  }

  // Membuat data yang akan dikirim
  String pesan = "T:" + String(data.temperature, 1) +
                 "C H:" + String(data.humidity, 1) + "%";

  // Tampilkan hasil pembacaan di Serial Monitor
  Serial.println("Data DHT11:");
  Serial.print("Temperature: ");
  Serial.print(data.temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(data.humidity, 1);
  Serial.println(" %");

  // Kirim data ke ESP32-2 melalui UART2
  Serial2.println(pesan);

  Serial.println("Data dikirim ke ESP32-2:");
  Serial.println(pesan);

  Serial.println("--------------------");

  // Baca sensor setiap 5 detik
  delay(5000);
}