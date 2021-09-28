#include <Arduino.h>

#include <ESP8266WiFi.h>                  //Incluye la librer\U{ed}a ESP8266WiFi
#include <ESP8266WebServer.h>              // esta libreria trae las funciones para que nuestro dispositivo funcione como servidor web

// Configuración STA se va conectar al modem

//const char ssid[] = "NodeMCU-ESP8266";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red- 
//const char password[] = "12345678";       //Definimos la contrase\U{f1}a de nuestro servidor debe ser minimo de 8 caracteres

const char* ssid = "INFINITUM84B7_2.4";  // Escribir nombre de la red a la que nos vamos a conectar
const char* password = "7A9mQgsbgU";  //Escribir el Password 



ESP8266WebServer server(80);
                  //Definimos el puerto de comunicaciones
int PinLED = 2;                           //Definimos el pin de salida - GPIO2 / D4

bool estado = HIGH;                         //Definimos la variable que va a recoger el estado del LED



String SendHTML(uint8_t estado2){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
   if(estado2)  // si estado2 es HIGH
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-off\" href=\"/led1off\">ON</a>\n";}
  else
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-on\" href=\"/led1on\">OFF</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void handle_OnConnect() {
  estado = HIGH;  /// esta apagado mi led
 // Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(estado)); 
}

void handle_led1on() {
  estado = LOW;  // se prende el led
  //Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true)); 
}

void handle_led1off() {
  estado = HIGH; // se apaga el led
  //Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false)); 
}

void setup() {

  Serial.begin(115200);                   // Se habilita la comunicaci\U{f3}n serial
  pinMode(PinLED, OUTPUT);                //Inicializamos el GPIO2 como salida
  
  WiFi.begin(ssid, password);            // iniciamos conexion con el modem


  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());   //  imprimir la ip en el monitor serial que nos asigna el modem
  

  server.on("/", handle_OnConnect);   // se define la funcion que se ejecuta al estar en la raiz
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);

  server.begin();  /// se inicia el servidor web


}


void loop() 
{
  
   server.handleClient();

  if(estado)
  {
    digitalWrite(PinLED, HIGH);
    }
  else

  {
    digitalWrite(PinLED, LOW);
    }

}      