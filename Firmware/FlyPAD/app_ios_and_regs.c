#include <avr/io.h>
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"

extern AppRegs app_regs;

/************************************************************************/
/* Configure and initialize IOs                                         */
/************************************************************************/
void init_ios(void)
{
    /* Configure input pins */
    io_pin2in(&PORTB, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // DI0
    io_pin2in(&PORTC, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // DI1
    io_pin2in(&PORTD, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // SDA11
    io_pin2in(&PORTD, 1, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // SDA12

    /* Configure input interrupts */
    io_set_int(&PORTB, INT_LEVEL_LOW, 0, (1<<0), false);                 // DI0
    io_set_int(&PORTC, INT_LEVEL_LOW, 0, (1<<0), false);                 // DI1

    /* Configure output pins */
    io_pin2out(&PORTH, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO0
    io_pin2out(&PORTH, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO1
    io_pin2out(&PORTH, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO2
    io_pin2out(&PORTH, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO3

    /* Initialize output pins */
    clr_DO0;
    clr_DO1;
    clr_DO2;
    clr_DO3;
}

/************************************************************************/
/* Registers' stuff                                                     */
/************************************************************************/
AppRegs app_regs;

uint8_t app_regs_type[] = {
    TYPE_U8,
    TYPE_U16,
    TYPE_U8,
    TYPE_U8,
    TYPE_U8,
    TYPE_U8,
    TYPE_U8,
    TYPE_U8,
    TYPE_U8
};

uint16_t app_regs_n_elements[] = {
    1,
    64,
    1,
    1,
    1,
    1,
    1,
    1,
    1
};

uint8_t *app_regs_pointer[] = {
    (uint8_t*)(&app_regs.REG_ENABLE_ACQUISITION),
    (uint8_t*)(&app_regs.REG_CAPACITANCE_VALUES),
    (uint8_t*)(&app_regs.REG_DI0_STATE),
    (uint8_t*)(&app_regs.REG_DI1_STATE),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_SET),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_CLEAR),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_TOGGLE),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_STATE),
    (uint8_t*)(&app_regs.REG_ENABLE_EVENTS)
};