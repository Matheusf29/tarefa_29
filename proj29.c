// Incluindo as bibliotecas
#include <stdio.h>
#include "pico/stdlib.h" 
#include "hardware/timer.h" 
#include "hardware/pio.h"

//Declarando os pinos
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

    typedef enum    {
    RED,
    YELLOW, 
    GREEN
    } EstadoSemaforo;

    EstadoSemaforo estado_atual = RED;

    // Estrutura de temporizador de repetição.
    struct repeating_timer timer;

    // Função de callback que será chamada repetidamente pelo temporizador
    bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDS antes de mudar para o próximo estado
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN,0);

    //Muda o estado do semáforo
    switch (estado_atual) {
        case RED:
            estado_atual = YELLOW;
            gpio_put(LED_YELLOW, 1);
            break;
        case YELLOW:
            estado_atual = GREEN;
            gpio_put(LED_GREEN, 1);
            break;
        case GREEN:
            estado_atual = RED;
            gpio_put(LED_RED, 1);
            break;

    }
    
    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}

    void iniciar_leds(){
        // Inicializar os pinos
        gpio_init(LED_RED);
        gpio_set_dir(LED_RED, GPIO_OUT);
        gpio_init(LED_YELLOW);
        gpio_set_dir(LED_YELLOW, GPIO_OUT);
        gpio_init(LED_GREEN);
        gpio_set_dir(LED_GREEN, GPIO_OUT);
        //Inicializar o semáforo com LED vermelho on
        gpio_put(LED_RED, 1);
    }

    void mensagem(){
        printf("ATENCAO AO SEMAFORO!\n");
        sleep_ms(1000);
}

int main() {
    // Inicializando
    stdio_init_all();
    iniciar_leds();

    // Temporizador para chamar a função de callback a cada 3 segundos.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito com a mensagem a ser exibida a cada  segundo.
    while (true) {
        mensagem();
    }
    return 0;
}
