/**
 * Autor: Gilglecio Santos
 */

/**
 * Bibliotecas
 */
#include <Servo.h>

/**
 * Constantes
 */
#define servoPinGarra 10
#define servoPinPunhoRotate 9
#define servoPinPunho 8
#define servoPinCotovelo 7
#define servoPinOmbro 6
#define servoPinBase 12

/**
 * Armazena a posição atual dos servos
 */
int positions[] = {90,90,90,90,90,90};

/**
 * Atribuição de objetos (servos do braço)
 */
Servo svBase, svOmbro, svCotovelo, svPunho, svPunhoRotate, svGarra;

/**
 * Use para mover os servos
 */
void move(int base, int ombro, int cotovelo, int punho, int punhoRotate, int garra);

/**
 * Suaviza os movimentos do servo, atraves do parametro tempo.
 * Quanto menor o tempo mais rápido será o movimento.
 */
void suave(int index, Servo servo, int tempo, int posicao);

/**
 * Setup
 */
void setup()
{
    /**
     * Define os pinos como saída
     */
    pinMode(servoPinGarra, OUTPUT);
    pinMode(servoPinPunhoRotate, OUTPUT);
    pinMode(servoPinPunho, OUTPUT);
    pinMode(servoPinCotovelo, OUTPUT);
    pinMode(servoPinOmbro, OUTPUT);
    pinMode(servoPinBase, OUTPUT);
  
    /**
     * Seta o pin para cada objeto
     */
    svGarra.attach(servoPinGarra);
    svPunhoRotate.attach(servoPinPunhoRotate);
    svPunho.attach(servoPinPunho);
    svCotovelo.attach(servoPinCotovelo);
    svOmbro.attach(servoPinOmbro);
    svBase.attach(servoPinBase);

    /**
     * Posicionamento inicial
     */
    svBase.write(positions[0]);
    svOmbro.write(positions[1]);
    svCotovelo.write(positions[2]);
    svPunho.write(positions[3]);
    svPunhoRotate.write(positions[4]);
    svGarra.write(positions[5]);

    /**
     * esera para iniciar
     */
    delay(3000);
}

/**
 * Loop
 */
void loop()
{
    move(150, 150, 150, 150, 150, 150);
    delay(1000);
    
    move(90, 10, 30, 110, 50, 150);
    delay(1000);
  
    move(20, 100, 180, 50, 10, 30);
    delay(1000);
}

/**
 * Use para mover os servos
 */
void move(int base, int ombro, int cotovelo, int punho, int punhoRotate, int garra)
{
    int tempo = 5;

    suave(0, svBase, tempo, base);
    suave(1, svOmbro, tempo, ombro);
    suave(2, svCotovelo, tempo, cotovelo);
    suave(3, svPunho, tempo, punho);
    suave(4, svPunhoRotate, tempo, punhoRotate);
    suave(5, svGarra, tempo, garra);
}

/**
 * Suaviza os movimentos do servo, atraves do parametro tempo.
 * Quanto menor o tempo mais rápido será o movimento.
 */
void suave(int index, Servo servo, int tempo, int posicao)
{
    int posicao_atual = positions[index];

    /**
     * Se o destino for maior que a posição atual do servo
     * devemos incremetar o grau, até atingir a posição
     */
    if (posicao > posicao_atual){
        
        for(int i = posicao_atual; i <= posicao; i++) {
            servo.write(i);
            delay(tempo);
        }
    }

    /**
     * Se o destino for menor que a posição atual do servo
     * devemos decrementar o grau, até atingir a posição
     */
    else if (posicao < posicao_atual) {

        for(int i = posicao_atual; i >= posicao; i--) {
            servo.write(i);
            delay(tempo);
        }
    }

    /**
     * Atualiza a posição atual do servo
     */
    positions[index] = posicao;
}