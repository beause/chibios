/*
    Copyright (C) 2013 Genist
*/

#ifndef _LED_H_
#define _LED_H_

#define LED_RED_MASK    0x00ff0000
#define LED_GREEN_MASK  0x0000ff00
#define LED_BLUE_MASK   0x000000ff
#define LED_BLACK       0x00
#define LED_RED         LED_RED_MASK
#define LED_GREEN       LED_GREEN_MASK
#define LED_BLUE        LED_BLUE_MASK
#define LED_WHITE       0x00ffffff
#define LED_YELLOW      (LED_RED_MASK | LED_GREEN_MASK)
#define LED_MAGENTA     (LED_RED_MASK | LED_BLUE_MASK)
#define LED_CYAN        (LED_GREEN_MASK | LED_BLUE_MASK)

extern void setLEDColor(uint32_t color);

#endif /* _LED_H_ */
