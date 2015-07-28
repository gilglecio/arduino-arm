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
void suave(int index, Servo servo, int posicao, int delay_min, int delay_max);

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
    /**
     * Quando maior a diferença entre eles, mais ingrime será a parábola
     */
    int delay_min = 1;
    int delay_max = 2;

    suave(0, svBase, base, delay_min, delay_max);
    suave(1, svOmbro, ombro, delay_min, delay_max);
    suave(2, svCotovelo, cotovelo, delay_min, delay_max);
    suave(3, svPunho, punho, delay_min, delay_max);
    suave(4, svPunhoRotate, punhoRotate, delay_min, delay_max);
    suave(5, svGarra, garra, delay_min, delay_max);
}

/**
 * Suaviza os movimentos do servo, atraves do parametro tempo.
 * Quanto menor o tempo mais rápido será o movimento.
 */
void suave(int index, Servo servo, int posicao, int delay_min, int delay_max)
{
    /**
     * Pega a posição atual do servo
     */
    int posicao_atual = positions[index];

    /**
     * Armazena a diferença entre os tempos
     */
    int diferenca_tempo = delay_max - delay_min;

    /**
     * O tempo será iniciado com o delay_max
     */
    int tempo = delay_max;

    /**
     * Se o destino for maior que a posição atual do servo
     * devemos incremetar o grau, até atingir a posição
     */
    if (posicao > posicao_atual) {

        /**
         * Armazena o valor correspondente a diferença da posição desejada
         * em relação a posição atual, e este valor é didido por dois
         * isso define a curva de acerelação em parábola.
         */
        int metade_diferenca = (posicao - posicao_atual) / 2;

        /**
         * Este valor será usado para incremendo ou decremento do tempo,
         * gerando a parábola desejada
         */
        int tempo_proporcional = diferenca_tempo / metade_diferenca;
        
        int j = 0;

        for(int i = posicao_atual; i <= posicao; i++) {

            servo.write(i);

            /**
             * Aqui ocorre a aceleração
             */
            if (j <= metade_diferenca) {
                tempo -= tempo_proporcional;
            }

            /**
             * Aqui a desaceleração
             */
            if (j > metade_diferenca) {
                tempo += tempo_proporcional;
            }

            j++;

            delay(tempo);
        }
    }

    /**
     * Se o destino for menor que a posição atual do servo
     * devemos decrementar o grau, até atingir a posição
     */
    else if (posicao < posicao_atual) {

        /**
         * Armazena o valor correspondente a diferença da posição desejada
         * em relação a posição atual, e este valor é didido por dois
         * isso define a curva de acerelação em parábola.
         */
        int metade_diferenca = (posicao_atual - posicao) / 2;

        /**
         * Este valor será usado para incremendo ou decremento do tempo,
         * gerando a parábola desejada
         */
        int tempo_proporcional = diferenca_tempo / metade_diferenca;

        int j = 0;

        for(int i = posicao_atual; i >= posicao; i--) {

            servo.write(i);

            /**
             * Aqui ocorre a aceleração
             */
            if (j <= metade_diferenca) {
                tempo -= tempo_proporcional;
            }

            /**
             * Aqui a desaceleração
             */
            if (j > metade_diferenca) {
                tempo += tempo_proporcional;
            }

            j++;

            delay(tempo);
        }
    }

    /**
     * Atualiza a posição atual do servo
     */
    positions[index] = posicao;
}