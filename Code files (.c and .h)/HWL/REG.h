#ifndef REG_H_
#define REG_H_

//DIO DRIVER REGISTERS
#define PA_data *((volatile uint8_t*)(0x3B)) // PORT (output control for output pins)
#define PA_ctrl *((volatile uint8_t*)(0x3A)) // DDR (direction setter "I/O")
#define PA_pin	*((volatile uint8_t*)(0x39)) // PIN (for reading the value)

#define PB_data *((volatile uint8_t*)(0x38))
#define PB_ctrl *((volatile uint8_t*)(0x37))
#define PB_pin	*((volatile uint8_t*)(0x36))

#define PC_data *((volatile uint8_t*)(0x35))
#define PC_ctrl *((volatile uint8_t*)(0x34))
#define PC_pin	*((volatile uint8_t*)(0x33))

#define PD_data *((volatile uint8_t*)(0x32))
#define PD_ctrl *((volatile uint8_t*)(0x31))
#define PD_pin	*((volatile uint8_t*)(0x30))

// TIMER0 REGISTERS
#define T0_data	*((volatile uint8_t*)(0x52))
#define T0_ctrl	*((volatile uint8_t*)(0x53))
#define T0_flag	*((volatile uint8_t*)(0x58)) // This is TIFR, 3omda...
#define T0_cmp	*((volatile uint8_t*)(0x5C))

// TIMER INTERRUPTS/FLAGS REGISTERS
#define TIFR	*((volatile uint8_t*)(0x58)
/* Flags register

7		6		5		4		3		2		1		0
OCF2	TOV2	ICF1	OCF1A	OCF1B	TOV1	OCF0	TOV0

*/

#define SREG	*((volatile uint8_t*)(0x5F)) // Status register
#define GICR	*((volatile uint8_t*)(0x5B)) // General Interrupt Control Register
#define MCUCR	*((volatile uint8_t*)(0x55)) // MCU Control register
#define TIMSK	*((volatile uint8_t*)(0x59)) // Interrupts masker


// TIMER2 REGISTERS
#define TCCR1A	*((volatile uint8_t*)(0x4F))
/*

7		6		5		4		3		2		1		0
COM1A1	COM1A0	COM1B1	COM1B0	FOC1A	FOC1B	WGM11	WGM10

COM1A[1:0]:	Compare Output Mode for Compare unit A
COM1B[1:0]:	Compare Output Mode for Compare unit B
FOC1A:		Force Output Compare for Compare unit A
FOC1B:		Force Output Compare for Compare unit B
WGM1[1:0]:	Waveform Generation Mode

*/

#define TCCR1B	*((volatile uint8_t*)(0x4E))
/*

7		6		5		4		3		2		1		0
ICNC1	ICES1	–		WGM13	WGM12	CS12	CS11	CS10

ICNC1:		Input Capture Noise Canceler
ICES1:		Input Capture Edge Select
WGM1[3:2]:	Waveform Generation Mode
CS1[2:0]:	Clock Select

*/

#define TCNT1H	*((volatile uint8_t*)(0x4D)) // For reading/writing the timer/counter value (high byte)
#define TCNT1L	*((volatile uint8_t*)(0x4C)) // For reading/writing the timer/counter value (low byte)
#define OCR1AH	*((volatile uint8_t*)(0x4B)) // For reading/writing the OCR (comparator) (high byte)
#define OCR1AL	*((volatile uint8_t*)(0x4A)) // For reading/writing the OCR (comparator) (low byte)
#define OCR1BH	*((volatile uint8_t*)(0x49)) // For reading/writing the OCR (comparator) (high byte)
#define OCR1BL	*((volatile uint8_t*)(0x48)) // For reading/writing the OCR (comparator) (low byte)
#define ICR1H	*((volatile uint8_t*)(0x47)) // For input capturing or the TOP value (high byte)
#define ICR1L	*((volatile uint8_t*)(0x46)) // For input capturing or the TOP value (low byte)

#endif /* REG_H_ */