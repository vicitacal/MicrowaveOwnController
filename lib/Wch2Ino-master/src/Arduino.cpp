#include "Arduino.h"
#include "ch32v00x.h"
#include "debug.h"

volatile unsigned long milliseconds = 0;

extern "C" void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
extern "C" void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    milliseconds++;
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

void initMillis(void) {

}

void init(void) { initMillis(); }

void initVariant(void) {}

int atexit(void (*func)()) {
  (void)func;
  return 0;
}

void pinMode(uint8_t pin, uint8_t mode) { GpioPinMode(pin, mode); }

void digitalWrite(uint8_t pin, uint8_t val) { GpioWriteState(pin, val); }

int digitalRead(uint8_t pin) { return GpioReadState(pin); }

int analogRead(uint8_t pin) {
  static uint8_t adc_initialized = 0;
  if (!adc_initialized) {
    RCC->APB2PCENR |= RCC_APB2Periph_ADC1;  // Включение тактирования АЦП
    ADC1->CTLR2 |= (1 << 0);   // Включение АЦП (ADC_ON = бит 0 в CTLR2)
    ADC1->CTLR2 &= ~(1 << 1);  // Отключение непрерывного режима (CONT = бит 1)
    ADC1->SAMPTR2 = 0x3FFFF;   // Установка времени выборки (макс. точность)
    adc_initialized = 1;
  }
  ADC1->RSQR3 = pin;
  ADC1->CTLR2 |= ADC_SWSTART;
  while (!(ADC1->STATR & ADC_EOC));
  return ADC1->RDATAR & 0x3FF;
}

void analogReference(uint8_t mode) {}

void analogWrite(uint8_t pin, int val) {}

unsigned long millis(void) { return milliseconds; }

unsigned long micros(void) {
    uint32_t ms;
    uint16_t cnt;
    __disable_irq();
    ms = milliseconds;
    cnt = TIM2->CNT;
    __enable_irq();
    return ms * 1000 + cnt;
}

void delay(unsigned long ms) { Delay_Ms(ms); }

void delayMicroseconds(unsigned int us) { Delay_Us(us); }

uint16_t makeWord(uint16_t w) { return w; }

uint16_t makeWord(byte h, byte l) { return ((uint16_t)h << 8) | l; }

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  unsigned long start = micros();
  unsigned long now;
  while (digitalRead(pin) == state) {
    now = micros();
    if ((now - start) >= timeout) return 0;
  }
  start = micros();
  while (digitalRead(pin) != state) {
    now = micros();
    if ((now - start) >= timeout) return 0;
  }
  start = micros();
  while (digitalRead(pin) == state) {
    now = micros();
    if ((now - start) >= timeout) return 0;
  }

  return micros() - start;
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout) {
  return pulseIn(pin, state, timeout);
}

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {}

void noTone(uint8_t _pin) {}

void randomSeed(unsigned long seed) {
  if (seed != 0) {
    srandom(seed);
  }
}

long random(long howbig) {
  if (howbig == 0) {
    return 0;
  }
  return random() % howbig;
}

long random(long howsmall, long howbig) {
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
  uint8_t data = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    digitalWrite(clockPin, HIGH);

    if (bitOrder == LSBFIRST)
      data |= digitalRead(dataPin) << i;
    else
      data |= digitalRead(dataPin) << (7 - i);

    digitalWrite(clockPin, LOW);
  }

  return data;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder,
              uint8_t val) {
  for (uint8_t i = 0; i < 8; i++) {
    if (bitOrder == LSBFIRST)
      digitalWrite(dataPin, !!(val & (1 << i)));
    else
      digitalWrite(dataPin, !!(val & (1 << (7 - i))));

    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {}

void detachInterrupt(uint8_t interruptNum) {}

void setup(void) {}

void loop(void) {}
