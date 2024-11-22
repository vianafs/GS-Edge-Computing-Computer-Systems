# GS-Edge-Computing-Computer-Systems
<h2>Integrantes</h2>
<h3>Rafael Menezes Viana RM558287</h3>
<h3>Kairo da Silva Silvestre de Carvalho RM558288</h3>
<h2>Descrição do Projeto</h2>
<p>Este projeto foi desenvolvido para demonstrar a utilização de IoT com ESP32 em um sistema voltado para monitoramento e controle de uma placa solar simulada. Os principais objetivos são:</p>
<ol>
  <li>Monitorar dados como luminosidade, consumo de corrente, potência gerada e estado do sistema.</li>
  <li>Controlar remotamente dispositivos (atuadores) via protocolo MQTT.</li>
</ol>
<p>Os componentes simulam o comportamento de um sistema de energia renovável e demonstram como podemos usar a tecnologia IoT para tornar o monitoramento mais eficiente.</p>
<h2>Características</h2>
<ol>
  <li>Sensores</li>
  <ul>
    <li>LDR: Mede a intensidade de luz.</li>
    <li>Potenciômetro: Simula a corrente gerada pela placa solar.</li>
  </ul>
  <li>Atuadores</li>
    <ul>
      <li>LED: Representa uma carga controlada remotamente via MQTT.</li>
    </ul>
  <li>Protocolo de Comunicação</li>
    <ul>
      <li>MQTT:</li>
      <li>Tópico de envio (publish): meu_projeto/monitoramento.</li>
      <li>Tópico de controle (subscribe): meu_projeto/controle.</li>
    </ul>
  <li>Exibição dos Dados</li>
  <ul>
    <li>Display LCD I2C: Apresenta as informações em tempo real, incluindo corrente, potência, luminosidade e estado do LED.</li>
  </ul>
  <li>Plataforma</li>
  <ul><li>Simulação feita no Wokwi ou hardware real ESP32.</li></ul>
</ol>
<h2>Requisitos</h2>
<h3>Hardware</h3>
<ul>
  <li>ESP32.</li>
  <li>LED + Resistor (220Ω ou 330Ω).</li>
  <li>LDR com divisor resistivo.</li>
  <li>Display LCD com interface I2C.</li>
</ul>
<h3>Software</h3>
<ul>
  <li>Arduino IDE 1.8 ou superior.</li>
  <li>Bibliotecas necessárias:</li>
  <li>WiFi.h (inclusa no ESP32 core).</li>
  <li>PubSubClient (instale pelo Gerenciador de Bibliotecas).</li>
  <li>LiquidCrystal_I2C (instale pelo Gerenciador de Bibliotecas).</li>
</ul>
<h2>Configuração do Hardware</h2>
<ol>
  <li>LDR</li>
  <ul>
    <li>Um terminal conectado ao pino 35 (A2) do ESP32.</li>
    <li>Outro terminal ao GND, com um resistor de pull-down (10kΩ).</li>
  </ul>
  <li>Potenciômetro</li>
    <ul>
      <li>Terminal central conectado ao pino 34 (A1) do ESP32.</li>
      <li>Terminais laterais ao GND e 3.3V.</li>
    </ul>
  <li>LED</li>
    <ul>
      <li>Anodo (perna longa) ao pino 26 (D26).</li>
      <li>Catodo ao GND com um resistor de 220Ω.</li>
    </ul>

  <li>LCD I2C</li>
    <ul>
      <li>Conecte os pinos SDA e SCL ao ESP32:</li>
      <li>SDA: Pino 21.</li>
      <li>SCL: Pino 22.</li>
    </ul>
</ol>
<h2>Configuração do MQTT</h2>
<ol>
  <li>Utilize um broker público como o HiveMQ ou outro de sua preferência:</li>
  <ul>
    <li>Endereço do broker: broker.hivemq.com.</li>
    <li>Porta: 1883.</li>
  </ul>
  <li>Altere no código os valores:</li>
  
```bash
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

```
</ol>
<h2>Instruções de Uso</h2>
<ol>
  <li>Conexão do Hardware</li>
  <ul>
    <li>Monte os sensores e atuadores conforme o esquema descrito.</li>
  </ul>
  <li>Configuração do Ambiente</li>
    <ul>
    <li>Instale as bibliotecas necessárias no Arduino IDE.</li>
    <li>Configure o Wi-Fi no código:</li>
      
```bash
const char* ssid = "Seu_SSID";
const char* password = "Sua_Senha";

```
  </ul>
  <li>Envio de Comandos MQTT</li>
    <ul>
    <li>Para ligar o LED, publique ON no tópico meu_projeto/controle.</li>
    <li>Para desligar o LED, publique OFF.</li>
  </ul>
  <li>Monitoramento</li>
    <ul>
    <li>As medições de luminosidade, corrente, potência e estado do LED são publicadas automaticamente no tópico meu_projeto/monitoramento.</li>
  </ul>
</ol>
<h2>Exemplo de Publicação e Monitoramento</h2>
<ol>
  <li>Exemplo de Publicação</li>
  <ul>
    <li>Comando para ligar o LED:</li>
    
```bash
Tópico: meu_projeto/controle  
Mensagem: ON

```   
  </ul>  
  <li>Exemplo de Monitoramento</li>
  <ul>
    <li>Mensagem publicada automaticamente pelo ESP32:</li>

```bash
Tópico: meu_projeto/monitoramento  
Mensagem: Corrente: 1.23A, Potência: 6.15W, Luz: 87.5%, LED: ON

``` 
  </ul>
</ol>
<h2>Estrutura do Projeto</h2>

```plaintext
ProjetoIoT/
├── README.md
├── src/
│   ├── projetoIoT.ino
│   └── bibliotecas/
│       ├── PubSubClient/
│       └── LiquidCrystal_I2C/
├── esquemas/
│   ├── esquema_conexao.png
└── exemplos_mqtt/
    ├── comandos_mqtt.txt

```
<h2>Considerações Finais</h2>
<p>Este projeto demonstra uma aplicação prática de IoT em energia renovável. A integração do ESP32 com sensores, atuadores e MQTT torna o sistema versátil para monitoramento e controle remoto. Ideal para aprendizado e desenvolvimento de soluções em IoT para um futuro mais sustentável.</p>













