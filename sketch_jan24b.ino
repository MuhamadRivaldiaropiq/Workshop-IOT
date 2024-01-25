#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int moist,sensor _analog;
const int sensor_pin = 34;

const char* ssid ="vl";
const char* password = "Rivalsa 123965";
#define CHAT_ID "5942747578";
#define BOTtoken "6923688294:AAGkyEStp6s-6-lL6l3mTAASo-hg3cHqwxA";
WiFiClientSecure.Client;
UniversalTelegramBot.bot(BOTtoken, client);
int botrequestDelay = 1000;
unsigned long lastTimeBotRan;

int M,sensor_analog;
const int sensor_pin = 34;


void setup() {
 serial.begin (115200);
 serial.print("Connecting Wifi: ");
 serial.print(ssid);

 WiFi.mode(WiFi_STA);
 WiFi.begin(ssid, password);
 client.setCaCert(TELEGRAM_CERTIFICATE_ROOT);


 while (WiFi.status() != WL_CONNECTED) {
  serial.print(".");
  delay(500);
 }
serial.println("");
serial.println("WiFi connected");
serial.print("IP addres: ");
serial.println(WiFi.localIP());

bot.sendMessage(CHAT_ID, "Tunggu dulu.....monitoring akan segera dimulai", "");

 delay(2000);
 serial.print("Workshop monitoring tanaman SMKN 7 be");
 dht.begin();

}

void loop() {
  sensor_analog = analogRead(sensor_pin);
  M = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
 float t = dht.readTemperature();
 float h = dht.readHumidity();
  if (isnan(h) || isnan(t) || isnan(M)) {
    serial.println("sensor tidak terbaca!");
    return;
  }
  serial.print("===========monitoring tanaman\n");
  serial.print("Humiditas gas udara: ");
  serial.print(h); \*print humiditas gas *\
  serial.println(" %");
  serial.print("Temperatur lingkungan :");
  serial.print(t); /*print temperatur*/
  serial.println(" c");
  serial.print("kelembapan air tanah: ");
  serial.print(M); /*print kelembapan air*/
  serial.println(" %");
  delay(2000);

}
