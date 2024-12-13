#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 9 // Pino utilizado para controle do led azul
#define led_verde 41 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul
#define botaoPin 18;  // Pino utilizado para controle do botão
// Variavél booleana para verificar o estado do botão
bool buttomState = 0;
bool buttomLastState = 0;
bool sytemState = false;

const int ldrPin = 4;  // Pino utilizado para controle do sensor ldr
int threshold=600;


void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(botaoPin, INPUT); // Inicializa o botão como input

  //os leds iniciam desligados
  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi 
  //(outra opção é colocar este comando dentro do if abaixo)
  Serial.println("Conectado ao WiFi com sucesso!"); 

  // Verifica estado do botão
  botaoEstado = digitalRead(botaoPin);
  if (botaoEstado == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("Resultado da Requisição HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Erro: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Desconectado.");
  }
}

void loop() {
  int ldrstatus=analogRead(ldrPin);

  if(ldrstatus<=threshold){
    Serial.print("Está escuro, ligue a luz");
    Serial.println(ldrstatus);

  }else{
    Serial.print("Está claro, desligue a luz");
    Serial.println(ldrstatus);
  }
}