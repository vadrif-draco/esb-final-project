/*
 * MOTOR.c
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 07:47:14 PM
 *  Author: Ahmad S. Salama
 */

#include "MOTOR.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/PWM/PWM_TIMER.h"

uint8_t MOTOR_IN1_port, MOTOR_IN1_pin;
uint8_t MOTOR_IN2_port, MOTOR_IN2_pin;
uint8_t MOTOR_IN3_port, MOTOR_IN3_pin;
uint8_t MOTOR_IN4_port, MOTOR_IN4_pin;
EN_MOTOR_STATE_t MOTOR_state = stopped;
EN_MOTOR_DIRECTION_t MOTOR_direction = 5; // 5 is not a valid value, hence used for initialized "unset" direction

void MOTOR_INIT(uint8_t IN1_port, uint8_t IN1_pin,
                uint8_t IN2_port, uint8_t IN2_pin,
                uint8_t IN3_port, uint8_t IN3_pin,
                uint8_t IN4_port, uint8_t IN4_pin)
{

    PWM_init(PCPWM);
    
    MOTOR_IN1_port = IN1_port, MOTOR_IN1_pin = IN1_pin;
    MOTOR_IN2_port = IN2_port, MOTOR_IN2_pin = IN2_pin;
    MOTOR_IN3_port = IN3_port, MOTOR_IN3_pin = IN3_pin;
    MOTOR_IN4_port = IN4_port, MOTOR_IN4_pin = IN4_pin;
    
    DIO_init(IN1_port, IN1_pin, low, high);
    DIO_init(IN2_port, IN2_pin, low, high);
    DIO_init(IN3_port, IN3_pin, low, high);
    DIO_init(IN4_port, IN4_pin, low, high);
}

void MOTOR_FWD(float speed_ratio)
{
    if (MOTOR_state == stopped)
    {
        if (MOTOR_direction != F)
        {
            DIO_write(MOTOR_IN1_port, MOTOR_IN1_pin, high);
            DIO_write(MOTOR_IN2_port, MOTOR_IN2_pin, low);
            DIO_write(MOTOR_IN3_port, MOTOR_IN3_pin, low);
            DIO_write(MOTOR_IN4_port, MOTOR_IN4_pin, high);
            
            MOTOR_direction = F;
        }
        
        MOTOR_START(speed_ratio);
    }
}

void MOTOR_BWD(float speed_ratio)
{
    if (MOTOR_state == stopped)
    {
        if (MOTOR_direction != B)
        {
            DIO_write(MOTOR_IN1_port, MOTOR_IN1_pin, low);
            DIO_write(MOTOR_IN2_port, MOTOR_IN2_pin, high);
            DIO_write(MOTOR_IN3_port, MOTOR_IN3_pin, high);
            DIO_write(MOTOR_IN4_port, MOTOR_IN4_pin, low);
            
            MOTOR_direction = B;
        }
        
        MOTOR_START(speed_ratio);
    }
}

void MOTOR_LEFT(float speed_ratio)
{
    if (MOTOR_state == stopped)
    {
        if (MOTOR_direction != L)
        {
            DIO_write(MOTOR_IN1_port, MOTOR_IN1_pin, low);
            DIO_write(MOTOR_IN2_port, MOTOR_IN2_pin, high);
            DIO_write(MOTOR_IN3_port, MOTOR_IN3_pin, low);
            DIO_write(MOTOR_IN4_port, MOTOR_IN4_pin, high);
            
            MOTOR_direction = L;
        }
        
        MOTOR_START(speed_ratio);
    }
}

void MOTOR_RIGHT(float speed_ratio)
{
    if (MOTOR_state == stopped)
    {
        if (MOTOR_direction != R)
        {
            DIO_write(MOTOR_IN1_port, MOTOR_IN1_pin, high);
            DIO_write(MOTOR_IN2_port, MOTOR_IN2_pin, low);
            DIO_write(MOTOR_IN3_port, MOTOR_IN3_pin, high);
            DIO_write(MOTOR_IN4_port, MOTOR_IN4_pin, low);
            
            MOTOR_direction = R;
        }
        
        MOTOR_START(speed_ratio);
    }
}

void MOTOR_START(float speed_ratio)
{
    PWM_setOCRA( (uint16_t) (65535.0f * speed_ratio) );
    PWM_setOCRB( (uint16_t) (65535.0f * speed_ratio) );
    PWM_start(clk, 0);
    MOTOR_state = running;
}

void MOTOR_STOP()
{
    if (MOTOR_state == running)
    {
        MOTOR_state = stopped;
        PWM_stop();
    }
}