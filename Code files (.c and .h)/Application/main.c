/*
 * main.c
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 09:54:24 AM
 * Author : Ahmad S. Salama
 */

#include "../MCAL/SOFTPWM/SoftPWM.h"

#include "../ECUAL/MOTOR/MOTOR_ALT.h"
#include "../ECUAL/MOTOR/MOTOR.h"
#include "../ECUAL/BTN/Button.h"
#include "../ECUAL/LED/LED.h"

#include "typedefs.h"

float motor_speeds[] = {0.3, 0.6, 0.9};
int8_t current_speed = 0;

void shift_gear(void)
{
    if (current_speed + 1 == sizeof(motor_speeds) / sizeof(float))
        current_speed = -1;
    else
        current_speed++;
}

void (*ISR_callback)() = &shift_gear; // Setting up the function for ISR callback

int main(void)
{
    Button_init('D', 2); // GEAR BUTTON
    Button_with_interrupt_init(INT0, RISING, ISR_callback); // GEAR BUTTON INTERRUPT SETTING (D2 = INT0)
    Button_init('A', 0); // MOVE BUTTON
    Button_init('A', 1); // LEFT BUTTON
    Button_init('A', 2); // RIGHT BUTTON
    
    // We initialize the first motor driver (H-bridge) via its direction pins
    MOTOR_INIT('C', 0,	// IN1
               'C', 1,	// IN2
               'C', 2,	// IN3
               'C', 3	// IN4
              );
              
    // Then the second, along with its SOFTPWM initializations
    MOTOR_ALT_INIT('B', 6,	// IN1
                   'B', 5,	// IN2
                   'B', 4,	// IN3
                   'B', 3,	// IN4
                   'B', 2,  // ENA
                   'B', 1	// ENB
                  );
                  
    while (1)
    {
        // hold move
        if (Button_read('A', 0))
        {
            current_speed == -1 ? MOTOR_BWD(motor_speeds[0]) : MOTOR_FWD(motor_speeds[current_speed]);
            current_speed == -1 ? MOTOR_ALT_BWD(motor_speeds[0]) : MOTOR_ALT_FWD(motor_speeds[current_speed]);
        }
        
        // hold left
        else if (Button_read('A', 1))
        {
            MOTOR_LEFT(motor_speeds[0]);
            MOTOR_ALT_LEFT(motor_speeds[0]);
        }
        
        // hold right
        else if (Button_read('A', 2))
        {
            MOTOR_RIGHT(motor_speeds[0]);
            MOTOR_ALT_RIGHT(motor_speeds[0]);
        }
        
        // nothing held
        else
        {
            MOTOR_STOP();
        }
    }
}

/*

"Documentation" of some sorts...

*Components:*

- 4 buttons: [LEFT (L)] [MOVE (M)] [RIGHT (R)] [GEAR (G)]
- 2 DC motors
- the microcontroller obviously
- H-bridge L298(n)


*States:*

- Moving forwards @(.3, .6, .9) speed
- Moving backwards @(.3) speed
- Stopped


*Code Architecture:*

- Application: main.c, typedefs.h
- ECUAL: BTN(.c+.h), LED(.c+.h), MOTOR(.c+.h)
- MCAL: DIO(.c+.h), TIMER(.c+.h), PWM_TIMER(.c+.h), SOFTPWM(.c+.h), PWM(.c+.h), TIMER(.c+.h)
- HWL: REG.h


*A potential usage sequence to verify final system:*

01. Initially, car is stopped.

02. The state of the car regarding motion speed and direction in this step is unknown,
hence we will assume that - by default - the car starts at speed 1, forward direction.

03. *HELD* M? Now car is moving with speed and direction car is set at.
04. *RELEASED* M? Stop car.

05. Pressed G? Go to speed 2 w/ direction forward. (Not moving)
06. *HELD* M? Move at speed and direction currently set.
07. *RELEASED* M? Stop car.

08. Pressed G? Go to speed 3 w/ direction forward. (Not moving)
09. *HELD* M? Move at speed and direction currently set.
10. *RELEASED* M? Stop car.

11. Pressed G? Go to speed 1 w/ direction backward. (Not moving)
12. *HELD* M? Move at speed and direction currently set.
13. *RELEASED* M? Stop car.

14. *HELD* R? Car rotates around itself clockwise at 30% speed
15. *RELEASED* R? Stop car.

16. *HELD* L? Car rotates around itself anticlockwise at 30% speed
17. *RELEASED* L? Stop car.

*/