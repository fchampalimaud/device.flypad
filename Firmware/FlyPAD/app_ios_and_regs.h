#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// DI0            Description: Digital Input 0
// DI1            Description: Digital Input 1

#define read_DI0 read_io(PORTB, 0)      // DI0
#define read_DI1 read_io(PORTC, 0)      // DI1

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// DO0            Description: Output DO0
// DO1            Description: Output DO1
// DO2            Description: Output DO2
// DO3            Description: Output DO3
// SCL            Description: I2C SCL line
// SDA11          Description: I2C SDA line - Arena 1 Sensor 1
// SDA12          Description: I2C SDA line - Arena 1 Sensor 2
// SDA13          Description: I2C SDA line - Arena 1 Sensor 3
// SDA14          Description: I2C SDA line - Arena 1 Sensor 4
// SDA21          Description: I2C SDA line - Arena 2 Sensor 1
// SDA22          Description: I2C SDA line - Arena 2 Sensor 2
// SDA23          Description: I2C SDA line - Arena 2 Sensor 3
// SDA24          Description: I2C SDA line - Arena 2 Sensor 4
// SDA31          Description: I2C SDA line - Arena 3 Sensor 1
// SDA32          Description: I2C SDA line - Arena 3 Sensor 2
// SDA33          Description: I2C SDA line - Arena 3 Sensor 3
// SDA34          Description: I2C SDA line - Arena 3 Sensor 4
// SDA41          Description: I2C SDA line - Arena 4 Sensor 1
// SDA42          Description: I2C SDA line - Arena 4 Sensor 2
// SDA43          Description: I2C SDA line - Arena 4 Sensor 3
// SDA44          Description: I2C SDA line - Arena 4 Sensor 4
// SDA51          Description: I2C SDA line - Arena 5 Sensor 1
// SDA52          Description: I2C SDA line - Arena 5 Sensor 2
// SDA53          Description: I2C SDA line - Arena 5 Sensor 3
// SDA54          Description: I2C SDA line - Arena 5 Sensor 4
// SDA61          Description: I2C SDA line - Arena 6 Sensor 1
// SDA62          Description: I2C SDA line - Arena 6 Sensor 2
// SDA63          Description: I2C SDA line - Arena 6 Sensor 3
// SDA64          Description: I2C SDA line - Arena 6 Sensor 4
// SDA71          Description: I2C SDA line - Arena 7 Sensor 1
// SDA72          Description: I2C SDA line - Arena 7 Sensor 2
// SDA73          Description: I2C SDA line - Arena 7 Sensor 3
// SDA74          Description: I2C SDA line - Arena 7 Sensor 4
// SDA81          Description: I2C SDA line - Arena 8 Sensor 1
// SDA82          Description: I2C SDA line - Arena 8 Sensor 2
// SDA83          Description: I2C SDA line - Arena 8 Sensor 3
// SDA84          Description: I2C SDA line - Arena 8 Sensor 4

/* DO0 */
#define set_DO0 set_io(PORTH, 0)
#define clr_DO0 clear_io(PORTH, 0)
#define tgl_DO0 toggle_io(PORTH, 0)
#define read_DO0 read_io(PORTH, 0)

/* DO1 */
#define set_DO1 set_io(PORTH, 1)
#define clr_DO1 clear_io(PORTH, 1)
#define tgl_DO1 toggle_io(PORTH, 1)
#define read_DO1 read_io(PORTH, 1)

/* DO2 */
#define set_DO2 set_io(PORTH, 2)
#define clr_DO2 clear_io(PORTH, 2)
#define tgl_DO2 toggle_io(PORTH, 2)
#define read_DO2 read_io(PORTH, 2)

/* DO3 */
#define set_DO3 set_io(PORTH, 3)
#define clr_DO3 clear_io(PORTH, 3)
#define tgl_DO3 toggle_io(PORTH, 3)
#define read_DO3 read_io(PORTH, 3)

/* SCL */
#define set_SCL set_io(PORTE, 1)
#define clr_SCL clear_io(PORTE, 1)
#define tgl_SCL toggle_io(PORTE, 1)
#define read_SCL read_io(PORTE, 1)

/* SDA11 */
#define set_SDA11 set_io(PORTD, 0)
#define clr_SDA11 clear_io(PORTD, 0)
#define tgl_SDA11 toggle_io(PORTD, 0)
#define read_SDA11 read_io(PORTD, 0)

/* SDA12 */
#define set_SDA12 set_io(PORTD, 1)
#define clr_SDA12 clear_io(PORTD, 1)
#define tgl_SDA12 toggle_io(PORTD, 1)
#define read_SDA12 read_io(PORTD, 1)

/* SDA13 */
#define set_SDA13 set_io(PORTD, 2)
#define clr_SDA13 clear_io(PORTD, 2)
#define tgl_SDA13 toggle_io(PORTD, 2)
#define read_SDA13 read_io(PORTD, 2)

/* SDA14 */
#define set_SDA14 set_io(PORTD, 3)
#define clr_SDA14 clear_io(PORTD, 3)
#define tgl_SDA14 toggle_io(PORTD, 3)
#define read_SDA14 read_io(PORTD, 3)

/* SDA21 */
#define set_SDA21 set_io(PORTD, 4)
#define clr_SDA21 clear_io(PORTD, 4)
#define tgl_SDA21 toggle_io(PORTD, 4)
#define read_SDA21 read_io(PORTD, 4)

/* SDA22 */
#define set_SDA22 set_io(PORTD, 5)
#define clr_SDA22 clear_io(PORTD, 5)
#define tgl_SDA22 toggle_io(PORTD, 5)
#define read_SDA22 read_io(PORTD, 5)

/* SDA23 */
#define set_SDA23 set_io(PORTD, 6)
#define clr_SDA23 clear_io(PORTD, 6)
#define tgl_SDA23 toggle_io(PORTD, 6)
#define read_SDA23 read_io(PORTD, 6)

/* SDA24 */
#define set_SDA24 set_io(PORTD, 7)
#define clr_SDA24 clear_io(PORTD, 7)
#define tgl_SDA24 toggle_io(PORTD, 7)
#define read_SDA24 read_io(PORTD, 7)

/* SDA31 */
#define set_SDA31 set_io(PORTE, 4)
#define clr_SDA31 clear_io(PORTE, 4)
#define tgl_SDA31 toggle_io(PORTE, 4)
#define read_SDA31 read_io(PORTE, 4)

/* SDA32 */
#define set_SDA32 set_io(PORTE, 5)
#define clr_SDA32 clear_io(PORTE, 5)
#define tgl_SDA32 toggle_io(PORTE, 5)
#define read_SDA32 read_io(PORTE, 5)

/* SDA33 */
#define set_SDA33 set_io(PORTE, 6)
#define clr_SDA33 clear_io(PORTE, 6)
#define tgl_SDA33 toggle_io(PORTE, 6)
#define read_SDA33 read_io(PORTE, 6)

/* SDA34 */
#define set_SDA34 set_io(PORTE, 7)
#define clr_SDA34 clear_io(PORTE, 7)
#define tgl_SDA34 toggle_io(PORTE, 7)
#define read_SDA34 read_io(PORTE, 7)

/* SDA41 */
#define set_SDA41 set_io(PORTF, 4)
#define clr_SDA41 clear_io(PORTF, 4)
#define tgl_SDA41 toggle_io(PORTF, 4)
#define read_SDA41 read_io(PORTF, 4)

/* SDA42 */
#define set_SDA42 set_io(PORTF, 5)
#define clr_SDA42 clear_io(PORTF, 5)
#define tgl_SDA42 toggle_io(PORTF, 5)
#define read_SDA42 read_io(PORTF, 5)

/* SDA43 */
#define set_SDA43 set_io(PORTF, 6)
#define clr_SDA43 clear_io(PORTF, 6)
#define tgl_SDA43 toggle_io(PORTF, 6)
#define read_SDA43 read_io(PORTF, 6)

/* SDA44 */
#define set_SDA44 set_io(PORTF, 7)
#define clr_SDA44 clear_io(PORTF, 7)
#define tgl_SDA44 toggle_io(PORTF, 7)
#define read_SDA44 read_io(PORTF, 7)

/* SDA51 */
#define set_SDA51 set_io(PORTH, 4)
#define clr_SDA51 clear_io(PORTH, 4)
#define tgl_SDA51 toggle_io(PORTH, 4)
#define read_SDA51 read_io(PORTH, 4)

/* SDA52 */
#define set_SDA52 set_io(PORTH, 5)
#define clr_SDA52 clear_io(PORTH, 5)
#define tgl_SDA52 toggle_io(PORTH, 5)
#define read_SDA52 read_io(PORTH, 5)

/* SDA53 */
#define set_SDA53 set_io(PORTH, 6)
#define clr_SDA53 clear_io(PORTH, 6)
#define tgl_SDA53 toggle_io(PORTH, 6)
#define read_SDA53 read_io(PORTH, 6)

/* SDA54 */
#define set_SDA54 set_io(PORTH, 7)
#define clr_SDA54 clear_io(PORTH, 7)
#define tgl_SDA54 toggle_io(PORTH, 7)
#define read_SDA54 read_io(PORTH, 7)

/* SDA61 */
#define set_SDA61 set_io(PORTJ, 0)
#define clr_SDA61 clear_io(PORTJ, 0)
#define tgl_SDA61 toggle_io(PORTJ, 0)
#define read_SDA61 read_io(PORTJ, 0)

/* SDA62 */
#define set_SDA62 set_io(PORTJ, 1)
#define clr_SDA62 clear_io(PORTJ, 1)
#define tgl_SDA62 toggle_io(PORTJ, 1)
#define read_SDA62 read_io(PORTJ, 1)

/* SDA63 */
#define set_SDA63 set_io(PORTJ, 2)
#define clr_SDA63 clear_io(PORTJ, 2)
#define tgl_SDA63 toggle_io(PORTJ, 2)
#define read_SDA63 read_io(PORTJ, 2)

/* SDA64 */
#define set_SDA64 set_io(PORTJ, 3)
#define clr_SDA64 clear_io(PORTJ, 3)
#define tgl_SDA64 toggle_io(PORTJ, 3)
#define read_SDA64 read_io(PORTJ, 3)

/* SDA71 */
#define set_SDA71 set_io(PORTA, 0)
#define clr_SDA71 clear_io(PORTA, 0)
#define tgl_SDA71 toggle_io(PORTA, 0)
#define read_SDA71 read_io(PORTA, 0)

/* SDA72 */
#define set_SDA72 set_io(PORTA, 1)
#define clr_SDA72 clear_io(PORTA, 1)
#define tgl_SDA72 toggle_io(PORTA, 1)
#define read_SDA72 read_io(PORTA, 1)

/* SDA73 */
#define set_SDA73 set_io(PORTA, 2)
#define clr_SDA73 clear_io(PORTA, 2)
#define tgl_SDA73 toggle_io(PORTA, 2)
#define read_SDA73 read_io(PORTA, 2)

/* SDA74 */
#define set_SDA74 set_io(PORTA, 3)
#define clr_SDA74 clear_io(PORTA, 3)
#define tgl_SDA74 toggle_io(PORTA, 3)
#define read_SDA74 read_io(PORTA, 3)

/* SDA81 */
#define set_SDA81 set_io(PORTB, 4)
#define clr_SDA81 clear_io(PORTB, 4)
#define tgl_SDA81 toggle_io(PORTB, 4)
#define read_SDA81 read_io(PORTB, 4)

/* SDA82 */
#define set_SDA82 set_io(PORTB, 5)
#define clr_SDA82 clear_io(PORTB, 5)
#define tgl_SDA82 toggle_io(PORTB, 5)
#define read_SDA82 read_io(PORTB, 5)

/* SDA83 */
#define set_SDA83 set_io(PORTB, 6)
#define clr_SDA83 clear_io(PORTB, 6)
#define tgl_SDA83 toggle_io(PORTB, 6)
#define read_SDA83 read_io(PORTB, 6)

/* SDA84 */
#define set_SDA84 set_io(PORTB, 7)
#define clr_SDA84 clear_io(PORTB, 7)
#define tgl_SDA84 toggle_io(PORTB, 7)
#define read_SDA84 read_io(PORTB, 7)

/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
    uint8_t REG_ENABLE_ACQUISITION;
    uint16_t REG_CAPACITANCE_VALUES[64];
    uint8_t REG_DIGITAL_INPUT_STATE;
    uint8_t REG_DIGITAL_OUTPUT_SET;
    uint8_t REG_DIGITAL_OUTPUT_CLEAR;
    uint8_t REG_DIGITAL_OUTPUT_TOGGLE;
    uint8_t REG_DIGITAL_OUTPUT_STATE;
    uint8_t REG_ENABLE_EVENTS;
} AppRegs;

/************************************************************************/
/* Registers' address                                                   */
/************************************************************************/
/* Registers */
#define ADD_REG_ENABLE_ACQUISITION       32 // U8     Starts or stops the data acquisition in all channels.
#define ADD_REG_CAPACITANCE_VALUES       33 // U16    Value of ADC capacitance values for each channel (2 values per channel).
#define ADD_REG_DIGITAL_INPUT_STATE      34 // U8     State of the digital inputs.
#define ADD_REG_DIGITAL_OUTPUT_SET       35 // U8     Set the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_CLEAR     36 // U8     Clears the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_TOGGLE    37 // U8     Toggles the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_STATE     38 // U8     Write the state of all digital output lines.
#define ADD_REG_ENABLE_EVENTS            39 // U8     Specifies the active events in the device.

/************************************************************************/
/* FlyPAD registers' memory limits                                      */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x27
#define APP_NBYTES_OF_REG_BANK              135

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/
#define B_DI0                 (1<<0)       // 
#define B_DI1                 (1<<1)       // 
#define B_DO0                 (1<<0)       // 
#define B_DO1                 (1<<1)       // 
#define B_DO2                 (1<<2)       // 
#define B_DO3                 (1<<3)       // 
#define B_DIGITAL_INPUTS      (1<<0)       // 

#endif /* _APP_REGS_H_ */