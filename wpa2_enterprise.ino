#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
  #include "c_types.h"
  #include "cert.h"
}

static const char* ssid = "ssid";

void setup(){
  Serial.begin(115200);
  Serial.printf("Connecting to %s\n", ssid);
  if (!wifi_set_opmode(STATION_MODE)) {
    Serial.print("Setting ESP into STATION mode only failed!");
  }

  struct station_config wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
 
  wifi_station_set_config(&wifi_config);
  wifi_station_set_wpa2_enterprise_auth(1);
  
  wifi_station_set_enterprise_cert_key((uint8*)user_cert, sizeof(user_cert), (uint8*)user_key, sizeof(user_key), (uint8*)user_key_pass, sizeof(user_key_pass));
  wifi_station_connect();
  delay(1000);
  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  wifi_station_clear_enterprise_cert_key();

  Serial.println("");
  Serial.println("Connected!");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("-----------------");
  delay(10000);
  Serial.println("Going into deep sleep");
  ESP.deepSleep(5e6);
}

void loop()
{
  
}
