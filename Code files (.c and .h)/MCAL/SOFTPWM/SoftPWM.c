/*
 * SoftPWM.c
 *
 * Created: 9/21/2020 2:12:32 PM
 *  Author: farah*/

#include "SoftPWM.h"
void SoftPWM_init(uint8_t output_port, uint8_t output_pin)
{
    DIO_init(output_port, output_pin, low, high);
    timerInit(NORMAL, clk_64);
    
}

//duty cycle is a percentage, and consider the whole period to be 16 ms,
//so for example when we want 60% duty cycle, ontime should be 9.6 ms  and offtime 6.4 ms
void SoftPWM_pulse(uint8_t dutycycle, uint8_t* output_ports, uint8_t* output_pins, uint8_t num_of_pins)
{
    for (int i = 0; i < num_of_pins; i++)
        DIO_write(output_ports[i], output_pins[i], high);
        
    uint8_t ontime = 250 * (dutycycle / 100.0); //250 micro*64=16ms
    uint8_t offtime = 250 - ontime;
    timerdelay(ontime);
    
    for (int i = 0; i < num_of_pins; i++)
        DIO_write(output_ports[i], output_pins[i], low);
        
    timerdelay(offtime);
    
    
}