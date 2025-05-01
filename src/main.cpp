#include "pinconfig.h"
#include "boozerController.h"
#include "ch32v00x.h"
#include <stdio.h>
#include "EncButton.h"
#include "TM16XX.h"
#include "Arduino.h"
#include "TM1652.h"
#include "TM16xxDisplay.h"

class Program {
	
public:

	Program() {
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		SystemCoreClockUpdate();
		Delay_Init();
		USART_Printf_Init(115200);
		GpioInitAll();
		GpioPinMode(PIN_CTRL_MAG, OUTPUT);
		_enc.setEncType(EB_STEP4_LOW);
		_enc.setEncReverse(1);
		init();

		printf("SystemClk:%d\r\n", (int)SystemCoreClock);
		printf("ChipID:%08x\r\n", (int)DBGMCU_GetCHIPID());
		//printf("FreeRTOS Kernel Version:%s\r\n",tskKERNEL_VERSION_NUMBER);
	};

	void Run() {
		//_mainBoozer.PlaySequence();
		_enc.attach([this]() { printf("Count:%lu\r\n", _enc.counter); });

		while (true) {
			_enc.tick();
			//printf("Count:%lu\r\n", _enc.counter);
			//printf("A:%d B:%d C:%d\r\n", GpioReadState(PIN_ENC_A), GpioReadState(PIN_ENC_B), GpioReadState(PIN_ENC_BUT));
		}
	}

	void callback() {
		printf("callback: ");
		switch (_enc.action()) {
			case EB_PRESS:
				printf("press\r\n");
				break;
			case EB_HOLD:
				printf("hold\r\n");
				break;
			case EB_STEP:
				printf("step\r\n");
				break;
			case EB_RELEASE:
				printf("release\r\n");
				break;
			case EB_CLICK:
				printf("click\r\n");
				break;
			case EB_CLICKS:
				printf("clicks %d\r\n", _enc.getClicks());
				break;
			case EB_TURN:
				printf("turn %d %d %d\r\n", _enc.dir(), _enc.fast(), _enc.pressing());
				break;
			case EB_REL_HOLD:
				printf("release hold\r\n");
				break;
			case EB_REL_HOLD_C:
				printf("release hold clicks %d\r\n", _enc.getClicks());
				break;
			case EB_REL_STEP:
				printf("release step\r\n");
				break;
			case EB_REL_STEP_C:
				printf("release step clicks %d\r\n", _enc.getClicks());
				break;
		}
	}

	void Click(){
		GpioWriteState(PIN_CTRL_MAG, true);
		delay(200);
		GpioWriteState(PIN_CTRL_MAG, false);
		delay(1000);
	}

private:

	TM1652 _display = TM1652(PIN_DISP_SDA);
	EncButton _enc = EncButton(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BUT, INPUT, INPUT);
	//boozerController _mainBoozer;

};

void* EB_self = nullptr;

int main() {

	auto mainProgram = Program();
	mainProgram.Run();
	while(1);
	
}
