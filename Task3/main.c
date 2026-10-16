#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED0 1
#define LED1 2
#define LED2 3
#define LED3 4

#define RESET_BTN 0

volatile int counter = 0;

int64_t timer_callback(alarm_id_t id, void *unused) // rückgabe wert ist int64_t id kennung des Alarms
{
    if (counter < 15)
    {
        counter = counter + 1;
    }

    
    return 1000 * 1000; // nochmal in 1 sek aufrufen
}

// Taster-Interrupt: Zähler zurücksetzen
void gpio_callback(uint gpio, uint32_t events) // gpio enthält welcher pin das auslöst
{
    if (gpio == RESET_BTN) // wen reset gedrückt 
    {
        counter = 0; // setze zurück 
    }
}

int main(void)
{
    // LEDs vorbereiten
    gpio_init(LED0);
    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);

    gpio_set_dir(LED0, GPIO_OUT);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);

    gpio_put(LED0, 0);
    gpio_put(LED1, 0);
    gpio_put(LED2, 0);
    gpio_put(LED3, 0);

    gpio_init(RESET_BTN);
    gpio_set_dir(RESET_BTN, GPIO_IN);
    gpio_pull_up(RESET_BTN);

    gpio_set_irq_enabled_with_callback( // interrupt initalisieren
        RESET_BTN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &gpio_callback
    );

    add_alarm_in_ms(1000, timer_callback, NULL, true); //Alrm nach 1000 ms, welche function, keine daten Übergeben,

    while (true)
    {

        gpio_put(LED0, (counter & 0x01));
        gpio_put(LED1, (counter & 0x02) >> 1);
        gpio_put(LED2, (counter & 0x04) >> 2);
        gpio_put(LED3, (counter & 0x08) >> 3);
    }
}