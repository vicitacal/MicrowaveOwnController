
#include "ch32v00x.h"
#include "ch32v00x_misc.h"
#include "pinconfig.h"
#include "debug.h"
#include <stdio.h>

class boozerController {

public:

    boozerController() {
        InitGpio();
    }

    void PlaySequence() {
        InitTimmer(550);
        for (uint16_t i = 550; i < 1200; i+= 50)
        {
            SetFrequency(i);
            Delay_Ms(100);	
        }
        SetFrequency(0);
    }

private:

    void InitTimmer(uint16_t period) {
        if (_initialized) { return; }
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        TIM_TimeBaseStructure.TIM_Period = period - 1;
        TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

        TIM_OCInitTypeDef TIM_OCInitStructure;
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_Pulse = 0x0200;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OC1Init(TIM1, &TIM_OCInitStructure);

        TIM_Cmd(TIM1, ENABLE);
        TIM_CtrlPWMOutputs(TIM1, ENABLE);
        _initialized = true;
    }

    void InitGpio(void) {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }

    void SetFrequency(uint16_t frequency) {
        if (frequency > 0) {
            TIM1->ATRLR = frequency - 1;
            TIM_CtrlPWMOutputs(TIM1, ENABLE);
        } else {
            TIM_CtrlPWMOutputs(TIM1, DISABLE);
        }
    }

    bool _initialized = false;

};