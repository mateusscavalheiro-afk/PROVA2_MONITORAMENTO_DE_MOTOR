package br.com.senai.automacao;

//Importação das bibliotecas
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.UUID;

@SuppressWarnings("all")

public class MonitoramentoMotor {

    public static void main(String[] args) {
        // CONFIGURAÇÕES
        String broker = "tcp://broker.hivemq.com:1883";
        String topico = "senai/MATEUS/motor/dados"; // O MESMO DO C++
        String clientId = "Java_Monitor_" + UUID.randomUUID().toString();

        try {
            // 1. Criar o cliente MQTT
            MqttClient client = new MqttClient(broker, clientId);
            MqttConnectOptions options = new MqttConnectOptions();
            options.setCleanSession(true);

            // 2. Definir o que acontece quando chega uma mensagem (Callback)
            client.setCallback(new MqttCallback() {

                @Override
                public void connectionLost(Throwable cause) {
                    System.out.println("Conexão perdida! Causa: " + cause.getMessage());
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) throws Exception {

                    String payload = new String(message.getPayload());

                    // O C++ envia: "25.0,12,30" (Exemplo)
                    // Vamos separar pela vírgula
                    String[] dados = payload.split(",");

                    if (dados.length >= 3) {
                        System.out.println("--------------------------------------------------");
                        System.out.println("Dados de Telemetria Coletados com Sucesso:");
                        System.out.println("Temperatura: " + dados[0] + " °C");
                        System.out.println("Vibração:    " + dados[1] + " %");
                        System.out.println("Corrente:    " + dados[2] + " A");

                        // Validação Extra para o Relatório (Segurança)
                        double vib = Double.parseDouble(dados[1]);
                        if (vib > 45) {
                            System.err.println("[ALERTA CRÍTICO] PERIGO DE VIBRAÇÃO EXCESSIVA!");
                        }
                    }
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    // Não usado pois só estamos recebendo
                }
            });

            // 3. Conectar e Assinar
            System.out.println("Conectando ao broker: " + broker);
            client.connect(options);
            System.out.println("Conectado! Assinando tópico: " + topico);
            client.subscribe(topico);

            System.out.println("Aguardando dados do ESP32...");

        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
}