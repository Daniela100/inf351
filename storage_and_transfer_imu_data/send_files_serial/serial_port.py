import os
import serial

def serial_connect():
    print_once = False
    count = 0
    while count <= 10000:
        try:
            arduino = serial.Serial('/dev/ttyUSB0', 9600)
            print('Arduino conectado')
            return arduino

        except:
            count += 1
            if not print_once:
                print("Falha ao conectar Serial")
                print_once = True
    exit()


ROOT = '/home/daniela/Documentos/embarcados/storage_and_transfer_imu_data'

if ROOT.startswith('/path/to'):
    print('Altere o caminho indicado pela variável ROOT')
    exit()

folder = f'{ROOT}/imu_data'

if not os.path.exists(folder):
    print('Criando pasta para armazenar os dados transferidos:')
    print(folder)
    os.mkdir(folder)

print('Conectando Serial ...')
arduino = serial_connect()

file = ''
files_names = []
# arduino.flush()
while True:
    msg = str(arduino.readline())
    # print(msg)
    msg = msg[2:-5]
    print(msg)
    # msg = msg.decode()

    if msg.startswith('f'):
        file_name = msg.split(',')
        file_name = file_name[1]
        
        file_path = f'{folder}/{file_name}'
        print("Salvando arquivo em: ", file_path)
        file = open(file_path, 'w')
        files_names.append(file_name)
    
    elif msg == 'END':
        print("Todos os arquivos foram transferidos")
        break

    elif len(msg) > 0:
        file.write(msg)

    arduino.flush()

# Tratando arquivos recebidos
for fn in files_names:
    file = open(f'{folder}/{fn}')
    line = file.read()
    file.close()
    lines = line.split('?')
    file = open(f'{folder}/{fn}', 'w')

    for l in lines:
        file.write(f'{l}\n')

    file.close()
