# 🏭 Sistema de Telemetria para Ensaios de Motores Elétricos

> **By Mateus Cavalheiro**  
> 🔗 [Meu Portifólio](https://mateusdossantoscavalheiro-sudo.github.io/Portifolio/)

![Status](https://img.shields.io/badge/STATUS-FINALIZADO-brightgreen?style=for-the-badge)
![Language C++](https://img.shields.io/badge/C%2B%2B-54%25-blue?style=for-the-badge&logo=c%2B%2B)
![Language Java](https://img.shields.io/badge/Java-46%25-orange?style=for-the-badge&logo=java)
![Protocol MQTT](https://img.shields.io/badge/Protocolo-MQTT-important?style=for-the-badge&logo=mqtt)

## 📖 Sobre o Projeto
Este projeto foi desenvolvido como parte da Avaliação Prática do curso Técnico em **CiberSistemas** do **SENAI/SC**. 

O objetivo foi modernizar o processo de ensaios de qualidade de motores elétricos, substituindo anotações manuais por um sistema de coleta automática de dados. O protótipo utiliza um **ESP32** para capturar métricas de sensores e enviá-las via protocolo **MQTT** para uma aplicação backend em **Java**, que registra o sucesso da operação.

## ⚙️ Funcionalidades
* **Coleta de Dados:** Leitura de temperatura, simulação de vibração e corrente elétrica.
* **Conectividade IoT:** Transmissão de dados via Wi-Fi utilizando protocolo MQTT.
* **Monitoramento Remoto:** Recepção e exibição de logs de telemetria em uma aplicação Java (Console).
* **Interface Local:** Exibição de status em Display LCD 16x2.

## 🛠️ Tecnologias e Ferramentas

### Hardware (Simulado no Wokwi)
| Componente | Função | Pino (GPIO) |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | Microcontrolador Principal | - |
| **DHT22** | Sensor de Temperatura | D15 |
| **Potenciômetro 1** | Simulação de Vibração | D34 |
| **Potenciômetro 2** | Simulação de Corrente | D35 |
| **LCD 16x2 (I2C)** | Display de Status Local | SDA: D21 / SCL: D22 |
| **LED Verde, Amarelo e Vermelho** | Indicador de Status | D12, 14 e 27 |

### Software & Bibliotecas
* **Firmware (C++):**
    * `<WiFi.h>`: Conexão de rede.
    * `<PubSubClient.h>`: Cliente MQTT.
    * `<DHT.h>`: Leitura do sensor de temperatura.
    * `<LiquidCrystal_I2C.h>`: Controle do display.
* **Backend (Java):**
    * **Maven:** Gerenciamento de dependências.
    * **Eclipse Paho MQTT:** Biblioteca cliente para comunicação.
    * **IDE:** IntelliJ IDEA / VS Code.

## 📡 Configuração MQTT
O sistema utiliza um broker público para comunicação:

* **Broker:** `broker.hivemq.com`
* **Porta:** `1883`
* **Tópico de Publicação:** `senai/seu_nome/motor/dados`

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
4.  O console exibirá os dados enviados pelo ESP32.

## 👨‍💻 Autor

**Mateus dos Santos Cavalheiro** Curso Técnico em CiberSistemas  
🏢 **WEG S.A. & SENAI - JARAGUÁ DO SUL** 📧 E-mail: mateusdossantoscavalheiro@gmail.com

*Unidade Curricular: Programação para Coleta de Dados em Automação* *Docente: Lucas Sousa dos Santos*

---
*Projeto desenvolvido para fins educacionais - 2026.*
