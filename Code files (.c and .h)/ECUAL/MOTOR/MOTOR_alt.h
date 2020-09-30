#ifndef MOTOR_ALT_H_
#define MOTOR_ALT_H_

#include "../../Application/typedefs.h"

void MOTOR_ALT_INIT(uint8_t IN1_port, uint8_t IN1_pin,
                    uint8_t IN2_port, uint8_t IN2_pin,
                    uint8_t IN3_port, uint8_t IN3_pin,
                    uint8_t IN4_port, uint8_t IN4_pin,
                    uint8_t ENA_port, uint8_t ENA_pin,
                    uint8_t ENB_port, uint8_t ENB_pin);

void MOTOR_ALT_FWD(float speed_ratio);
void MOTOR_ALT_BWD(float speed_ratio);
void MOTOR_ALT_LEFT(float speed_ratio);
void MOTOR_ALT_RIGHT(float speed_ratio);
void MOTOR_ALT_PULSE(float speed_ratio);
void MOTOR_ALT_STOP();


#endif /* MOTOR_ALT_H_ */