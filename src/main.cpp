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
		GpioInitAll();
		init();

		printf("SystemClk:%d\r\n", (int)SystemCoreClock);
		printf("ChipID:%08x\r\n", (int)DBGMCU_GetCHIPID());
		//printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);
	};

	void Run() {
		//_mainBoozer.PlaySequence();
		//_enc.attach([this]() {printf("Count:%lu\r\n", _enc.counter);});
		// GpioPinMode(PIN_ENC_A, INPUT);
		// GpioPinMode(PIN_ENC_B, INPUT);
		// GpioPinMode(PIN_ENC_BUT, INPUT);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		while (true) {
			printf("A:%d B:%d C:%d\r\n", GpioReadState(PIN_ENC_A), GpioReadState(PIN_ENC_B), GPIO_ReadInputDataBit(GPIOD, 3));
		}
	}

	void Click(){
		GpioWriteState(PIN_CTRL_ATTACH, true);
		delay(200);
		GpioWriteState(PIN_CTRL_ATTACH, false);
		delay(1000);
	}

private:

	//EncButton _enc = EncButton(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BUT, INPUT, INPUT);
	//boozerController _mainBoozer;

};

void* EB_self = nullptr;

int main() {

	auto mainProgram = Program();
	mainProgram.Run();
	while(1);
	
}
