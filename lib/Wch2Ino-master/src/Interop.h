#define GpioOf( pin ) ((GPIO_TypeDef *)(GPIOA_BASE + 0x400 * ((pin)>>4)))

#define GpioInitAll() { RCC->APB2PCENR |= ( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD ); }
#define GpioPinMode( pin, mode ) { GpioOf(pin)->CFGLR = (GpioOf(pin)->CFGLR & (~(0xf<<(4*((pin)&0xf))))) | ((mode)<<(4*((pin)&0xf))); }
#define GpioReadState( pin ) ((int)((GpioOf(pin)->INDR >> ((pin)&0xf)) & 1))
#define GpioWriteState( pin, value ) { GpioOf( pin )->BSHR = 1<<((!(value))*16 + ((pin) & 0xf)); }