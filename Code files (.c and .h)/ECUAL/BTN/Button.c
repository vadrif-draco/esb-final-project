/*
 * Button.cpp (Changed to Button.c)
 *
 *  Created on: Sep 19, 2020
 *      Author: ezzelgaby
 *		Modified by: Ahmad S. Salama
 */

#include "../../Application/typedefs.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../HWL/REG.h"
#include "Button.h"

void (*ISR_callback)();

void Button_init(uint8_t port_num, uint8_t pin_num)
{
    DIO_init(port_num, pin_num, low, low); // ... PORTx DDRx
}

uint8_t Button_read(uint8_t port_num, uint8_t pin_num)
{
    return DIO_read(port_num, pin_num);
}

void Button_with_interrupt_init(EN_EXT_INTERRUPT_t e, EN_INTERRUPT_TRIGGER_t t, void (*ISR)())
{

    ISR_callback = ISR;
    
    switch (e)
    {
        case INT0:
        {
            MCUCR |= t;
            break;
        }
        
        case INT1:
        {
            MCUCR |= t << 2;
            break;
        }
        
        case INT2:
        {
            // still have no idea what to do here, unused anyway
            break;
        }
        
        default:
            break;
    }
    
    SREG |= 1 << 7;
    GICR |= 1 << e;
}

// ISR for external interrupt 0
void __vector_1(void)
{
    ISR_callback();
}