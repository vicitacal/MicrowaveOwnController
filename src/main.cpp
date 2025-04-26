#include "pinconfig.h"
#include "boozerController.h"
#include "ch32v00x.h"
#include "debug.h"
#include <stdio.h>
#include "EncButton.h"
#include "TM16XX.h"
#include "Arduino.h"

class Program {
	
public:

	Program() {
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		SystemCoreClockUpdate();
		Delay_Init();
		USART_Printf_Init(115200);
		// GpioInitAll();
		// GpioPinMode(PIN_CTRL_ATTACH, OUTPUT);
		
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_InitStruct;
		TIM_InitStruct.TIM_Prescaler = SystemCoreClock / 1000000 - 1;
		TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_InitStruct.TIM_Period = 999;
		TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_InitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		//NVIC_EnableIRQ(TIM2_IRQn);
		TIM_Cmd(TIM2, ENABLE);

		printf("SystemClk:%d\r\n", (int)SystemCoreClock);
		printf("ChipID:%08x\r\n", (int)DBGMCU_GetCHIPID());
		//printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);
	};

	void Run() {
		//_mainBoozer.PlaySequence();
		bool state = true;
		while (true) {
			GpioWriteState(PIN_CTRL_ATTACH, state);
			delay(1000);
			printf("Millis:%lu\r\n", millis());
			state = !state;
		}
	}

	void Click(){
		GpioWriteState(PIN_CTRL_ATTACH, true);
		delay(200);
		GpioWriteState(PIN_CTRL_ATTACH, false);
		delay(1000);
	}

private:

	//EncButton _enc;
	//boozerController _mainBoozer;

};

int main() {

	auto mainProgram = Program();
	mainProgram.Run();
	while(1);
	
}
