#include "pico/stdlib.h"

#define LED_PIN1    0
#define BUTTON_ON   1
#define BUTTON_OFF  2
#define LED_PIN6    6

int main(void)
{
    volatile uint32_t *SIO =
        (volatile uint32_t *)0xD0000000; // Basisadresse

    gpio_init(LED_PIN1);
    *(SIO + 0x018 / 4) = 1ul << LED_PIN1; //pointer to GPIO_OUT_claer
    gpio_set_dir(LED_PIN1, GPIO_OUT);	 //ul unsigned mit 1 << shiften zu der richten zahl

    gpio_init(LED_PIN6);
    *(SIO + 0x018 / 4) = 1ul << LED_PIN6; //pointer to GPIO_OUT_claer
    gpio_set_dir(LED_PIN6, GPIO_OUT);

    gpio_init(BUTTON_ON);
    *(SIO + 0x018 / 4) = 1ul << LED_PIN1; // macht LED aus
    gpio_set_dir(BUTTON_ON, GPIO_IN);
    gpio_pull_up(BUTTON_ON);
    

    *(SIO + 0x018 / 4) = 1ul << LED_PIN6;
    gpio_init(BUTTON_OFF);
    gpio_set_dir(BUTTON_OFF, GPIO_IN);
    gpio_pull_up(BUTTON_OFF);

    while (true)
    {
        
        uint32_t inputs = *(SIO + 0x004 / 4); //Hat alle inputs vom rasperybi gespeichert
											  // wie viele bit man weiter gehen soll durch /4
        if ((inputs & (1ul << BUTTON_ON)) == 0)// nimmt die inputs hat eine Bitmaske drüber und schaut ob das gleich ist 
        {// Da durch BUTTON_ON wird nur der Button_on angescahut 
            *(SIO + 0x014 / 4) = 1ul << LED_PIN1; //14 gleichbedeutend mit GPIO_OUT_SET
            *(SIO + 0x014 / 4) = 1ul << LED_PIN6;
        }

        if ((inputs & (1ul << BUTTON_OFF)) == 0)
        {
            // GPIO_OUT_CLR: LED ausschalten
            *(SIO + 0x018 / 4) = 1ul << LED_PIN1; //18 null setzen
            *(SIO + 0x018 / 4) = 1ul << LED_PIN6;
        }
    }
}