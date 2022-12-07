# M5StickC - IMU (Unidade de Medição Inercial)
- O M5StickC possui módulo para obter dados de giroscópio, acelerômetro e eixos de controle de aeronave (roll, pitch e yaw)
- Um código de exemplo básico está disponível em *imu/imu.ino*
- Um código de exemplo para armazenar os dados coletados no M5StickC está disponível em *storage_imu/storage_imu.ino*
- Um código de exemplo para transferir os dados armezados no M5StickC para o computador utilizando Serial está disponível em *transfer_imu_serial/tarnsfer_imu_serial.ino*
- Um código de exemplo para transferir os dados *em tempo real* do M5StickC para o computador utilizando MQTT está disponível em *transfer_imu_mqtt/tarnsfer_imu_mqtt.ino*

## Utilizando o módulo IMU
- Para utilizar o IMU do M5StickC, a unidade deve ser iniciada com <code>M5.IMU.Init()</code>
- Obtendo dados do acelerômetro: função <code>void getAccelData(float *ax, float *ay, float *az)</code>
```
float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

M5.IMU.getAccelData(&accX, &accY, &accZ);
```
- Obtendo dados do giroscópio: função <code>void getGyroData(float *gx, float *gy, float *gz)</code>
```
float gyroX = 0.0f;
float gyroY = 0.0f;
float gyroZ = 0.0f;

M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
```
- Obtendo dados de eixos de controle de aeronave: função <code>void getAhrsData(float *pitch, float *roll, float *yaw)</code>
```
float pitch = 0.0f;
float roll = 0.0f;
float yaw = 0.0f;

M5.IMU.getGyroData(&pitch, &roll, &yaw);
```

## Utilizar o código na pasta *storage_imu/storage_imu.ino*
Possui código que coleta e armazena os dados do IMU utilizando o M5StickC.

Por padrão, os dados do IMU serão coletados durante 1 minuto em intervalos de 500 milisegundos. Para alterar o tempo de coleta, basta alterar o valor na variável *RECORD_TIME* considerando minutos. Para alterar o intervalo de coleta, altere a variável *GAP*.

Os arquivos serão armazenados com nome *n.txt*, com n=0,1,2,...

Após upar o código *storage_imu.ino*, basta apertar o botão home do M5StickC. O início da gravação dos dados da IMU serão indicados por sinal vermelho no display.

## Utilizar os códigos na pasta *transfer_imu_serial*
Possui código referente para a transferência dos arquivos da IMU gravados no M5StickC para o computador atráves utilizando Serial (usb).
Para realizar a transferência:

1. *Upar* o código "send_files_serial.ino" para o M5StickC
2. Executar o código *serial_port.py*
    - python serial_port.py
    - O código foi testado na versão 3.10.6 de Python
    - Utiliza a biblioteca pyserial que pode ser instalada com o comando *pip install pyserial*
    - Antes de executar o código, altere o caminho absoluto na variável *ROOT* para a pasta que desejar
3. Para iniciar a transferência, aperte e solte o botão *home* do M5StickC

<span style="color: red">Importante: *serial_port.py* deve ser executado antes de iniciar a transferência</span>

## Utilizar os códigos na pasta *transfer_mqtt*
1. Configurar a rede WiFi no código *transfer_mqtt.ino*
    - Linha 14: nome da rede
    - Linha 15: senha da rede
2. *Upar* o código *transfer_mqtt.ino* com as alterações necessárias para o M5StickC
3. Após a conexão com o Broker pelo M5StickC, execute o código *mqttClient.py* e a transferência irá iniciar automaticamente
    - python mqttClient.py
    - O código foi testado na versão 3.10.6 de Python
    - Utiliza a biblioteca paho-mqtt que pode ser instalada com o comando *pip install paho-mqtt*



## Referências
- https://docs.m5stack.com/en/api/stickc/imu
- https://github.com/m5stack/M5StickC/blob/master/examples/Basics/IMU/IMU.ino
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/MQTT/MQTT.ino
- https://www.emqx.com/en/blog/how-to-use-mqtt-in-python
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/Storage/SPIFFS/SPIFFS/SPIFFS.ino
- https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/Storage/Counter/Counter.ino