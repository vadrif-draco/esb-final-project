/*
 * PWM_TIMER.c
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 01:50:43 PM
 *  Author: Ahmad S. Salama
 */

#include "PWM_TIMER.h"
#include "../DIO/DIO.h"

void PWM_init(EN_TIMERMODE_t tm)
{
    // Here we set the different TCCRxn bits that control the timer mode
    // The bits we need to change are [0, 1] in TCCR1A, [3, 4] in TCCR1B
    // Also, we setup the compare output mode, with bits [4:7] in TCCR1A
    // Possible PWM modes are: PCPWM and FPWM (explained in header file)
    // *** NOTICE: Setting the mode doesn't immediately start the timer!
    
    switch (tm)
    {
        case NORMAL:	// WGM1[3:0] = 0000 [unused]
            break;
            
        case CTC:		// WGM1[3:0] = 0100 [unused]
            break;
            
        case PCPWM:		// WGM1[3:0] = 1010
        
            TCCR1A &= ~(1 << 0);			// ...0
            TCCR1A |= (1 << 1);				// ..10
            TCCR1B &= ~(1 << 3);			// .010
            TCCR1B |= (1 << 4);				// 1010
            break;
            
        case FPWM:		// WGM1[3:0] = 1110
        
            TCCR1A &= ~(1 << 0);			// ...0
            TCCR1A |= (1 << 1);				// ..10
            TCCR1B |= (1 << 4) | (1 << 3);	// 1111
            break;
            
        default:
            break;
    }
    
    TCCR1A |= 0xA0; // |= 1010 0000... --> COM1[7:4] = 1010
    
    // Finally, we setup the two pins where the PWM output is to come out
    DIO_init('D', 4, low, high);
    DIO_init('D', 5, low, high);
    
    // As well as the register corresponding to the TOP of the counter
    ICR1H = 0xFF; ICR1L = 0xFF;
    
}

// *** To do a 16-bit write, the high byte must be written before the low byte.

void PWM_setValue(uint16_t value)
{
    TCNT1H = (uint8_t) (value >> 8) & 0xFF;
    TCNT1L = (uint8_t) (value >> 0) & 0xFF;
}

void PWM_setOCRA(uint16_t val)
{
    OCR1AH = (uint8_t) (val >> 8) & 0xFF;
    OCR1AL = (uint8_t) (val >> 0) & 0xFF;
}

void PWM_setOCRB(uint16_t val)
{
    OCR1BH = (uint8_t) (val >> 8) & 0xFF;
    OCR1BL = (uint8_t) (val >> 0) & 0xFF;
}

void PWM_start(EN_CLOCKSOURCE_t cs, uint16_t startVal)
{
    // First, we set the starting value before the timer starts. This action doesn't start the timer.
    PWM_setValue(startVal);
    
    // To actually start the timer, we have to set its clock source, then it immediately starts counting.
    // To set the clock source, we use the respective TCCR register to adjust bits 2:0.
    TCCR1B &= 0xF8; // (1111 1000) First we clear the three bits
    TCCR1B |= (uint8_t) cs; // Then we set them as we wish
}

void PWM_stop()
{
    // Here, to stop the timer, we set the OCRs to zero.
    
    OCR1AH = 0; OCR1BH = 0;
    OCR1AL = 0; OCR1BL = 0;
}

void PWM_reset()
{
    // 1. Stop the timer (PWM first)
    PWM_stop();
    
    // 2. Reset clock source and count
    TCCR1B &= 0xF8;	// 1111 1000
    TCNT1H = 0;
    TCNT1L = 0;
    
    // 3. Reset its mode (by setting it to normal)
    TCCR1A &= ~(1 << 1) & ~(1 << 0);	// ..00
    TCCR1B &= ~(1 << 4) & ~(1 << 3);	// 0000
}