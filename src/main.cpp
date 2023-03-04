#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <PubSubClient.h>

#include "index.h"
#include "submit.h"

#define BUTTON 5
#define ANALOG_POWER 4
#define ANALOG_SELECT 12
#define SENSOR_POWER 13
#define BATTERY_POWER 14

bool setup_mode = false;
bool blink_state = false;
long last_blink = 0;

String ap_name = "SoilMoisture";
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

String readEEPROM(uint8_t offset = 0, uint8_t max_length = 32) {
  String in_str;
  for(int i = 0; i < max_length; i++) {
    char in_ch = char(EEPROM.read(offset + i));
    if(in_ch == 0x00) break;
    in_str += in_ch;
  }
  return in_str;
}

void writeEEPROM(String data, uint8_t offset = 0) {
  for(uint8_t i = 0; i < data.length(); i++) EEPROM.write(offset + i, data[i]);
  EEPROM.write(offset + data.length(), 0x00);
}

ESP8266WebServer server(80);

void handleConnection() {
  server.send(200, "text/html", INDEX_HTML);
}

void handleSubmit() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

  writeEEPROM(ssid);
  writeEEPROM(password, 32);
  EEPROM.commit();

  server.send(200, "text/html", SUBMIT_HTML);

  WiFi.softAPdisconnect();
  server.stop();

  ESP.reset();
}

void handleNotFound() {
  server.send(404, "text/html", "<h1>Not Found</h1>");
}

// MQTT Broker
const char *mqtt_broker = "mqtt.nlu-office.ch";
const int mqtt_port = 2883;

WiFiClient espClient;
PubSubClient client(espClient);

void setupMode() {
  setup_mode = true;

  int ap_id = random(10, 99);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ap_name + ap_id);

  server.on("/", handleConnection);
  server.on("/submit", handleSubmit);
  server.onNotFound(handleNotFound);

  server.begin();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  Serial.println();
  
  pinMode(BUTTON, INPUT);
  pinMode(ANALOG_POWER, OUTPUT);
  pinMode(ANALOG_SELECT, OUTPUT);
  pinMode(SENSOR_POWER, OUTPUT);
  pinMode(BATTERY_POWER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  String ssid = readEEPROM(0, 32);
  String password = readEEPROM(32, 64);

  Serial.print("EEPROM SSID: ");
  Serial.println(ssid);
  Serial.print("EEPROM Password: ");
  Serial.println(password);

  if(ssid.length() > 0) {
    WiFi.begin(ssid, password);
  }

  delay(2000);
  int button_state = digitalRead(BUTTON);
  if(button_state == HIGH) setupMode();

  client.setServer(mqtt_broker, mqtt_port);
}

void loop() {
  if(setup_mode) {
    if(millis() - last_blink > 200) {
      digitalWrite(LED_BUILTIN, blink_state ? LOW : HIGH);
      blink_state = !blink_state;
      last_blink = millis();
    }

    server.handleClient();
  } else {
    if(WiFi.status() == WL_CONNECTED && client.connect(WiFi.macAddress().c_str())) {
      if(blink_state) {
        digitalWrite(LED_BUILTIN, LOW);
        blink_state = !blink_state;
      }

      digitalWrite(ANALOG_POWER, HIGH);
      digitalWrite(ANALOG_SELECT, LOW);
      digitalWrite(SENSOR_POWER, HIGH);
      delay(10);

      int sensor_value = analogRead(A0);
      String sonsor_topic = "soilmoisture/" + WiFi.macAddress() + "/sensor";
      client.publish(sonsor_topic.c_str(), String(sensor_value).c_str());
      client.loop();

      digitalWrite(SENSOR_POWER, LOW);
      digitalWrite(ANALOG_SELECT, HIGH);
      digitalWrite(BATTERY_POWER, HIGH);
      delay(10);

      int battery_value = analogRead(A0);
      String battery_topic = "soilmoisture/" + WiFi.macAddress() + "/battery";
      client.publish(battery_topic.c_str(), String(battery_value).c_str());
      client.loop();

      digitalWrite(ANALOG_POWER, LOW);
      digitalWrite(ANALOG_SELECT, LOW);
      digitalWrite(BATTERY_POWER, LOW);
      delay(10);

      client.disconnect();
      WiFi.disconnect();
      espClient.stop();

      int button_state = digitalRead(BUTTON);
      if(button_state == HIGH) setupMode();
      else {
        ESP.deepSleep(30e6);
        delay(1000);
      }
    } else {
      if(millis() - last_blink > 1000) {
        digitalWrite(LED_BUILTIN, blink_state ? LOW : HIGH);
        blink_state = !blink_state;
        last_blink = millis();
      }
    }
  }

  if(millis() > 30e6) {
    ESP.deepSleep(60e6);
    delay(1000);
  }
}