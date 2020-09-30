/*
 * SoftPWM.h
 *
 * Created: 9/21/2020 2:12:09 PM
 *  Author: farah
 */


#ifndef SOFTPWM_H_
#define SOFTPWM_H_
#include "../DIO/DIO.h"
#include "../TIMER/Timer.h"
#include "../../Application/typedefs.h"
#include "../../HWL/REG.h"

void SoftPWM_init(uint8_t output_port, uint8_t output_pin);//init of timer 0 in normal mode with prescalar 64 + init of output pin
//void SoftPWM_pulse(uint8_t dutycycle, uint8_t output_port, uint8_t output_pin);//generates one pulse on, one off
void SoftPWM_pulse(uint8_t dutycycle, uint8_t* output_ports, uint8_t* output_pins, uint8_t num_of_pins); //same as previous but simultaneously for multiple pins

#endif /* SOFTPWM_H_ */