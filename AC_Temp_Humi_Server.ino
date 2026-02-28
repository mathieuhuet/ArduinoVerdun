
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include "ACS712.h"
#define DHT22_PIN_INSIDE  D4 
#define DHT22_PIN_OUTSIDE  D6
#define DHT22_PIN_INSIDE2  D8 

const int ACControlpin = 2;
const int SensorResetControlpin = 3;
const int SensorNegativeContactControlpin = 7;
const int LightControlpin = 9;

const char* ssid     = "Suspiria";
const char* password = "jeudredi";

IPAddress local_IP(192, 168, 1, 40);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

DHT insideTemp(DHT22_PIN_INSIDE, DHT22);
DHT outsideTemp(DHT22_PIN_OUTSIDE, DHT22);
DHT insideTemp2(DHT22_PIN_INSIDE2, DHT22);

//Amp meter ACS712
ACS712 sensor(ACS712_30A, A0);

WebServer server(80);


void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// MorseCode through control pin
void displayMessageInMorseCode(String text) {
  text.toLowerCase();
  for (int i = 0; i < text.length(); i++) {
    char character = text.charAt(i);
    if (character == 'a') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'b') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'c') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'd') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'e') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'f') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'g') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'h') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'i') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'j') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'k') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'l') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'm') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'n') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'o') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'p') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 'q') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'r') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 's') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == 't') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'u') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'v') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'w') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'x') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'y') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == 'z') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '1') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == '2') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == '3') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == '4') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == '5') {
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '6') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '7') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '8') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '9') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(500);
    } else if (character == '0') {
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
      digitalWrite(LightControlpin, LOW);
      delay(500);
      digitalWrite(LightControlpin, HIGH);
      delay(1200);
    } else if (character == ' ') {
      delay(1500);
    }
    //Pause between character
    digitalWrite(LightControlpin, LOW);
    delay(2100);
  }
}




void setup(void) {
  insideTemp.begin(); // initialize the DHT22 sensor
  outsideTemp.begin(); // initialize the DHT22 sensor
  insideTemp2.begin(); // initialize the DHT22 sensor
  sensor.calibrate(); // initializa amp sensor ACS712
  pinMode(ACControlpin, OUTPUT);
  pinMode(SensorResetControlpin, OUTPUT);
  pinMode(SensorNegativeContactControlpin, OUTPUT);
  pinMode(LightControlpin, OUTPUT);
  Serial.begin(115200);
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  //Turn OFF AC
  server.on("/H", []() {
    digitalWrite(ACControlpin, HIGH); 
    server.send(200, "application/json", "{\"command\": \"OFF\"}");
  });
  //Connected to Temp sensor power supply + "OFF"
  server.on("/RelayOff", []() {
    digitalWrite(SensorResetControlpin, LOW); 
    server.send(200, "application/json", "{\"command\": \"OFF\"}");
  });
  //Connected to Temp sensor power supply + "ON"
  server.on("/RelayOn", []() {
    digitalWrite(SensorResetControlpin, HIGH); 
    server.send(200, "application/json", "{\"command\": \"ON\"}");
  });
  //Connected to Temp sensor power supply - "OFF"
  server.on("/RelayNegativeOff", []() {
    digitalWrite(SensorNegativeContactControlpin, LOW); 
    server.send(200, "application/json", "{\"command\": \"OFF\"}");
  });
  //Connected to Temp sensor power supply - "ON"
  server.on("/RelayNegativeOn", []() {
    digitalWrite(SensorNegativeContactControlpin, HIGH); 
    server.send(200, "application/json", "{\"command\": \"ON\"}");
  });
  //Turn ON AC
  server.on("/L", []() {
    digitalWrite(ACControlpin, LOW); 
    server.send(200, "application/json", "{\"command\": \"ON\"}");
  });
  //Turn ON Light
  server.on("/turnonlight", []() {
    digitalWrite(LightControlpin, HIGH); 
    server.send(200, "application/json", "{\"command\": \"ON\"}");
  });
  //Turn OFF Light
  server.on("/turnofflight", []() {
    digitalWrite(LightControlpin, LOW); 
    server.send(200, "application/json", "{\"command\": \"OFF\"}");
  });

  //Get state of all Arduino reading
  server.on("/get", []() {
    float IT = insideTemp.readTemperature();
    float IH = insideTemp.readHumidity();
    float OT = outsideTemp.readTemperature();
    float OH = outsideTemp.readHumidity();
    float IT2 = insideTemp2.readTemperature();
    float IH2 = insideTemp2.readHumidity();
    String ACSTATE = "unknown";
    String LIGHTSTATE = "unknown";
    if (digitalRead(ACControlpin) == HIGH) {
      ACSTATE = "OFF";
    } else if (digitalRead(ACControlpin) == LOW) {
      ACSTATE = "ON";
    }
    if (digitalRead(LightControlpin) == HIGH) {
      LIGHTSTATE = "ON";
    } else if (digitalRead(LightControlpin) == LOW) {
      LIGHTSTATE = "OFF";
    }
    server.send(200, "application/json", "{\"insideTemp\": \"" + String(IT) + "\", \"insideHumi\" : \"" + String(IH) + "\" , \"outsideTemp\": \"" + String(OT) + "\", \"outsideHumi\" : \"" + String(OH) + "\", \"insideTemp2\": \"" + String(IT2) + "\", \"insideHumi2\" : \"" + String(IH2) + "\", \"acstate\" : \"" + ACSTATE + "\", \"lightstate\" : \"" + LIGHTSTATE + "\"}");
  });

  //get AC status
  server.on("/status", []() {
    if (digitalRead(ACControlpin) == HIGH) {
      server.send(200, "application/json", "{\"state\": \"OFF\"}");
    } else if (digitalRead(ACControlpin) == LOW) {
      server.send(200, "application/json", "{\"state\": \"ON\"}");
    }
  });

  server.on("/insidetemp", []() {
    float res = insideTemp.readTemperature();
    server.send(200, "application/json", "{\"temp\": \"" + String(res) + "\"}");
  });
  server.on("/insidehumi", []() {
    float res = insideTemp.readHumidity();
    server.send(200, "application/json", "{\"humi\": \"" + String(res) + "\"}");
  });
  server.on("/outsidetemp", []() {
    float res = outsideTemp.readTemperature();
    server.send(200, "application/json", "{\"temp\": \"" + String(res) + "\"}");
  });
  server.on("/outsidehumi", []() {
    float res = outsideTemp.readHumidity();
    server.send(200, "application/json", "{\"humi\": \"" + String(res) + "\"}");
  });
  server.on("/insidetemp2", []() {
    float res = insideTemp2.readTemperature();
    server.send(200, "application/json", "{\"temp\": \"" + String(res) + "\"}");
  });
  server.on("/insidehumi2", []() {
    float res = insideTemp2.readHumidity();
    server.send(200, "application/json", "{\"humi\": \"" + String(res) + "\"}");
  });

  //Get Current from current sensor(current reading not working well, not accurate)
  server.on("/getCurrent", [](){
    float I = sensor.getCurrentAC();
  //ignoring the value below 0.09
    if (I < 0.09) {
      I = 0;
    }
    Serial.println(I);
    server.send(200, "application/json", "{\"Current\": \"" + String(I)+ "\"");
  });

  //Broadcast Message Morse 192.168.1.40/sendmessage?message=messagetosend
  server.on("/sendmessage", []() {
    String message = server.arg("message");
    if (digitalRead(LightControlpin) == HIGH) {
      digitalWrite(LightControlpin, LOW);
      delay(3000);
    }
    server.send(200, "application/json", "{\"Message to announce\": \"" + message + "\"}");
    displayMessageInMorseCode(message);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
