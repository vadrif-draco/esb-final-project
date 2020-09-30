/*
 * DIO.c
 *
 * Created: 16/08/2020 23:45:56
 *  Author: Seif Habib
 */

#include "../../Application/typedefs.h"
#include "../../HWL/REG.h"
#include "DIO.h"

void DIO_init(uint8_t port, uint8_t pin, EN_bit data, EN_bit ctrl)
{
    if (ctrl == high)
        DIO_set(port, pin, high);
    else
        DIO_set(port, pin, low);
        
    if (data == high)
        DIO_write(port, pin, high);
    else
        DIO_write(port, pin, low);
}

void DIO_set (uint8_t port, uint8_t pin, EN_bit value)
{
    switch (port)
    {
        case 'A':
            if (value)
                setbit(&PA_ctrl, pin);
            else
                clrbit(&PA_ctrl, pin);
                
            break;
            
        case 'B':
            if (value)
                setbit(&PB_ctrl, pin);
            else
                clrbit(&PB_ctrl, pin);
                
            break;
            
        case 'C':
            if (value)
                setbit(&PC_ctrl, pin);
            else
                clrbit(&PC_ctrl, pin);
                
            break;
            
        case 'D':
            if (value)
                setbit(&PD_ctrl, pin);
            else
                clrbit(&PD_ctrl, pin);
                
            break;
    }
}

void DIO_write (uint8_t port, uint8_t pin, EN_bit value)
{
    switch (port)
    {
        case 'A':
            if (value)
                setbit(&PA_data, pin);
            else
                clrbit(&PA_data, pin);
                
            break;
            
        case 'B':
            if (value)
                setbit(&PB_data, pin);
            else
                clrbit(&PB_data, pin);
                
            break;
            
        case 'C':
            if (value)
                setbit(&PC_data, pin);
            else
                clrbit(&PC_data, pin);
                
            break;
            
        case 'D':
            if (value)
                setbit(&PD_data, pin);
            else
                clrbit(&PD_data, pin);
                
            break;
    }
}

uint8_t DIO_read(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case 'A':
            return readbit(&PA_pin, pin);
            
        case 'B':
            return readbit(&PB_pin, pin);
            
        case 'C':
            return readbit(&PC_pin, pin);
            
        case 'D':
            return readbit(&PD_pin, pin);
            
        default:
            return low;
    }
}

void DIO_toggle(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case 'A':
            tglbit(&PA_data, pin);
            break;
            
        case 'B':
            tglbit(&PB_data, pin);
            break;
            
        case 'C':
            tglbit(&PC_data, pin);
            break;
            
        case 'D':
            tglbit(&PD_data, pin);
            break;
    }
}



uint8_t readbit (volatile uint8_t* portadd, uint8_t bit)
{
    return (*portadd & (1 << bit)); // should return low or high
}

void setbit (volatile uint8_t* portadd, uint8_t bit)
{
    *portadd |= (1 << bit);
}

void tglbit (volatile uint8_t* portadd, uint8_t bit)
{
    *portadd ^= (1 << bit);
    
}

void clrbit (volatile uint8_t* portadd, uint8_t bit)
{
    *portadd &= ~(1 << bit);
}