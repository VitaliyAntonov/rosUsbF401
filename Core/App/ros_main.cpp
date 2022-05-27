#include "ros_main.h"
#include "../Inc/main.h"

#include "../RosLibs/ros.h"
#include "../RosLibs/std_msgs/String.h"
#include "../RosLibs/sensor_msgs/Imu.h"


#include "../Process/Interval.h"

#include "../logger/Logger.hpp"

#include "../Inc/preference.h"


void receiverCallback(const std_msgs::String & msg);
void ledToggle();
void linkSpinOnce();
void txLoggerInterval();


/** массив данных об интервалах */
extern ArrIntervalsParam arrIP;

extern Logger mLog;

/** узел ROS */
ros::NodeHandle nh;

/** Объекты класса интервал для функций основного цикла
 * Функция будет вызываться каждые заданный интервал в миллисекундах
 * из loop() через arrIP.mainIntervalActivate()
 * посредством указателя на функцию */

//Interval iTxLogBuffer(LOG_UART_TX_DMA_TIMEOUT, txLoggerInterval); // отправка лога

Interval iLedToggle(2000, ledToggle);  // управление светодиодом

Interval iSpinOnce(998, linkSpinOnce);  // основной отклик на ROS


/** Публикатор */
std_msgs::String str_msg;
ros::Publisher chatter("kek", &str_msg);
char hello[] = "Hello world!";

// Подписчик
/** Из обобщённого шаблона подписчика формируем объект подписчика для типа String */
ros::Subscriber <std_msgs::String> rec("lol", receiverCallback, 1);

/** Обратный вызов при приёме сообщения */
void receiverCallback(const std_msgs::String & msg){
/** Здесь код выполняемый при получении сообщения  */
  chatter.publish(&msg);
}

void ledToggle(){
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

  str_msg.data = hello;
  chatter.publish(&str_msg);

//  char str_tx[] = "USB == Hello World\r\n";
//
//  CDC_Transmit_FS((unsigned char*)str_tx, strlen(str_tx));

//  log_string(USB == Hello World - test message\r\n)

}

void txLoggerInterval(){
  mLog.transmitLogBuffer(); // отправка буфера лога в классе интервал
}

void linkSpinOnce(){
  nh.spinOnce();
}

/** Инициализация */
void setup(void)
{
  nh.initNode();

  nh.advertise(chatter);  // инициализация издателя
  nh.subscribe(rec);      // инициализация подписчика
  
}


void loop(void)
{
	
//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//
//	str_msg.data = hello;
//  chatter.publish(&str_msg);
//
//  nh.spinOnce();
//	HAL_Delay(1000);

  /** класс Interval проверка активации и вызов обработчиков */
  arrIP.mainIntervalActivate();

}
