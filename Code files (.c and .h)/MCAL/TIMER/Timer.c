/*
 * TIMER.c
 *
 * Created: 24/09/2020 2:10:29 pm
 *  Author: ahmed
 */


#include "Timer.h"

EN_CLOCKSOURCE_t clkSource;

void timerInit(EN_TIMERMODE_t tmode, EN_CLOCKSOURCE_t source)
{
    if (tmode == NORMAL)
    {
        clrbit(&T0_ctrl, 3);
        clrbit(&T0_ctrl, 6);
    }
    else if (tmode == PCPWM)
    {
        clrbit(&T0_ctrl, 3);
        setbit(&T0_ctrl, 6);
    }
    else if (tmode == CTC)
    {
        setbit(&T0_ctrl, 3);
        clrbit(&T0_ctrl, 6);
    }
    else if (tmode == FPWM)
    {
        setbit(&T0_ctrl, 3);
        setbit(&T0_ctrl, 6);
    }
    
    clkSource = source;
}
void setCompare(uint8_t cmpValue, EN_CMPMODE_t cmpMode)
{
    T0_cmp = cmpValue;
    
    if (cmpMode == DISCONNECTED)
    {
        clrbit(&T0_ctrl, 4);
        clrbit(&T0_ctrl, 5);
    }
    else if (cmpMode == REVERSED)
    {
        setbit(&T0_ctrl, 4);
        clrbit(&T0_ctrl, 5);
    }
    else if (cmpMode == CLR_CMP)
    {
        clrbit(&T0_ctrl, 4);
        setbit(&T0_ctrl, 5);
    }
    else if (cmpMode == SET_CMP)
    {
        setbit(&T0_ctrl, 4);
        setbit(&T0_ctrl, 5);
    }
}
void prescaler(EN_CLOCKSOURCE_t source)
{
    if (source == noclk)
    {
        clrbit(&T0_ctrl, 0);
        clrbit(&T0_ctrl, 1);
        clrbit(&T0_ctrl, 2);
    }
    else if (source == clk)
    {
        setbit(&T0_ctrl, 0);
        clrbit(&T0_ctrl, 1);
        clrbit(&T0_ctrl, 2);
    }
    else if (source == clk_8)
    {
        clrbit(&T0_ctrl, 0);
        setbit(&T0_ctrl, 1);
        clrbit(&T0_ctrl, 2);
    }
    else if (source == clk_64)
    {
        setbit(&T0_ctrl, 0);
        setbit(&T0_ctrl, 1);
        clrbit(&T0_ctrl, 2);
    }
    else if (source == clk_256)
    {
        clrbit(&T0_ctrl, 0);
        clrbit(&T0_ctrl, 1);
        setbit(&T0_ctrl, 2);
    }
    else if (source == clk_1024)
    {
        setbit(&T0_ctrl, 0);
        clrbit(&T0_ctrl, 1);
        setbit(&T0_ctrl, 2);
    }
    else if (source == clk_ext_rising)
    {
        clrbit(&T0_ctrl, 0);
        setbit(&T0_ctrl, 1);
        setbit(&T0_ctrl, 2);
    }
    else if (clk_ext_falling)
    {
        setbit(&T0_ctrl, 0);
        setbit(&T0_ctrl, 1);
        setbit(&T0_ctrl, 2);
    }
    else
    {
        clrbit(&T0_ctrl, 0);
        clrbit(&T0_ctrl, 1);
        clrbit(&T0_ctrl, 2);
    }
}

void timerStop()
{
    setbit(&T0_flag, 0);
    prescaler(noclk);
    T0_data = 0x00;
}

void timerCycle()
{
    while (readbit(&T0_flag, 0) != 1);
    
    setbit(&T0_flag, 0);
}


void timerdelayMS(int32_t timeMS)
{
    int32_t timerCycles = timeMS / 262 + 1;
    volatile uint8_t timerInitial = (timeMS / timerCycles) * 256 / 262;
    T0_data = 256 - timerInitial;
    prescaler(clk_1024);
    
    for (uint8_t i = 0; i < timerCycles; i++)
    {
        timerCycle();
        T0_data = 256 - timerInitial;
    }
    
    timerStop();
}

void timerdelay(int32_t time)
{
    int32_t timerCycles = time / 256 + 1;
    volatile uint8_t timerInitial = (time / timerCycles);
    T0_data = 256 - timerInitial;
    prescaler(clkSource);
    
    for (uint8_t i = 0; i < timerCycles; i++)
    {
        timerCycle();
        T0_data = 256 - timerInitial;
    }
    
    timerStop();
}
