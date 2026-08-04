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

    /* Configure input interrupts */
    io_set_int(&PORTB, INT_LEVEL_LOW, 0, (1<<0), false);                 // DI0
    io_set_int(&PORTC, INT_LEVEL_LOW, 0, (1<<0), false);                 // DI1

    /* Configure output pins */
    io_pin2out(&PORTH, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO0
    io_pin2out(&PORTH, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO1
    io_pin2out(&PORTH, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO2
    io_pin2out(&PORTH, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // DO3
    io_pin2out(&PORTE, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SCL
    io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA11
    io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA12
    io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA13
    io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA14
    io_pin2out(&PORTD, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA21
    io_pin2out(&PORTD, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA22
    io_pin2out(&PORTD, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA23
    io_pin2out(&PORTD, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA24
    io_pin2out(&PORTE, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA31
    io_pin2out(&PORTE, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA32
    io_pin2out(&PORTE, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA33
    io_pin2out(&PORTE, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA34
    io_pin2out(&PORTF, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA41
    io_pin2out(&PORTF, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA42
    io_pin2out(&PORTF, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA43
    io_pin2out(&PORTF, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA44
    io_pin2out(&PORTH, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA51
    io_pin2out(&PORTH, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA52
    io_pin2out(&PORTH, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA53
    io_pin2out(&PORTH, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA54
    io_pin2out(&PORTJ, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA61
    io_pin2out(&PORTJ, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA62
    io_pin2out(&PORTJ, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA63
    io_pin2out(&PORTJ, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA64
    io_pin2out(&PORTA, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA71
    io_pin2out(&PORTA, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA72
    io_pin2out(&PORTA, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA73
    io_pin2out(&PORTA, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA74
    io_pin2out(&PORTB, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA81
    io_pin2out(&PORTB, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA82
    io_pin2out(&PORTB, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA83
    io_pin2out(&PORTB, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // SDA84

    /* Initialize output pins */
    clr_DO0;
    clr_DO1;
    clr_DO2;
    clr_DO3;
    clr_SCL;
    clr_SDA11;
    clr_SDA12;
    clr_SDA13;
    clr_SDA14;
    clr_SDA21;
    clr_SDA22;
    clr_SDA23;
    clr_SDA24;
    clr_SDA31;
    clr_SDA32;
    clr_SDA33;
    clr_SDA34;
    clr_SDA41;
    clr_SDA42;
    clr_SDA43;
    clr_SDA44;
    clr_SDA51;
    clr_SDA52;
    clr_SDA53;
    clr_SDA54;
    clr_SDA61;
    clr_SDA62;
    clr_SDA63;
    clr_SDA64;
    clr_SDA71;
    clr_SDA72;
    clr_SDA73;
    clr_SDA74;
    clr_SDA81;
    clr_SDA82;
    clr_SDA83;
    clr_SDA84;
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
    (uint8_t*)(app_regs.REG_CAPACITANCE_VALUES),
    (uint8_t*)(&app_regs.REG_DI0_STATE),
    (uint8_t*)(&app_regs.REG_DI1_STATE),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_SET),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_CLEAR),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_TOGGLE),
    (uint8_t*)(&app_regs.REG_DIGITAL_OUTPUT_STATE),
    (uint8_t*)(&app_regs.REG_ENABLE_EVENTS)
};