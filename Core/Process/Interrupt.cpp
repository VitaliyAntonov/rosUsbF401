//
// Created by vitaliy on 03.04.2022.
//

#include "main.h"
#include "Interrupt.hpp"
#include "../logger/Logger.hpp"
#include "stm32f4xx_it.h"
#include "../Inc/preference.h"
#include "Interval.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern Logger mLog;
extern ArrIntervalsParam arrIP;  // массив данных об интервалах


/** Проверка лога внутри прерывания */
uint16_t pauseItCount = 0;
uint8_t itMess[] = "======InterruptTestMessage=====\r\n";
void logItTest(void){
  if(pauseItCount > 99){
    mLog.messageLogIT(itMess, sizeof(itMess) - 1);
    pauseItCount = 0;
  }
  pauseItCount += 1;
}


/**
 * Прерывание сравнения TIM1_CH1 для отправки логов из кольцевого буфера в UART через DMA
 */
void TIM1_CC_IRQHandler(void)
{
//  logItTest(); // Проверка отправки лога в прерывании

//  /** Прерывание сравнения TIM1_CH1 для отправки логов из кольцевого буфера в UART через DMA */
//  if ((htim1.Instance->SR & TIM_SR_CC1IF) != 0){
//    /** следующий вход в прерывание через 1000 микросекунд */
//    htim1.Instance->CCR2 = htim1.Instance->CCR2 + LOG_UART_TX_DMA_TIMEOUT;
//
//
//
//    /** вывод лога в UART через DMA  Отправка накопленных в кольцевом буфере сообщений */
//    mLog.logToDmaUart_IT();
//  }

  HAL_TIM_IRQHandler(&htim1);

}


/** Прерывание от системного таймера */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  arrIP.interruptOnSystemTick();

  /* USER CODE END SysTick_IRQn 1 */
}




