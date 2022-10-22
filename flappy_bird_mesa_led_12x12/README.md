## Tarefa 2 da disciplina INF351

### Projeto: Flappy Bird em mesa de led 12x12

O código foi testado em simulador de mesa de LED previamente fornecido:
- [Código fonte](https://github.com/arduinoufv/inf351/blob/master/2022/Tarefa2/Simulador_Arthur_mesa.zip)
- [Instruções de uso](https://github.com/cacauvicosa/inf351_2019/tree/master/trabalhos/t3/Arthur/simulador)

O simulador denpende da biblioteca *freeglut3-dev*. Para instalar no Linux:

```bash
sudo apt-get update
sudo apt-get install freeglut3-dev
```
Para executar o este projeto (após instalação da biblioteca *freeglut3-dev*), basta executar os seguintes comandos (no Linux):
```bash
# Para compilar o programa (apenas uma vez)
./comp.sh flappy_bird.cpp flappy
# Para executar o programa
./flappy
```

Para iniciar o jogo após o comando *./flappy* e jogar, pressione a tecla **W**