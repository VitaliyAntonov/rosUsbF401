//
// Created by vitaliy on 20.04.2022.
//

#include "Interval.h"

/** Класс служит для организации периодического вызова обработчиков
 * через заданный интервал времени */

ArrIntervalsParam arrIP;  // массив данных об интервалах



/**
 * Конструктор интервала. Задаёт длительность интервала в миллисекундах
 * @param millisecond   -  интервал в миллисекундах
 * @param foo           -  указатель на функцию - обработчик при активации
 */
Interval::Interval(uint32_t millisecond, void (*foo)() ){
  if(arrIP.count < INTERVALS_QUA){        // проверка количества интервалов

    /** объект с параметрами интервала */
    intervalParam ip;

    /** инициализация длительности интервала */
    ip.interval = millisecond;
    /** фиксация начального значения системного таймера */
    ip.startTick = HAL_GetTick();
    /** фиксируем указатель на функцию - обработчик при активации */
    ip.functionGran = foo;

    /** добавляем интервал в массив интервалов */
    arrIP.arrInterval[arrIP.count] = ip;

    /** фиксируем номер параметров данного интервала в массив  */
    intervalID = arrIP.count;

    /** увеличиваем номер в массиве для следующего экземпляра интервала */
    arrIP.count += 1;
  }
  else{
    /** === Ошибка. Превышено максимальное количество заданных интервалов === */
  }

}




/** обработчик прерывания от системного таймера */
void ArrIntervalsParam::interruptOnSystemTick(){

  /** Если созданы интервалы */
  if(arrIP.count > 0){

    /** обход всех интервалов */
    for(uint8_t cnt = 0; cnt < arrIP.count; cnt++){

      if((HAL_GetTick() - arrIP.arrInterval[cnt].startTick) >= arrIP.arrInterval[cnt].interval){
        /** Интервал закончен */
        /** активируем флаг разрешения обработки */
        arrIP.arrInterval[cnt].numGran = INTERVAL_PERMIT_ON;
        /** перезагружаем стартовое значение для следующего срабатывания */
        arrIP.arrInterval[cnt].startTick = HAL_GetTick();
      }
    }
  }
}

/** Проверка флагов активации(номер гранулы) и включение обработчиков */
void ArrIntervalsParam::mainIntervalActivate(){
  /** Если созданы интервалы */
  if(arrIP.count > 0){
    /** обход всех интервалов */
    for(uint8_t cnt = 0; cnt < arrIP.count; cnt++){
      /** проверка флага активации */
      if(arrIP.arrInterval[cnt].numGran != 0){
        /** вызов функции - обработчика */
        arrIP.arrInterval[cnt].functionGran();
        /** сброс флага активации */
        arrIP.arrInterval[cnt].numGran = 0;
      }
    }
  }
}

