/*
 * MOTOR.c
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 07:47:14 PM
 *  Author: Ahmad S. Salama
 */

#include "MOTOR_alt.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/SOFTPWM/SoftPWM.h"

uint8_t MOTOR_ALT_IN1_port, MOTOR_ALT_IN1_pin;
uint8_t MOTOR_ALT_IN2_port, MOTOR_ALT_IN2_pin;
uint8_t MOTOR_ALT_IN3_port, MOTOR_ALT_IN3_pin;
uint8_t MOTOR_ALT_IN4_port, MOTOR_ALT_IN4_pin;
uint8_t MOTOR_ALT_ENA_port, MOTOR_ALT_ENA_pin;
uint8_t MOTOR_ALT_ENB_port, MOTOR_ALT_ENB_pin;
EN_MOTOR_DIRECTION_t MOTOR_ALT_direction = 5; // 5 is not a valid value, hence used for initialized "unset" direction

void MOTOR_ALT_INIT(uint8_t IN1_port, uint8_t IN1_pin,
                    uint8_t IN2_port, uint8_t IN2_pin,
                    uint8_t IN3_port, uint8_t IN3_pin,
                    uint8_t IN4_port, uint8_t IN4_pin,
                    uint8_t ENA_port, uint8_t ENA_pin,
                    uint8_t ENB_port, uint8_t ENB_pin
                   )
{
    MOTOR_ALT_IN1_port = IN1_port, MOTOR_ALT_IN1_pin = IN1_pin;
    MOTOR_ALT_IN2_port = IN2_port, MOTOR_ALT_IN2_pin = IN2_pin;
    MOTOR_ALT_IN3_port = IN3_port, MOTOR_ALT_IN3_pin = IN3_pin;
    MOTOR_ALT_IN4_port = IN4_port, MOTOR_ALT_IN4_pin = IN4_pin;
    MOTOR_ALT_ENA_port = ENA_port, MOTOR_ALT_ENA_pin = ENA_pin;
    MOTOR_ALT_ENB_port = ENB_port, MOTOR_ALT_ENB_pin = ENB_pin;
    
    SoftPWM_init(ENA_port, ENA_pin);
    SoftPWM_init(ENB_port, ENB_pin);
    
    DIO_init(IN1_port, IN1_pin, low, high);
    DIO_init(IN2_port, IN2_pin, low, high);
    DIO_init(IN3_port, IN3_pin, low, high);
    DIO_init(IN4_port, IN4_pin, low, high);
}

void MOTOR_ALT_FWD(float speed_ratio)
{
    if (MOTOR_ALT_direction != F)
    {
        DIO_write(MOTOR_ALT_IN1_port, MOTOR_ALT_IN1_pin, low);
        DIO_write(MOTOR_ALT_IN2_port, MOTOR_ALT_IN2_pin, high);
        DIO_write(MOTOR_ALT_IN3_port, MOTOR_ALT_IN3_pin, high);
        DIO_write(MOTOR_ALT_IN4_port, MOTOR_ALT_IN4_pin, low);
        
        MOTOR_ALT_direction = F;
    }
    
    MOTOR_ALT_PULSE(speed_ratio);
}

void MOTOR_ALT_BWD(float speed_ratio)
{
    if (MOTOR_ALT_direction != B)
    {
        DIO_write(MOTOR_ALT_IN1_port, MOTOR_ALT_IN1_pin, high);
        DIO_write(MOTOR_ALT_IN2_port, MOTOR_ALT_IN2_pin, low);
        DIO_write(MOTOR_ALT_IN3_port, MOTOR_ALT_IN3_pin, low);
        DIO_write(MOTOR_ALT_IN4_port, MOTOR_ALT_IN4_pin, high);
        
        MOTOR_ALT_direction = B;
    }
    
    MOTOR_ALT_PULSE(speed_ratio);
}

void MOTOR_ALT_LEFT(float speed_ratio)
{
    if (MOTOR_ALT_direction != L)
    {
        DIO_write(MOTOR_ALT_IN1_port, MOTOR_ALT_IN1_pin, high);
        DIO_write(MOTOR_ALT_IN2_port, MOTOR_ALT_IN2_pin, low);
        DIO_write(MOTOR_ALT_IN3_port, MOTOR_ALT_IN3_pin, high);
        DIO_write(MOTOR_ALT_IN4_port, MOTOR_ALT_IN4_pin, low);
        
        MOTOR_ALT_direction = L;
    }
    
    MOTOR_ALT_PULSE(speed_ratio);
}

void MOTOR_ALT_RIGHT(float speed_ratio)
{
    if (MOTOR_ALT_direction != R)
    {
        DIO_write(MOTOR_ALT_IN1_port, MOTOR_ALT_IN1_pin, low);
        DIO_write(MOTOR_ALT_IN2_port, MOTOR_ALT_IN2_pin, high);
        DIO_write(MOTOR_ALT_IN3_port, MOTOR_ALT_IN3_pin, low);
        DIO_write(MOTOR_ALT_IN4_port, MOTOR_ALT_IN4_pin, high);
        
        MOTOR_ALT_direction = R;
    }
    
    MOTOR_ALT_PULSE(speed_ratio);
}

void MOTOR_ALT_PULSE(float speed_ratio) // speed ratio is... a ratio (0 ... 1)
{
    uint8_t ports[2] = {MOTOR_ALT_ENA_port, MOTOR_ALT_ENB_port};
    uint8_t pins[2] = {MOTOR_ALT_ENA_pin, MOTOR_ALT_ENB_pin};
    SoftPWM_pulse(100 * speed_ratio, ports, pins, 2); // first parameter is duty cycle in percent  (0 ... 100)
    
    //     SoftPWM_pulse(100 * speed_ratio, MOTOR_ALT_ENA_port, MOTOR_ALT_ENA_pin); // first parameter is duty cycle in percent  (0 ... 100)
    //     SoftPWM_pulse(100 * speed_ratio, MOTOR_ALT_ENB_port, MOTOR_ALT_ENB_pin);
}