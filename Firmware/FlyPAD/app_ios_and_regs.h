#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// DI0            Description: Digital Input 0
// DI1            Description: Digital Input 1
// SDA11          Description: I2C SDA line - Arena 1 Sensor 1
// SDA12          Description: I2C SDA line - Arena 1 Sensor 2

#define read_DI0 read_io(PORTB, 0)      // DI0
#define read_DI1 read_io(PORTC, 0)      // DI1
#define read_SDA11 read_io(PORTD, 0)    // SDA11
#define read_SDA12 read_io(PORTD, 1)    // SDA12

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// DO0            Description: Output DO0
// DO1            Description: Output DO1
// DO2            Description: Output DO2
// DO3            Description: Output DO3

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

/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
    uint8_t REG_ENABLE_ACQUISITION;
    uint16_t REG_CAPACITANCE_VALUES[64];
    uint8_t REG_DI0_STATE;
    uint8_t REG_DI1_STATE;
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
#define ADD_REG_DI0_STATE                34 // U8     State of the digital input pin 0.
#define ADD_REG_DI1_STATE                35 // U8     State of the digital input pin 1.
#define ADD_REG_DIGITAL_OUTPUT_SET       36 // U8     Set the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_CLEAR     37 // U8     Clears the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_TOGGLE    38 // U8     Toggles the specified digital output lines.
#define ADD_REG_DIGITAL_OUTPUT_STATE     39 // U8     Write the state of all digital output lines.
#define ADD_REG_ENABLE_EVENTS            40 // U8     Specifies the active events in the device.

/************************************************************************/
/* FlyPAD registers' memory limits                                      */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x28
#define APP_NBYTES_OF_REG_BANK              136

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/
#define B_DO0                    (1<<0)       // 
#define B_DO1                    (1<<1)       // 
#define B_DO2                    (1<<2)       // 
#define B_DO3                    (1<<3)       // 
#define MSK_DIGITAL_STATE        0x01         // 
#define GM_DIGITAL_STATE_LOW     0x00         // 
#define GM_DIGITAL_STATE_HIGH    0x01         // 

#endif /* _APP_REGS_H_ */