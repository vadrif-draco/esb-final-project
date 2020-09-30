/*
 * Timer.h
 *
 * Created: 24/09/2020 2:10:21 pm
 *  Author: ahmed
 */


#ifndef TIMER_H_
#define TIMER_H_

#include "../DIO/DIO.h"
#include "../../HWL/REG.h"
#include "../../Application/typedefs.h"
#include "../../HWL/REG.h"

extern EN_CLOCKSOURCE_t clkSource;

void timerInit(EN_TIMERMODE_t tmode, EN_CLOCKSOURCE_t source); //initialize timer with its mode (normal, CTC, fast PWM, PWM Phase Correct) and prescaler
void setCompare(uint8_t cmpValue, EN_CMPMODE_t cmpMode); //Set compare value for CTC, fast PWM, PWM Phase Correct and its mode on OC0 pin
void timerdelayMS(int32_t timeMS); //Delay time in millisecond
void timerdelay(int32_t time); //Delay time given prescaler (noclk,clk,clk_8,clk_64,clk_256,clk_1024,clk_ext_rising,clk_ext_falling)
void prescaler(EN_CLOCKSOURCE_t source); //Set prescaler to

void timerStop();	//Private function don't call
void timerCycle();	//private function don't call


#endif /* TIMER_H_ */