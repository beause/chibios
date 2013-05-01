/*
    Copyright (C) 2013 Genist
*/

#ifndef _LED_H_
#define _LED_H_

#define LED_BLACK   0x07
#define LED_RED     0x01
#define LED_GREEN   0x02
#define LED_BLUE    0x04
#define LED_WHITE   0x00
#define LED_YELLOW  (LED_RED | LED_GREEN)
#define LED_MAGENTA (LED_RED | LED_BLUE)
#define LED_CYAN    (LED_GREEN | LED_BLUE)

extern void setLEDColor(uint8_t color);

#endif /* _LED_H_ */
