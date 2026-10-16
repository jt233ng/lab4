#include "pico/stdlib.h" //so that i can use the Pico SDK

#define LED_PIN	0
#define BUTTON_ON 1
#define BUTTON_OFF 2


int main(void) //void ncihts wird übergeben
{
	gpio_init(LED_PIN);
	gpio_put(LED_PIN, 0);
	gpio_set_dir(LED_PIN, GPIO_OUT);


	gpio_init(BUTTON_ON);
	gpio_set_dir(BUTTON_ON, GPIO_IN);
	gpio_pull_up(BUTTON_ON); //Pull ob so nicht gedrückt makes 1

	gpio_init(BUTTON_OFF);
	gpio_set_dir(BUTTON_OFF, GPIO_IN);
	gpio_pull_up(BUTTON_OFF);

	while(true)
	{
		if(!gpio_get(BUTTON_ON))//! because its a pull up
		{
			gpio_put(LED_PIN,1);
		} 
		else if(!gpio_get(BUTTON_OFF))//! because its a pull up
		{
			gpio_put(LED_PIN,0);
		} 
	}
}