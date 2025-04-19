#include "pinconfig.h"
#include "boozerController.h"
#include "ch32v00x.h"
#include "debug.h"
#include <stdio.h>
#include "EncButton.h"
#include "TM16XX.h"

class Program {
	
public:

	Program() {
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		SystemCoreClockUpdate();
		Delay_Init();
		USART_Printf_Init(115200);
		_mainBoozer = boozerController();
		_enc = EncButton();

		printf("SystemClk:%d\r\n", (int)SystemCoreClock);
		printf("ChipID:%08x\r\n", (int)DBGMCU_GetCHIPID());
		//printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);
	};

	void Run() {
		//_mainBoozer.PlaySequence();
	}

private:

	EncButton _enc;
	boozerController _mainBoozer;

};

int main() {
	
	auto mainProgram = Program();
	mainProgram.Run();
	while (1);
	
}
