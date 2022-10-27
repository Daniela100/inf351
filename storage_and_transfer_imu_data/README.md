# Armazenamento dos dados IMU
### Utilizar o código na pasta *storage_imu*
Possui código que coleta e armazena os dados do IMU utilizando o M5StickC.

Por padrão, os dados do IMU serão coletados durante 1 minuto em intervalos de 500 milisegundos. Para alterar o tempo de coleta, basta alterar o valor na variável *RECORD_TIME* considerando minutos. Para alterar o intervalo de coleta, altere a variável *GAP*.

Os arquivos serão armazenados com nome *n.txt*, com n=0,1,2,...

Após upar o código *storage_imu.ino*, basta apertar o botão home do M5StickC. O início da gravação dos dados da IMU serão indicados por sinal vermelho no display.

# Transfências do arquivos utilizando Serial
### Utilizar os códigos na pasta *send_files_serial*
Possui código referente para a transferência dos arquivos da IMU gravados no M5StickC para o computador atráves utilizando Serial (usb).
Para realizar a transferência:

1. Upar o código "send_files_serial.ino" para o M5StickC
2. Executar o código *serial_port.py*
    - python serial_port.py
    - O código foi testado na versão 3.10.6 do python
    - Utiliza a biblioteca pyserial que pode ser instalada com o comando *pip install pyserial*
    - Antes de executar o código, altere o caminho absoluto na variável *ROOT* para a pasta que desejar
3. Para iniciar a transferência, aperte e solte o botão home do M5StickC

<span style="color: red">Importante: *serial_port.py* deve ser executado antes de iniciar a transferência</span>

# Transfências do arquivos utilizando conexão WiFi
Em desenvolvimento
