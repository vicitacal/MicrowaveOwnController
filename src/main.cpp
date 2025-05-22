#include "pinconfig.h"
#include "boozerController.h"
#include "ch32v00x.h"
#include <stdio.h>
#include "EncButton.h"
#include "Arduino.h"
#include "TM1652.h"
#include "TM16XX.h"
#include "TM16xxDisplay.h"

#define V(x)( x ? 0xff : 0x00 )

class Program {
	
public:

	Program() {
		_display.begin(true, 1);
		_display.setupDisplay(true, 0, 0);
		_enc.setEncType(EB_STEP4_LOW);
		_enc.setEncReverse(1);

		pinMode(PIN_DETECT_DOOR, INPUT);

		printf("SystemClk:%d\r\n", (int)SystemCoreClock);
		printf("ChipID:%08x\r\n", (int)DBGMCU_GetCHIPID());
	};

	void Run() {

		//_mainBoozer.PlaySequence();
		//_enc.attach([this]() { printf("Count:%lu\r\n", _enc.counter); _display.setDisplayToDecNumber(_enc.counter, _BV(4)); });
		// for (size_t i = 1; i < 15; i++)
		// {
		// 	byte intens = i / 2;
		// 	byte cur = (i - 1) / 2;
		// 	_display.setupDisplay(true, intens, cur);
		// 	_display.setDisplayToDecNumber(intens*10+cur, _BV(4));
		// 	delay(1000);
		// }
		
		while (true) {
			if (_enc.tick()) {
			 	printf("Count:%lu\r\n", _enc.counter);
			 	_display.setDisplayToDecNumber(_enc.counter, V(_enc.holding()));
			}
			//printf("Count:%lu\r\n", _enc.counter);
			//printf("A:%d B:%d C:%d\r\n", GpioReadState(PIN_ENC_A), GpioReadState(PIN_ENC_B), GpioReadState(PIN_ENC_BUT));
		}
	}

	// void callback() {
	// 	printf("callback: ");
	// 	switch (_enc.action()) {
	// 		case EB_PRESS:
	// 			printf("press\r\n");
	// 			break;
	// 		case EB_HOLD:
	// 			printf("hold\r\n");
	// 			break;
	// 		case EB_STEP:
	// 			printf("step\r\n");
	// 			break;
	// 		case EB_RELEASE:
	// 			printf("release\r\n");
	// 			break;
	// 		case EB_CLICK:
	// 			printf("click\r\n");
	// 			break;
	// 		case EB_CLICKS:
	// 			printf("clicks %d\r\n", _enc.getClicks());
	// 			break;
	// 		case EB_TURN:
	// 			printf("turn %d %d %d\r\n", _enc.dir(), _enc.fast(), _enc.pressing());
	// 			break;
	// 		case EB_REL_HOLD:
	// 			printf("release hold\r\n");
	// 			break;
	// 		case EB_REL_HOLD_C:
	// 			printf("release hold clicks %d\r\n", _enc.getClicks());
	// 			break;
	// 		case EB_REL_STEP:
	// 			printf("release step\r\n");
	// 			break;
	// 		case EB_REL_STEP_C:
	// 			printf("release step clicks %d\r\n", _enc.getClicks());
	// 			break;
	// 	}
	// }

	void Click(){
		GpioWriteState(PIN_CTRL_MAG, true);
		delay(200);
		GpioWriteState(PIN_CTRL_MAG, false);
		delay(1000);
	}

private:

	EncButton _enc = EncButton(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BUT, INPUT, INPUT);
	TM1652 _display = TM1652(PIN_DISP_SDA, 4);
	//boozerController _mainBoozer;

};

void* EB_self = nullptr;

int main() {

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	GpioInitAll();
	init();

	auto mainProgram = Program();
	mainProgram.Run();
	while(1);
	
}
