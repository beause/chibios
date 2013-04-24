#include "ch.h"
#include "hal.h"

/**
**  @brief turn LED on/off
**  @param TRUE=LED on, FALSE=LED off
**/
void switchLED(GPIO_TypeDef* gpiot, uint8_t pin, bool_t onoff)
{

  if (!(gpiot == GPIOC && (pin == GPIOC_LED_R ||
			   pin == GPIOC_LED_B ||
			   pin == GPIOC_LED_G))) {
    port_halt();
  }

  /* 
     genistCustom board as of March 18, 2013
     LEDs are wired to 5V.  To turn off must
     make pin float.  To turn on, pull low. 
   */

  if (onoff == FALSE)   {
#if 0
    /* 
       turn LED off 
       
       make GPIO pin an input, and floating
     */
    gpiot->MODER &= ~( 1 << (2*pin));
    gpiot->PUPDR &= ~( 1 << (2*pin));
#else
    gpiot->MODER  &= ~( 1 << (2*pin));  /* clear mode */
    gpiot->MODER  |=  ( 1 << (2*pin));  /* set to output */
    gpiot->OTYPER &= ~( 1 << pin);      /* set to push pull */
    gpiot->PUPDR  &= ~( 1 << (2*pin));  /* set to floating */
    gpiot->ODR    |= ( 1 << pin);      /* set output to 0 */
#endif
  }
  else {
    /* 
       turn LED on 
       
       make GPIO pin an output, and set to low
     */
    gpiot->MODER  &= ~( 1 << (2*pin));  /* clear mode */
    gpiot->MODER  |=  ( 1 << (2*pin));  /* set to output */
    gpiot->OTYPER &= ~( 1 << pin);      /* set to push pull */
    gpiot->PUPDR  &= ~( 1 << (2*pin));  /* set to floating */
    gpiot->ODR    &= ~( 1 << pin);      /* set output to 0 */
  }
}

