#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// Conexion a punto de acceso wifi
#define WIFI_SSID "iPhoneSaidani"
#define WIFI_PASSWORD "632062065"

// El pin digital donde se conecta el sensor
#define DHTPIN 4

// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

String data;

void setup() {
  Serial.begin(9600);

  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println ("");
  Serial.println ("Se conectó al wifi!");
  Serial.println(WiFi.localIP());
  
  dht.begin();
}



void loop() {

  float t = dht.readTemperature();
  int h = dht.readHumidity(); 
  
  data = "temperature="+String(t)+"&humidity="+String(h);

  if (client.connect("172.20.10.2",80)) { // Preguntamos se si conectó a la IP del servidor 
    Serial.println("se conecto");
    client.println("POST /dht11phpmysql/backend/setData.php HTTP/1.1"); 
    client.println("Host: 172.20.10.2"); // IP del servidor
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
  } 

  if (client.connected()) { 
    client.stop();  // Disconectamos del servidor
  }

  delay(1000); // Cada 1 sengundo se envia los datos al servidor

}
