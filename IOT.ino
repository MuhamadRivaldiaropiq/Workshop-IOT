#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

const char* ssid ="V2026";
const char* password = "ahmad2007";
#define CHAT_ID "5942747578"
#define BOTtoken "6923688294:AAGkyEStp6s-6-lL6l3mTAASo-hg3cHqwxA"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
 Serial.begin(115200);
 Serial.print("Connecting Wifi: ");
 Serial.println(ssid);

 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 client.setCACert(TELEGRAM_CERTIFICATE_ROOT);


 while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
 }
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP addres: ");
Serial.println(WiFi.localIP());

bot.sendMessage(CHAT_ID, "Tunggu dulu.....monitoring akan segera dimulai", "");

 delay(2000);
 Serial.print("Workshop monitoring tanaman SMKN 7 be");
 dht.begin();

}

void loop() {
  sensor_analog = analogRead(sensor_pin);
  M = (100-((sensor_analog/4095.00)*100));
 float t = dht.readTemperature();
 float h = dht.readHumidity();
  if (isnan(h) || isnan(t) || isnan(M)) {
    Serial.println("sensor tidak terbaca!");
    return;
    bot.sendMessage(CHAT_ID,"Sensortidakterbaca!","");
  }
  Serial.print("===========monitoring tanaman\n");
  Serial.print("Humiditas gas udara: ");
  Serial.print(h); /*print humiditas gas */
  Serial.println(" %");
  Serial.print("Temperatur lingkungan :");
  Serial.print(t); /*print temperatur*/
  Serial.println(" c");
  Serial.print("kelembapan air tanah: ");
  Serial.print(M); /*print kelembapan air*/
  Serial.println(" %");
  delay(2000);
  kirimPesanTelegram(h,t,M);

}

void kirimPesanTelegram(float h, float t, int M) {
  String pesan = "Suhu saat ini: "+ String (t, 2) + "%\n" +
                  "Humaditas saat ini: " + String(h, 2) + "%\n" +
                  "Tingkat kelembapan tanah saat ini: " + String(M) + "%\n";
    if (bot.sendMessage(CHAT_ID, pesan, "Markdown")) {
      Serial.println("Pesan berhasil dikirim");
    } else {
      Serial.println("Gagal mengirimkan pesan");
    }
    delay(1000); //Menunggu sejenak sebelum mengirim pesan lagi
}