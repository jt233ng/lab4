#include "pico/stdlib.h"

#define LED0 1
#define LED1 2
#define LED2 3
#define LED3 4

#define UP_BTN   5
#define DOWN_BTN 6

volatile int counter = 0; // volatile weil es sich außerhalb der Hauptschleife veraedern kann

// Wird durch einen Taster-Interrupt aufgerufen
void gpio_callback(uint gpio, uint32_t events) //gpio which Pin the interrupt activate, events what its aktivate
{
    if (gpio == UP_BTN && counter < 15) //wen ausgelöst und unter den werten counter erhoehen
    {
        counter = counter + 1;
    }
    else if (gpio == DOWN_BTN && counter > 0)
    {
        counter = counter - 1;
    }
}

int main(void)
{
    gpio_init(LED0);
    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);

    gpio_set_dir(LED0, GPIO_OUT);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);

    gpio_init(UP_BTN);
    gpio_set_dir(UP_BTN, GPIO_IN);
    gpio_pull_up(UP_BTN);

    gpio_init(DOWN_BTN);
    gpio_set_dir(DOWN_BTN, GPIO_IN);
    gpio_pull_up(DOWN_BTN);

    gpio_set_irq_enabled_with_callback( // initalisiertTaster Interrupt und legt fest was überwacht werden soll und so
        UP_BTN,
        GPIO_IRQ_EDGE_FALL, // Fallende flanke
        true,
        &gpio_callback // adresse der funktion
    );

    gpio_set_irq_enabled_with_callback(
        DOWN_BTN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &gpio_callback
    );

    while (true)
    {
        gpio_put(LED0, (counter & 0x01)); // Bitmuster über und nur erste Nummer behalten
        gpio_put(LED1, (counter & 0x02) >> 1); // das >> nach rechts shiften soll ja Led 1 anmachen 
        gpio_put(LED2, (counter & 0x04) >> 2); // von 100 zu 1
        gpio_put(LED3, (counter & 0x08) >> 3); // nicht unbedingt nötig glaub ich >>
    }
}