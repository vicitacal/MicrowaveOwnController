/********************************** (C) COPYRIGHT
 ******************************** File Name          : ch32v00x_it.c Author :
 *WCH Version            : V1.0.0 Date               : 2022/08/08 Description :
 *Main Interrupt Service Routines.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include <ch32v00x_it.h>
#include "ch32v00x.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
// void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void) {

}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
__attribute__((interrupt)) void HardFault_Handler(void) {
  uint32_t mcause, mepc;

  __asm volatile ("csrr %0, mcause" : "=r"(mcause));
  __asm volatile ("csrr %0, mepc" : "=r"(mepc));

  printf("HardFault!\r\n");
  printf("MCAUSE = 0x%08lX\r\n", mcause);
  printf("MEPC   = 0x%08lX\r\n", mepc); // <- тут краш

  while (1);
}
