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
char passwordSQL[] = "pass";       

char INSERIR_TEMP[] = "INSERT INTO registrosensores (Temperatura) VALUES (%s)"; 
char BANCODEDADOS[] = "USE arduino"; 

DHTesp dht;

char MsgTemperaturaMQTT[10];
char MsgHumidadeMQTT[10];
//char MsgLuzMQTT[10]; 
char MsgChuvaMQTT[10]; 


//informações da rede WIFI

//const char* ssid = "user";        //SSID da rede WIFI
//const char* password =  "pass";    //senha da rede wifi

const char* ssid = "user";        //SSID da rede WIFI
const char* password =  "pass";


//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT

const char* mqttServer = "soldier.cloudmqtt.com";   //server
const char* mqttUser = "8888888";    //user
const char* mqttPassword = "88888888";  //password
const int mqttPort = 13924;          //port
const char* mqttTopicSub = "Teste/Casa"; //tópico que sera assinado

int ultimoEnvioMQTT = 0;

WiFiClient espClient;

PubSubClient client(espClient);

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

  client.setServer(mqttServer, mqttPort);


  while (!client.connected()) {
#ifdef DEBUG
    Serial.println("Conectando ao Broker MQTT...");
#endif

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
#ifdef DEBUG
      Serial.println("Conectado");
#endif

    } else {
#ifdef DEBUG
      Serial.print("falha estado  ");
      Serial.print(client.state());
#endif
      delay(2000);

    }
  }

  //subscreve no tópico

  client.subscribe(mqttTopicSub);

/*
  Serial.println("Conectando ao Banco...");
  while (conn.connect(server_addr, 3306, userSQL, passwordSQL) != true) {
    delay(200);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado MySQL!");
*/
}

//função pra reconectar ao servido MQTT

void reconect() {

  //Enquanto estiver desconectado

  while (!client.connected()) {
#ifdef DEBUG
    Serial.println("Tentando conectar ao servidor MQTT");
#endif

    bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP8266Client", mqttUser, mqttPassword) :
                     client.connect("ESP8266Client");

    if (conectado) {
#ifdef DEBUG
      Serial.println("Conectado!");
#endif

      //subscreve no tópico

      client.subscribe(mqttTopicSub, 1); //nivel de qualidade: QoS 1
    } else {

#ifdef DEBUG
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Tentando novamente em 10 s");
#endif

      //Aguarda 10 segundos

      delay(10000);
    }
  }
}



void loop() {
  if (!client.connected()) {
    reconect();
  }

  //envia a cada X segundos

  if ((millis() - ultimoEnvioMQTT) > INTERVALO_ENVIO)
  {
    dadosDTH22();

    ultimoEnvioMQTT = millis();
  }

  client.loop();
}


void dadosDTH22() {
  umidade = dht.getHumidity();
  temperatura = dht.getTemperature();
  //luminosidade = analogRead(luz); 
  chuva = analogRead(SensorChuva);  

//&& umidade > 65 

   if(chuva < 700){
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
  Serial.print("\"Leitura sensor\": ");
  Serial.print(chuva);
  Serial.print("}\n");

  sprintf(MsgTemperaturaMQTT, "%f", temperatura);
  client.publish("Temperatura", MsgTemperaturaMQTT);

  sprintf(MsgHumidadeMQTT, "%f", umidade);
  client.publish("Umidade", MsgHumidadeMQTT); 

  client.publish("Tempo", MsgChuvaMQTT);


  /*
  sprintf(MsgLuzMQTT, "%d", luminosidade);
  client.publish("Luminosidade", MsgLuzMQTT);*/

  
  /*dtostrf(temperatura, 4, 1, valortemp);
  sprintf(sentenca, INSERIR_TEMP, valortemp);
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(sentenca);
  delete cur_mem;*/


}
