#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

#define POTENCIOMETRO 34
#define LDR 35
#define LED 26 


const char* ssid = "Colocar SSID preferido";
const char* password = "Senha SSID";
const char* mqtt_server = "Colocar servidor escolhido";
const char* mqtt_topic_pub = "projetoIoT/status";
const char* mqtt_topic_sub = "projetoIoT/controle";
const int mqtt_port = 1883; //porta universal e publica

WiFiClient espClient;
PubSubClient client(espClient);

float corrente = 0;
float tensao = 5.0; 
float watt = 0;
float luminosidade = 0;
float limite_corrente = 2.0;


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String mensagem = "";
  for (unsigned int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }
  Serial.println("Mensagem: " + mensagem);

  
  if (String(topic) == mqtt_topic_sub) {
    if (mensagem == "ON") {
      digitalWrite(LED, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED Ligado");
    } else if (mensagem == "OFF") {
      digitalWrite(LED, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED Desligado");
    }
  }
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);


  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi!");

  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);


  pinMode(POTENCIOMETRO, INPUT);
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  
  int leituraPot = analogRead(POTENCIOMETRO);
  corrente = leituraPot * (5.0 / 4095);
  watt = corrente * tensao;


  int leituraLDR = analogRead(LDR);
  luminosidade = leituraLDR * (100.0 / 4095);


  char mensagem[50];
  sprintf(mensagem, "Corrente: %.2f A, Potencia: %.2f W", corrente, watt);
  client.publish(mqtt_topic_pub, mensagem);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Corrente:");
  lcd.print(corrente, 2);
  lcd.print("A");
  lcd.setCursor(0, 1);
  lcd.print("Potencia:");
  lcd.print(watt, 2);
  lcd.print("W");

  delay(1000);
}
