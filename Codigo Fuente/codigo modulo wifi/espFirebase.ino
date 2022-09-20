/**********************************************************************************
 * TITULO: Código ESP8266 - FIREBASE
 * AUTOR: Jhimmy Astoraque Durán
 * DESCRIPCION: Este es el código de este episodio del canal que tambien es parte de la Serie Intermedia del esp8266
 * CANAL YOUTUBE: https://www.youtube.com/c/jadsatv
 * © 2020
 * *******************************************************************************/

#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"


// Credenciales wifi
const char *ssid = "1"; // nombre de la red
const char *password = "123456789";
//const char *ssid = "ZTE-d794ca"; // nombre de la red
//const char *password = "AMERICANO1";

// Credenciales Proyecto Firebase
const char *FIREBASE_HOST = "reices-v1-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "uyFpoKOnLr6iu2Y2Lhr4AKhUiuBNLg9LkbWJNP9J";

// Firebase Data object in the global scope
FirebaseData firebaseData;

bool iterar = true;


void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\nConectado al Wi-Fi");
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(5, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  String nodo = "Proyecto1";
  String users = "Users";
  String pr = "pr";

  //while (iterar)
  //{

    // escribir datos
   Firebase.setInt(firebaseData, "lectura1", 512);
   //Firebase.setInt(firebaseData, "luz");
   Firebase.setString(firebaseData, "string1", "On");

    Firebase.setString(firebaseData, nodo + "/sensor", "DHT11");
    Firebase.setString(firebaseData, pr + "/sensor" + "/hola", "lucesita");
    //Firebase.setInt(firebaseData, nodo + "/temperatura", 31);
    //Firebase.setBool(firebaseData, nodo + "/alarmas", false);

    // leer datos
     Firebase.getInt(firebaseData,users+ "/jorge" + "/luz1");
     //Serial.println(firebaseData.intData());
     if ( firebaseData.intData()== 1)
     {
      digitalWrite(5, HIGH);
     }
     else{
      digitalWrite(5, LOW);
     }
     delay(0);
     Firebase.getInt(firebaseData,users +"/jorge" + "/luz2");
      if ( firebaseData.intData()== 1)
     {
      digitalWrite(16, HIGH);
     }
     else{
      digitalWrite(16, LOW);
     }
     delay(0);
     Firebase.getInt(firebaseData,users + "/jorge" + "/luz3");
      if ( firebaseData.intData()== 1)
     {
      digitalWrite(4, HIGH);
     }
     else{
      digitalWrite(4, LOW);
     }
     delay(0);
     //Firebase.getString(firebaseData, nodo + "/sensor");
    // Serial.println(firebaseData.stringData());

    // push de datos
    //  Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
    //  delay(150);
    //  Firebase.pushInt(firebaseData, nodo + "/temperatura", 31);
    //  delay(150);
    //  Firebase.pushInt(firebaseData, nodo + "/temperatura", 30);
    //  delay(150);
    //  Firebase.pushInt(firebaseData, nodo + "/Humedad", 67);

   // iterar = false;
    //Firebase.end(firebaseData);
  //}
} // End Loop
