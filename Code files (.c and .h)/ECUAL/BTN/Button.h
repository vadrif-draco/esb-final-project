/*
 * Button.h
 *
 *  Created on: Sep 19, 2020
 *      Author: ezzelgaby
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../Application/typedefs.h"

void Button_init(uint8_t port_num, uint8_t pin_num);
uint8_t Button_read(uint8_t port_num, uint8_t pin_num);
void Button_with_interrupt_init(EN_EXT_INTERRUPT_t e, EN_INTERRUPT_TRIGGER_t t, void (*ISR)());
void __vector_1(void) __attribute__ ((signal, used)); // ISR for external interrupt 0

#endif /* BUTTON_H_ */
