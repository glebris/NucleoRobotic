#include <stm32f10x.h>

#define LED_PIN 5
#define LED_ON()  do{GPIOA->BSRR |= GPIO_BSRR_BS5 ;}while(0)
#define LED_OFF() do{GPIOA->BSRR |= GPIO_BSRR_BR5;}while(0)
 
int main() {
	/* Enbale GPIOA clock */
	RCC->AHBENR |= RCC_AHB1ENR_GPIOAEN;
	/* Configure GPIOA pin 5 as output */
	GPIOA->MODER |= (1 << (LED_PIN << 1));
	/* Configure GPIOA pin 5 in max speed */
	GPIOA->OSPEEDR |= (3 << (LED_PIN << 1));
 
	/* Turn on the LED */
	LED_ON();
 
}

