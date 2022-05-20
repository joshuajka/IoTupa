#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <SPI.h>



#define INTERVALO_ENVIO 5000
#define DEBUG
#define pinSensor D7 
#define SensorChuva A0 


char sentenca[128]; //AQUI
char valortemp[10];
float umidade;
float temperatura;
//int luminosidade;
int chuva; 



IPAddress server_addr(192, 168, 0, 9); 
char userSQL[] = "user";      
char passwordSQL[] = "senha";       

char INSERIR_TEMP[] = "INSERT INTO registrosensores (Temperatura) VALUES (%s)"; 
char BANCODEDADOS[] = "USE arduino"; 

DHTesp dht;

char MsgTemperaturaMQTT[10];
char MsgHumidadeMQTT[10];
//char MsgLuzMQTT[10]; 
char MsgChuvaMQTT[10]; 


//informações da rede WIFI

const char* ssid = "rede";        //SSID da rede WIFI
const char* password =  "senha";    //senha da rede wifi

//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT

const char* mqttServer = "soldier.cloudmqtt.com";   //server
const char* mqttUser = "888888888";    //user
const char* mqttPassword = "8888888888";  //password
const int mqttPort = 13924;          //port
const char* mqttTopicSub = "Teste/Casa"; //tópico que sera assinado

int ultimoEnvioMQTT = 0;

WiFiClient espClient;

MySQL_Connection conn((Client*)&espClient);

void setup() {
  pinMode(SensorChuva, INPUT);
  
  Serial.begin(9600);
  dht.setup(pinSensor, DHTesp::DHT22);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    Serial.println("Conectando ao WiFi..");
#endif
  }
#ifdef DEBUG
  Serial.println("Conectado na rede WiFi");
#endif


  Serial.println("Conectando ao Banco...");
  while (conn.connect(server_addr, 3306, userSQL, passwordSQL) != true) {
    delay(200);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado MySQL!");
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(BANCODEDADOS);
  delete cur_mem;
}

//função pra reconectar ao servido MQTT


void loop() {

  if ((millis() - ultimoEnvioMQTT) > INTERVALO_ENVIO)
  {
    dadosDTH22();

    ultimoEnvioMQTT = millis();
  }
}


void dadosDTH22() {
  umidade = dht.getHumidity();
  temperatura = dht.getTemperature();
  //luminosidade = analogRead(luz); 
  chuva = analogRead(SensorChuva);  


   if(chuva < 500 && umidade > 65 ){
    sprintf(MsgChuvaMQTT, "%s", "Chovendo"); 
  }
  else if(chuva>=500){
    sprintf(MsgChuvaMQTT, "%s", "Sem chuva");
  }
  else{
    sprintf(MsgChuvaMQTT, "%s", "SEM DADOS"); 
  }


  Serial.print("{\"Umidade\": ");
  Serial.print(umidade);
  Serial.print(", \"Temp\": ");
  Serial.print(temperatura);
  Serial.print("\"Tempo\": ");
  Serial.print(MsgChuvaMQTT);
  Serial.print("}\n");

  
  dtostrf(temperatura, 4, 1, valortemp);

  sprintf(sentenca, INSERIR_TEMP, valortemp);
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(sentenca);
  delete cur_mem;


}
