//
// Created by vitaliy on 29.03.2022.
//

#ifndef C60APP_PREFERENCE_H
#define C60APP_PREFERENCE_H

#include "main.h"
#include "../../Drivers/CMSIS/Include/cmsis_compiler.h"
#include "../RosLibs//std_msgs/Float32.h"


extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;


/** ====================  Настройки логгера  =================== */
/** размер буфера лога для отправки в UART_TX */
#define LOG_TX_SIZE  1024  //
/** размер буфера лога создаваемого в прерывании */
#define LOG_IT_SIZE  512

/** Интервал в миллисекундах между отправками ЛОГА в UART через DMA */
#define LOG_UART_TX_DMA_TIMEOUT 10

/** uart привязанный к логгеру */
#define UART_LOGGER huart2
/** DMA привязанный к UART TX логгера */
#define DMA_TX_LOGGER hdma_usart2_tx
/** DMA привязанный к UART RX логгера */
#define DMA_RX_LOGGER hdma_usart2_rx


/** ========= Максимальное количество заданных интервалов ========= */
#define INTERVALS_QUA 10

/** ========= Тип сообщения ROS для управления мощностью двигателей ===== */
#define PWR_MOTOR_MSG std_msgs::Float32


/** ===== Управление мощностью двигателей ====== */
/** количество двигателей */
#define MOTORS_QUA 4
/** Значение в регистре ШИМ при максимальной мощности двигателя */
#define MAX_PWM_PULSE_COUNT 1000
/** Максимально возможное ускорение(увеличение мощности) двигателя <единиц мощности в миллисекунду> */
#define MAX_ACCELERATION 10
/** Длительность в миллисекундах одного шага при изменении мощности */
#define STEP_POWER_CONTROL 5
/** Шаг изменения мощности для выбранных настроек */
#define INCREMENT_PWR_VALUE  50

/** =========== Энкодеры двигателей ============ */
/** Интервал между считываниями состояния энкодеров в миллисекундах */
#define ENCODER_CONTROL_STEP 100
/** Таймеры энкодеров */
#define ENCODER_TIM_M0 htim2
#define ENCODER_TIM_M1 htim3
#define ENCODER_TIM_M2 htim4
#define ENCODER_TIM_M3 htim5

/** Тип сообщения о скорости двигателей */
#define SPEED_MSG std_msgs::Float32

#endif //C60APP_PREFERENCE_H
