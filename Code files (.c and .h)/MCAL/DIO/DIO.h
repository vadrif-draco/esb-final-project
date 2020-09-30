/*
 * DIO.h
 *
 * Created: 16/08/2020 23:46:09
 *  Author: Seif Habib
 */

#ifndef DIO_H_
#define DIO_H_

#include "../../Application/typedefs.h"

//don't forget to pass the port between ''
void DIO_init(uint8_t port, uint8_t pin, EN_bit data, EN_bit ctrl);//initialize the data and control of the pin
uint8_t DIO_read(uint8_t port, uint8_t pin); //reads pin value and return 0 for low otherwise high
void DIO_set (uint8_t port, uint8_t pin, EN_bit value); //set the ctrl value on a pin
void DIO_write (uint8_t port, uint8_t pin, EN_bit value); //write data on a pin high or low
void DIO_toggle(uint8_t port, uint8_t pin); //toggle data on a pin

//we can change it later and put it in a general header files as a macro, so anyone can use it in any driver.
//bit manipulation
//don't forget to pass the portadd by reference put & before the reg address
uint8_t readbit ( volatile uint8_t* portadd, uint8_t bit);
void setbit (volatile uint8_t* portadd, uint8_t bit);
void tglbit (volatile uint8_t* portadd, uint8_t bit);
void clrbit (volatile uint8_t* portadd, uint8_t bit);
#endif /* DIO_H_ */