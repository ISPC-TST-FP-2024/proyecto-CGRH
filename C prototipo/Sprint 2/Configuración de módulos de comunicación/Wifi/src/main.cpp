#include <Arduino.h>
#include<ESP8266WiFiMulti.h>
#include<ESP8266HTTPClient.h>

const char* ssid = "wifi";
const char* password = "Contra";

String user = "ioticos";
String pass = "pingpong";

void setup() {
  delay(10);
  Serial.begin(115200);

 WiFi.begin("conectando...");
 while (WiFi.status() != WL_CONNECTED)
 {
  delay(500);
  Serial.print(".");
 }
 Serial.print("contado con exito, mi ip es;");
 Serial.println(WiFi.localIP());


}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String datos_a_enviar = "?user=" + user + "&pass" + pass;
    
    http.begin("http://wwww.php");
    http.addHeader("conte.Type","aplication" );
    int codigo_respuesta =http.POST(datos_a_enviar);

    if(codigo_respuesta >=0){
      Serial.println("codigo HTTP " + String(codigo_respuesta));
      
      if(codigo_respuesta == 200){
        String cuerpo_respuessta = http.getString();
        Serial.println("El servidor respondio");
        Serial.println(cuerpo_respuessta);
      }
      http.end();
    }else{
      Serial.println("Error en la conexion wifi");
    }
    delay(2000);
  }

}
