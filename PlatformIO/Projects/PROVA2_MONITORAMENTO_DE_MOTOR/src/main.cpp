#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// --- 1. CONFIGURAÇÕES (WIFI e MQTT) ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

// TÓPICO OBRIGATÓRIO (Mude SEU_NOME)
const char* topic_publish = "senai/MATEUS/motor/dados"; 

// --- 2. HARDWARE (PINAGEM DO ANEXO 1) ---
#define PIN_DHT 15       // Temperatura
#define PIN_VIB 34       // Vibração (Potenciômetro 1)
#define PIN_COR 35       // Corrente (Potenciômetro 2)

// LEDs (Sua lógica de semáforo para vibração)
#define LED_VERDE 12     // GPIO 12
#define LED_AMARELO 14   // GPIO 14 (Adicional para alerta)
#define LED_VERMELHO 27  // GPIO 27 (Adicional para perigo)

// --- 3. OBJETOS ---
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(PIN_DHT, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Configura Pinos
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Inicia Sensores
  dht.begin();
  lcd.init();
  lcd.backlight();

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");

  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    String clientId = "ESP32_Motor_" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("OK!");
    } else {
      Serial.print("Falha: ");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // --- 4. LEITURA E MAPEAMENTO ---
  
  // A) Temperatura
  float temp = dht.readTemperature();
  if (isnan(temp)) temp = 0.0;

  // B) Vibração (0-4095 -> 0-100%)
  int leituraVib = analogRead(PIN_VIB);
  int vibracao = map(leituraVib, 0, 4095, 0, 100);

  // C) Corrente (0-4095 -> 0-100 A)
  int leituraCor = analogRead(PIN_COR);
  int corrente = map(leituraCor, 0, 4095, 0, 100);

  // --- 5. LÓGICA DE LEDS (Baseada na VIBRAÇÃO) ---
  // Reseta
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  if (vibracao < 35) {
    digitalWrite(LED_VERDE, HIGH); // Normal
  } else if (vibracao >= 35 && vibracao < 45) {
    digitalWrite(LED_AMARELO, HIGH); // Alerta
  } else {
    digitalWrite(LED_VERMELHO, HIGH); // Perigo (>45)
  }

  // --- 6. LCD (MOSTRAR DADOS BRUTOS) ---
  lcd.clear();
  lcd.setCursor(0,0);
  // Ex: T:25.0 V:10%
  lcd.print("T:"); lcd.print(temp, 1); lcd.print(" V:"); lcd.print(vibracao); lcd.print("%");
  
  lcd.setCursor(0,1);
  // Ex: C:12A St:OK
  lcd.print("C:"); lcd.print(corrente); lcd.print("A");

  // --- 7. ENVIO FORMATO STRING SIMPLES (ANEXO 1) ---
  // O Anexo pede: temperatura,vibracao,corrente
  
  String payload = String(temp, 1) + "," + String(vibracao) + "," + String(corrente);

  Serial.print("Enviando: ");
  Serial.println(payload);

  client.publish(topic_publish, payload.c_str());

  delay(2000); // Envia a cada 2 segundos
}