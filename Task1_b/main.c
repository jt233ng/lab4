#include "pico/stdlib.h"

#define LED_PIN     0
#define BUTTON_ON   1
#define BUTTON_OFF  2

int main(void)
{
    volatile uint32_t *SIO =
        (volatile uint32_t *)0xD0000000; // Basisadresse

    gpio_init(LED_PIN);
    *(SIO + 0x018 / 4) = 1ul << LED_PIN; //pointer to GPIO_OUT_claer
    gpio_set_dir(LED_PIN, GPIO_OUT);	 //ul unsigned mit 1 << shiften zu der richten zahl

    gpio_init(BUTTON_ON);
    *(SIO + 0x018 / 4) = 1ul << LED_PIN; // macht LED aus
    gpio_pull_up(BUTTON_ON);

    gpio_init(BUTTON_OFF);
    gpio_set_dir(BUTTON_OFF, GPIO_IN);
    gpio_pull_up(BUTTON_OFF);

    while (true)
    {
        
        uint32_t inputs = *(SIO + 0x004 / 4); //Hat alle inputs vom rasperybi gespeichert
											  // wie viele bit man weiter gehen soll durch /4
        if ((inputs & (1ul << BUTTON_ON)) == 0)// nimmt die inputs hat eine Bitmaske drüber und schaut ob das gleich ist 
        {// Da durch BUTTON_ON wird nur der Button_on angescahut 
            *(SIO + 0x014 / 4) = 1ul << LED_PIN; //14 gleichbedeutend mit GPIO_OUT_SET
        }

        if ((inputs & (1ul << BUTTON_OFF)) == 0)
        {
            // GPIO_OUT_CLR: LED ausschalten
            *(SIO + 0x018 / 4) = 1ul << LED_PIN; //18 null setzen
        }
    }
}