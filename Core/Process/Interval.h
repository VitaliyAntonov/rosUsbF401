//
// Created by vitaliy on 20.04.2022.
//



#ifndef TANK_INTERVAL_H
#define TANK_INTERVAL_H

/** Класс служит для организации периодического вызова обработчиков
 * через заданный интервал времени */

#include "../Inc/preference.h"

typedef enum {
    /** Флаг - Разрешение процесса */
    INTERVAL_PERMIT_ON = 0x01,
}main_process_activate_flags;

/** Параметры одного интервала */
typedef struct {
    /** номер гранулы процесса. При выключенном процессе = 0 */
    uint8_t  numGran = 0;
    /** стартовое значение системного таймера при активации */
    uint32_t startTick;
    /** пауза как количество прерываний(обычно в миллисекундах) */
    uint32_t interval;
    /** указатель на функцию - обработчик при активации */
    void (*functionGran)();
}intervalParam;

/** Массив данных об интервалах */
class ArrIntervalsParam {
public:
    /** количество созданных интервалов для обработки */
    uint8_t count;

    /** массив параметров интервалов */
    intervalParam arrInterval[INTERVALS_QUA];

    /** обработчик прерывания от системного таймера */
    void interruptOnSystemTick();

    /** Проверка флагов активации(номер гранулы) и включение обработчиков */
    void mainIntervalActivate();
};


/**
 * Класс активирует флаги разрешения процессов в основном цикле main
 */
class Interval {
    /** номер данных о интервале в массиве */
    uint8_t intervalID;
public:
    /**
     * Конструктор интервала. Задаёт длительность интервала в миллисекундах
     * @param millisecond   -  интервал в миллисекундах
     * @param foo           -  указатель на функцию - обработчик при активации
     */
    Interval(uint32_t millisecond, void (*foo)());

};


#endif //TANK_INTERVAL_H
