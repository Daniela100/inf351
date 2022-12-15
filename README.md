# Repositório para projetos da disciplina INF351 - Sistemas embarcados

## M5StickC - IMU (Unidade de Medição Inercial)
- O M5StickC possui módulo para obter dados de giroscópio, acelerômetro e eixos de controle de aeronave (roll, pitch e yaw)
- Um código de exemplo básico está disponível em *imu/imu.ino*
- Um código de exemplo para armazenar os dados coletados no M5StickC está disponível em *storage_imu/storage_imu.ino*
- Um código de exemplo para transferir os dados armezados no M5StickC para o computador utilizando Serial está disponível em *transfer_imu_serial/tarnsfer_imu_serial.ino*
- Um código de exemplo para transferir os dados *em tempo real* do M5StickC para o computador utilizando MQTT está disponível em *transfer_imu_mqtt/tarnsfer_imu_mqtt.ino*

## Referências
- https://docs.m5stack.com/en/api/stickc/imu
- https://github.com/m5stack/M5StickC/blob/master/examples/Basics/IMU/IMU.ino
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/MQTT/MQTT.ino
- https://www.emqx.com/en/blog/how-to-use-mqtt-in-python
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/Storage/SPIFFS/SPIFFS/SPIFFS.ino
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/Storage/Counter/Counter.ino
