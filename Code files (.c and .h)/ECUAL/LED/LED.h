/*
 * LED.h
 *
 *  Created on: Sep 19, 2020
 *      Author: ezzelgaby
 */

#ifndef LED_H_
#define LED_H_

#include "../../Application/typedefs.h"

void LED_ON(uint8_t port, uint8_t pin);
void LED_OFF(uint8_t port, uint8_t pin);
void LED_toggle(uint8_t port, uint8_t pin);
void LED_init(uint8_t port, uint8_t pin, EN_bit data);


#endif /* LED_H_ */
