/*
 * LED.cpp (changed to LED.c)
 *
 *  Created on: Sep 19, 2020
 *      Author: ezzelgaby
 *		Modified by: Ahmad S. Salama
 */

#include "../../Application/typedefs.h"
#include "../../MCAL/DIO/DIO.h"
#include "LED.h"

void LED_ON(uint8_t port_num, uint8_t pin_num)
{
    DIO_write (port_num, pin_num, 1);
}

void LED_OFF(uint8_t port_num, uint8_t pin_num)
{
    DIO_write (port_num, pin_num, 0);
}

void LED_toggle(uint8_t port_num, uint8_t pin_num)
{
    DIO_toggle(port_num, pin_num);
}

void LED_init(uint8_t port_num, uint8_t pin_num, EN_bit data)
{
    DIO_init(port_num, pin_num, data, high);
}
