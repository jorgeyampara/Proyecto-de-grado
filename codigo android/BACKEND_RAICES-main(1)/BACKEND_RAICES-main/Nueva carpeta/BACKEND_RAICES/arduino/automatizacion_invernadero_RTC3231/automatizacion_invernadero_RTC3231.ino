// Con Arduino NANO,(RTC), Modulo Rele, Modulo I2C para LCD 2x16, modulo DHT11 
// Conexion i2C :Arduino UNO/NANO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
// Conexion RTC3231 :Arduino NANO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
// NOTA: se debe cargar dos veces este programa 1. Con la linea "RTC.adjust(DateTime(__DATE__, __TIME__));" y otra sin ella
#include <Wire.h> 
#include "RTClib.h"
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
const int sensorDHT = 2;           // pin 2 encargado de leer el sensor DHT11
DHT dht (sensorDHT, DHT11);
LiquidCrystal_I2C lcd(0x27,16,2);  // inicializa la interfaz I2C del LCD 16x2
RTC_DS1307 RTC;                    // inicializa el modulo RTC

const int bomba_1 = 3;             // Pin 3 encargado de activar bomba 1
const int bomba_2 = 4;             // pin 4 encargado de activar bomba 2
const int oxigenadores = 5;        // pin 5 encargado de activar oxigenadores
const int ventiladores = 6;        // Pin 6 encargado de activar ventiladores
int temp, humedad;
int minuto;
int hora;
int tr;
int purgar;
int hora_inicio = 6;
int hora_fin = 18;
int h1_b = 6;
int tipo_riego = 3;
int tiempo_riego = 5;

int contacto1;
int contacto2;
int contacto3;
int estado_1 = 4;
int estado_2 = 2;
int estado_3 = 4;
int estado_anterior1 = 0;
int estado_anterior2 = 0;
int estado_anterior3 = 0;
int oxi = 0;


//////////////////////////////// tiempo oxigenadores /////////////////////////
int h1_o=5;   int m1_o=30;
int h2_o=8;   int m2_o=30;
int h3_o=11;  int m3_o=30;
int h4_o=14;   int m4_o=30;
int h5_o=17;  int m5_o=30;
////////////////////////////////// Void Setup() ///////////
void setup () { 
 
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
 pinMode(bomba_1, OUTPUT);                    // Configura como salida el pin 3
 pinMode(bomba_2, OUTPUT);                    // configura como salida el pin 4
 pinMode(oxigenadores, OUTPUT);               // configura como salida el pin 5
 pinMode(ventiladores, OUTPUT);               // configura como salida el pin 6
 digitalWrite(bomba_1, HIGH);
 digitalWrite(bomba_2, HIGH);
    
    Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600 
    dht.begin();
    Wire.begin();                               
    RTC.begin();                                // Inicia la comunicacion con el RTC 
    lcd.init();
    lcd.backlight();                            // Coloca luz de fondo al LCD
    lcd.clear();                                // Borra el  LCD
    
//RTC.adjust(DateTime(__DATE__, __TIME__));
}
////////////////////////////////// Void loop() ///////////
void loop(){
  lcd.clear();
  humedad = dht.readHumidity(); //Funcion incluida en la libreria. Permite leer la humedad.
  temp = dht.readTemperature(); //Permite leer la temperatura.
  DateTime now = RTC.now();    // Obtiene la fecha y hora del RTC

 contacto1 = digitalRead(A0);    //lee el valor de los contactos para escoger configuraciones
 contacto2 = digitalRead(A1);    //modifica los valores de configuracion
 contacto3 = digitalRead(A2);    //guardar configuracion

 if ((contacto1 == HIGH) && (estado_anterior1 == LOW)){
  estado_anterior1 = contacto1;
  lcd.clear();
    while (estado_1 > 0) {
    if (estado_1 == 4){
    contacto2 = digitalRead(A1);
    if ((contacto2 == HIGH) && (estado_anterior2 == LOW)){
      estado_anterior2 = contacto2;
      lcd.clear();
      tiempo_riego = tiempo_riego + 5;
      if (tiempo_riego > 20){
        tiempo_riego = 5;
      }
    }
    delay(20);
    estado_anterior2 = contacto2;
    
    lcd.setCursor(0,0);
    lcd.print("CONFIGURAR");
    lcd.setCursor(0,1);
    lcd.print("tiempo_riego:");
    lcd.print(tiempo_riego);
    delay(100);
    contacto1 = digitalRead(A0);
    if ((contacto1 == HIGH) && (estado_anterior1 == LOW)){
      estado_anterior1 = contacto1;
      estado_1 = (estado_1 - 1);
    }
    contacto3 = digitalRead(A2);
    if (contacto3 == HIGH){
      estado_1 = 0;
    }
   }
   
   if (estado_1 == 2){
     while (estado_2 == 2){
      contacto2 = digitalRead(A1);
      if (contacto2 == HIGH){
      hora_inicio = hora_inicio + 1;
      if (hora_inicio > 12){
        hora_inicio = 6;
      }
    }
    h1_b = hora_inicio;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CONFIGURAR");
    lcd.setCursor(0,1);
    lcd.print("hora_inicio:");
    lcd.print(hora_inicio);
    delay(100);
    contacto3 = digitalRead(A2);
    if (contacto3 == HIGH){
      estado_2 = (estado_2 - 1);
    }
    contacto1 = digitalRead(A0);
    if (contacto1 == HIGH && estado_anterior == LOW){
      estado_1 = 0;
      estado_2 = 0;
     }
     delay(20);
    estado_anterior = contacto1;
     }
    while (estado_2 == 1){
      contacto2 = digitalRead(A1);
      if (contacto2 == HIGH){
      hora_fin = hora_fin + 1;
      if (hora_fin > 20){
        hora_fin = 15;
      }
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CONFIGURAR");
    lcd.setCursor(0,1);
    lcd.print("hora_fin:");
    lcd.print(hora_fin);
    delay(100);
    contacto3 = digitalRead(A2);
    if (contacto3 == HIGH){
      estado_2 = (estado_2 - 1);
      estado_1 = (estado_1 - 1);
    }
    contacto1 = digitalRead(A0);
    if (contacto1 == HIGH && estado_anterior == LOW){
      estado_1 = 0;
      estado_2 = 0;
     }
     delay(20);
    estado_anterior = contacto1;
     }
   }
   if (estado_1 == 1){
    contacto2 = digitalRead(A1);
    if (contacto2 == HIGH){
      tipo_riego = tipo_riego + 1;
      if (tipo_riego > 4){
        tipo_riego = 1;
      }
    }
    
    lcd.setCursor(0,0);
    lcd.print("CONFIGURAR");
    lcd.setCursor(0,1);
    lcd.print("tipo riego:");
    lcd.print(tipo_riego);
    delay(100);
    contacto3 = digitalRead(A2);
    if (contacto3 == HIGH){
      estado_1 = (estado_1 - 1);
    }
    contacto1 = digitalRead(A0);
    if (contacto1 == HIGH && estado_anterior1 == LOW){
      estado_1 = 0;
    }
    delay(20);
    estado_anterior1 = contacto1;
   }
   
   }
   }
   delay(20);
   estado_anterior1 = contacto1;
 
 while (contacto3 == HIGH){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("PR:");
     lcd.print(hora_inicio);
     lcd.print(":");
     lcd.print(hora_fin);
     lcd.print(" ");
     lcd.print("TR:");
     lcd.print(tr = tiempo_riego / 60000);
     lcd.setCursor(0,1);
     lcd.print("TIPO:");
     if (tipo_riego == 1){
      lcd.print("bomba 1");
     }
     if (tipo_riego == 2){
      lcd.print("bomba 2");
     }
     if (tipo_riego == 3){
      lcd.print("bombas 1,2");
     }
     if (tipo_riego == 4){
      lcd.print("purgar 1,2");
     }
     delay(1000);
     contacto3 = digitalRead(A2);
   }
   if (estado_1 == 0){
    estado_1 = 3;
   }
   if (estado_2 == 0){
    estado_2 = 2;
   }


   
 Serial.print(now.Day(), DEC);  // Dia
 Serial.print('/');
 Serial.print(now.Month(), DEC); // Mes
 Serial.print('/');
 Serial.print(now.Year(), DEC);   // Año
 Serial.print(' ');
 Serial.print(now.Hour(), DEC);  // Horas
 Serial.print(':');
 Serial.print(now.Minute(), DEC); // Minutos
 Serial.print(':');
 Serial.print(now.Second(), DEC); // Segundos
 Serial.println();

 hora = now.Hour();
 minuto = now.Minute();

 lcd.setCursor(0,0);
 lcd.print(now.Day(), DEC);
 lcd.print("/");
 lcd.print(now.Month(), DEC);
 lcd.print("/");
 lcd.print(now.Year(), DEC);
 lcd.print(" ");
 lcd.setCursor(11,0);
 lcd.print("HR");
 lcd.print(humedad);
 lcd.print("%");
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print(now.Hour(), DEC);
 lcd.print(":");
 lcd.print(now.Minute(), DEC);
 lcd.print(":");
 lcd.print(now.Second(), DEC);
 lcd.print(" ");
 lcd.setCursor(12,1);
 lcd.print("T");
 lcd.print(temp);
 lcd.print("C");

 
 dia_de_semana(), oxigenar(), riego_bombas(), riego_purgar();
  
      
delay(500);

}

//////////////////////////////// Fin del void loop(), inician las Funciones /////////////////////////

/////////////////////////////// Calcula el dia de la Semana //////////////////////////////////
void dia_de_semana(){   // Encuentar el dia de la semana de una fecha
 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo=6;

 DateTime now = RTC.now(); //fecha y hora del RTC
 lcd.setCursor(8,1);

 n_anno=(now.Year()-2000);
 d_anno=n_anno/4;
 n_dia=now.day();
 n_mes=now.month();

 switch (n_mes) {
    case 1:
      t_mes=0;
      break;
    case 2:
      t_mes=3;
      break;
    case 3:
      t_mes=3;
      break;
    case 4:
      t_mes=6;
      break;
    case 5:
      t_mes=1;
      break;
    case 6:
      t_mes=4;
      break;
    case 7:
      t_mes=6;
      break;
    case 8:
      t_mes=2;
      break;
    case 9:
      t_mes=5;
      break;
    case 10:
      t_mes=0;
      break;
    case 11:
      t_mes=3;
      break;
    case 12:
      t_mes=5;
      break;
    default: 
      t_mes=t_mes;
    break;
 }

 r_dia=n_dia+t_mes+n_anno+d_anno+t_siglo;
 r_dia = r_dia % 7;

 switch (r_dia) {
    case 1:
       lcd.print("Lun");
        Serial.print(" Lun ");
      break;
      case 2:
       lcd.print("Mar");
       Serial.println(" Mar ");
      break;
      case 3:
       lcd.print("Mie");
       Serial.print(" Mie ");
      break;
      case 4:
       lcd.print("Jue");
       Serial.print(" Jue ");
      break;
      case 5:
       lcd.print("Vie");
       Serial.print(" Vie ");
      break;
      case 6:
       lcd.print("Sab");
       Serial.print(" Sab ");
      break;
      case 0:
       lcd.print("Dom");
       Serial.print(" Dom ");
      break;
      default: 
       lcd.print("---");
       Serial.print(" --- ");
      break;
 } 
 return r_dia; 
}

/////////////////////////////// Funcion que activa bombas //////////////////////////////////
void activar_bombas(){
  lcd.clear();
    if (tipo_riego == 1){
    digitalWrite(bomba_1, LOW); 
    lcd.setCursor(0,0);
    lcd.print("bomba 1   ");
    Serial.println("Bomba 1 Activo");
    }
    if (tipo_riego == 2){
    digitalWrite(bomba_2, LOW); 
    lcd.setCursor(0,0);
    lcd.print("bomba 2   ");
    Serial.println("bomba 2 activo");
    }
    if (tipo_riego == 3){
    digitalWrite(bomba_1, LOW);
    digitalWrite(bomba_2, LOW); 
    lcd.setCursor(0,0);
    lcd.print("bombas 1,2");
    Serial.println("riego total");
    }
    
    delay(tiempo_riego);
    digitalWrite(bomba_1, HIGH);
    digitalWrite(bomba_2, HIGH);
}
/////////////////////condicion de riego bombas//////////////////////////////////
void riego_bombas(){ 

   if (hora > h1_b){
    h1_b = (hora - h1_b) + (h1_b + 1);
   }
   if (hora == h1_b && h1_b <= hora_fin){
    activar_bombas();
    h1_b = h1_b + 1;
   }
   if (h1_b > hora_inicio && hora_fin < hora){
    h1_b = hora_inicio;
   }
}

/////////////////////////////// Funcion que activa purgar //////////////////////////////////
void activar_purgar(){
    contacto2 = digitalRead(A1);
    if (contacto2 == HIGH && estado_anterior2 == LOW){
      purgar = 1 - purgar;
      lcd.clear();
      delay(20);
    }
    estado_anterior2 = contacto2;
    if (purgar == 1){
      digitalWrite(bomba_1, LOW);
      digitalWrite(bomba_2, LOW); 
      lcd.setCursor(0,0);
      lcd.print("purgar 1,2");
      Serial.println("purgar tanques");
    }
    else {
      digitalWrite(bomba_1, HIGH);
      digitalWrite(bomba_2, HIGH);
    }
    delay(500);
}
/////////////////////condicion de purgar//////////////////////////////////
void riego_purgar(){ 

   if (tipo_riego == 4){
    activar_purgar();
   }

}
/////////////////////condicion de riego micro bomba//////////////////////////////////
void oxigenar(){ 

   if ((hora==h1_o) && (minuto>=m1_o))  activar_oxigenadores();
   if ((hora==h2_o) && (minuto>=m2_o))  activar_oxigenadores();
   if ((hora==h3_o) && (minuto>=m3_o))  activar_oxigenadores();
   if ((hora==h4_o) && (minuto>=m4_o))  activar_oxigenadores();
   if ((hora==h5_o) && (minuto>=m5_o))  activar_oxigenadores();
}
/////////////////////////////// Funcion que activa oxigenadores //////////////////////////////////
void activar_oxigenadores(){
  while (minuto <= 55){
    digitalWrite(oxigenadores, LOW); 
    Serial.println("oxigenando");
  }
    digitalWrite(oxigenadores, HIGH);
}








