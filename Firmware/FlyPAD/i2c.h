#ifndef _I2C_
#define _I2C_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "cpu.h"

void init_ios2();
void read_capacitance();
void calculate_capacitance_1();
void calculate_capacitance_2();
void calculate_capacitance_3();
void calculate_capacitance_4();
void calculate_capacitance_5();
void calculate_capacitance_6();
void calculate_capacitance_7();
void calculate_capacitance_8();

#endif