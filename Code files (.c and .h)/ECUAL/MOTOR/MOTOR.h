/*
 * MOTOR.h
 *
 * Created: Sun, 20 Sep, 20 - 20, 9, 20 07:47:27 PM
 *  Author: Ahmad S. Salama
 */


#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../Application/typedefs.h"

void MOTOR_INIT(uint8_t IN1_port, uint8_t IN1_pin,
                uint8_t IN2_port, uint8_t IN2_pin,
                uint8_t IN3_port, uint8_t IN3_pin,
                uint8_t IN4_port, uint8_t IN4_pin);

void MOTOR_FWD(float speed_ratio);
void MOTOR_BWD(float speed_ratio);
void MOTOR_LEFT(float speed_ratio);
void MOTOR_RIGHT(float speed_ratio);
void MOTOR_START(float speed_ratio);
void MOTOR_STOP();


#endif /* MOTOR_H_ */