# 🏭 Sistema de Telemetria para Ensaios de Motores Elétricos

![Status](https://img.shields.io/badge/STATUS-FINALIZADO-brightgreen?style=for-the-badge)
![Language C++](https://img.shields.io/badge/C%2B%2B-54%25-blue?style=for-the-badge&logo=c%2B%2B)
![Language Java](https://img.shields.io/badge/Java-46%25-orange?style=for-the-badge&logo=java)
![Protocol MQTT](https://img.shields.io/badge/Protocolo-MQTT-important?style=for-the-badge&logo=mqtt)

## 📖 Sobre o Projeto
Este projeto foi desenvolvido como parte da Avaliação Prática do curso Técnico em **CiberSistemas** do **SENAI/SC**. 

O objetivo foi modernizar o processo de ensaios de qualidade de motores elétricos, substituindo anotações manuais por um sistema de coleta automática de dados. [cite_start]O protótipo utiliza um **ESP32** para capturar métricas de sensores e enviá-las via protocolo **MQTT** para uma aplicação backend em **Java**, que registra o sucesso da operação[cite: 823, 824, 828].

## ⚙️ Funcionalidades
* [cite_start]**Coleta de Dados:** Leitura de temperatura, simulação de vibração e corrente elétrica[cite: 830].
* **Conectividade IoT:** Transmissão de dados via Wi-Fi utilizando protocolo MQTT.
* **Monitoramento Remoto:** Recepção e exibição de logs de telemetria em uma aplicação Java (Console).
* **Interface Local:** Exibição de status em Display LCD 16x2.

## 🛠️ Tecnologias e Ferramentas

### Hardware (Simulado no Wokwi)
| Componente | Função | Pino (GPIO) |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | Microcontrolador Principal | - |
| **DHT22** | Sensor de Temperatura | [cite_start]D15 [cite: 438] |
| **Potenciômetro 1** | Simulação de Vibração | [cite_start]D34 [cite: 439] |
| **Potenciômetro 2** | Simulação de Corrente | [cite_start]D35 [cite: 440] |
| **LCD 16x2 (I2C)** | Display de Status Local | [cite_start]SDA: D21 / SCL: D22 [cite: 441] |
| **LED Verde** | Indicador de Status | [cite_start]D12 [cite: 442] |

### Software & Bibliotecas
* **Firmware (C++):**
    * `<WiFi.h>`: Conexão de rede.
    * `<PubSubClient.h>`: Cliente MQTT.
    * `<DHT.h>`: Leitura do sensor de temperatura.
    * `<LiquidCrystal_I2C.h>`: Controle do display.
* **Backend (Java):**
    * **Maven:** Gerenciamento de dependências.
    * [cite_start]**Eclipse Paho MQTT:** Biblioteca cliente para comunicação[cite: 741].
    * **IDE:** IntelliJ IDEA / VS Code.

## 📡 Configuração MQTT
O sistema utiliza um broker público para comunicação:

* [cite_start]**Broker:** `broker.hivemq.com` [cite: 444]
* [cite_start]**Porta:** `1883` [cite: 445]
* [cite_start]**Tópico de Publicação:** `senai/seu_nome/motor/dados` [cite: 446]

## 🚀 Como Executar

### 1. Firmware (ESP32)
1.  Acesse o simulador [Wokwi](https://wokwi.com/).
2.  Carregue o arquivo `diagram.json` e o código fonte `.ino` / `.cpp`.
3.  Instale as bibliotecas necessárias no gerenciador de bibliotecas.
4.  Inicie a simulação.

### 2. Backend (Java)
1.  Abra o projeto na sua IDE de preferência (VS Code ou IntelliJ).
2.  Certifique-se de que o **Maven** baixou as dependências do `pom.xml`.
3.  Execute a classe `App.java` (ou `Main.java`).
4.  [cite_start]O console exibirá: *"Dados de Telemetria Coletados com Sucesso: [DADOS]"*[cite: 832].

## 👨‍💻 Autor
**Mateus Cavalheiro** Curso Técnico em CiberSistemas - SENAI/SC
**E-mail** mateusdossantoscavalheiro@gmail.com
[cite_start]*Unidade Curricular: Programação para Coleta de Dados em Automação* *Docente: Lucas Sousa dos Santos* [cite: 797]

---
*Projeto desenvolvido para fins educacionais - 2026.*
