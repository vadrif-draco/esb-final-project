/*
 * PWM_TIMER.h
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 01:50:49 PM
 *  Author: Ahmad S. Salama
 */

/*
TIMER MODES:

	normal/overflow mode:

		since timer register is 8 bits, and it is continuously incrementing at 1MHz (so increments once per microsecond),
		this means that it overflows after 256 microseconds. This raises the overflow flag (TOVn).
		If required delay is less than that all good. If more, you need prescaler.
		A prescaler of 2 for example halves the frequency, making the 256 bits overflow in 512 microseconds.
		Setting the delay is done by loading TCNTn at the max value (in prev. example, 512,) minus the number required.
____________________________________________________________________________________________________________________________________

	ctc mode: (uses a flag to interrupt its loop at satisfied comparison, (OCFn) flag to be exact)

		*** *** *** NOTE: The OCFn Flag can be cleared by software by writing a logical one to its I/O bit location *** *** ***

		instead of always overflowing, the value required is set as the cap of the timer, so once it reaches it it becomes 0.
		This "comparison" is done via comparing the value stored in a register "OCR" (output compare register)
____________________________________________________________________________________________________________________________________

	fast-pwm mode:

		makes use of the OCFn flag but instead of zeroing the counter register, it controls the 5V output compare pin "OC0",
		where while lower than OCFn flag it sets it as 0V (or 5V) and once higher flips.

		mode 1:	non-inverting: while lower than OCR, LOW, else, HIGH
		mode 2:     inverting: ... opposite
____________________________________________________________________________________________________________________________________

	phase-correct-pwm mode: like fast-pwm but instead of going up then overflowing it goes up then goes down.
____________________________________________________________________________________________________________________________________

	counter mode: external source (Tn) gives you input, based on which you count via detecting rising edges or falling edges
____________________________________________________________________________________________________________________________________

	For PWM modes:
		Duty Cycle %ge = OCR/max "which is 256 for 8-bit timers", hence:

			OCR = 256 × Duty Cycle %ge

*/

#ifndef PWM_TIMER_H_
#define PWM_TIMER_H_

#include "../../Application/typedefs.h"
#include "../../HWL/REG.h"

void PWM_init(EN_TIMERMODE_t tm);

void PWM_setValue(uint16_t value);

void PWM_setOCRA(uint16_t val);
void PWM_setOCRB(uint16_t val);

void PWM_start(EN_CLOCKSOURCE_t cs, uint16_t startVal);
void PWM_stop();

void PWM_reset();

#endif /* PWM_TIMER_H_ */