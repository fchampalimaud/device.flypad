#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"
#include "i2c.h"



/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_ENABLE_ACQUISITION,
	&app_read_REG_CAPACITANCE_VALUES,
	&app_read_REG_DIGITAL_INPUT_STATE,
	&app_read_REG_DIGITAL_OUTPUT_SET,
	&app_read_REG_DIGITAL_OUTPUT_CLEAR,
	&app_read_REG_DIGITAL_OUTPUT_TOGGLE,
	&app_read_REG_DIGITAL_OUTPUT_STATE,
	&app_read_REG_ENABLE_EVENTS
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_ENABLE_ACQUISITION,
	&app_write_REG_CAPACITANCE_VALUES,
	&app_write_REG_DIGITAL_INPUT_STATE,
	&app_write_REG_DIGITAL_OUTPUT_SET,
	&app_write_REG_DIGITAL_OUTPUT_CLEAR,
	&app_write_REG_DIGITAL_OUTPUT_TOGGLE,
	&app_write_REG_DIGITAL_OUTPUT_STATE,
	&app_write_REG_ENABLE_EVENTS
};

/************************************************************************/
/* REG_ENABLE_ACQUISITION                                               */
/************************************************************************/
void app_read_REG_ENABLE_ACQUISITION(void) {}

bool app_write_REG_ENABLE_ACQUISITION(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_ENABLE_ACQUISITION = reg;
    return true;
}

/************************************************************************/
/* REG_CAPACITANCE_VALUES                                               */
/************************************************************************/
// This register is an array with 64 positions
void app_read_REG_CAPACITANCE_VALUES(void) {}

bool app_write_REG_CAPACITANCE_VALUES(void *a) { return false; }

/************************************************************************/
/* REG_DIGITAL_INPUT_STATE                                              */
/************************************************************************/
void app_read_REG_DIGITAL_INPUT_STATE(void)
{
	app_regs.REG_DIGITAL_INPUT_STATE = (read_DI0) ? B_DI0 : 0;
	app_regs.REG_DIGITAL_INPUT_STATE |= (read_DI1) ? B_DI1 : 0;
}

bool app_write_REG_DIGITAL_INPUT_STATE(void *a) { return false; }

/************************************************************************/
/* REG_DIGITAL_OUTPUT_SET                                               */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_SET(void) {}

bool app_write_REG_DIGITAL_OUTPUT_SET(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	if (reg & B_DO0) set_DO0;
	if (reg & B_DO1) set_DO1;
	if (reg & B_DO2) set_DO2;
	if (reg & B_DO3) set_DO3;

	app_regs.REG_DIGITAL_OUTPUT_SET = reg;
	app_regs.REG_DIGITAL_OUTPUT_STATE |= reg;

    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_CLEAR                                             */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_CLEAR(void) {}

bool app_write_REG_DIGITAL_OUTPUT_CLEAR(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	if (reg & B_DO0) clr_DO0;
	if (reg & B_DO1) clr_DO1;
	if (reg & B_DO2) clr_DO2;
	if (reg & B_DO3) clr_DO3;

	app_regs.REG_DIGITAL_OUTPUT_CLEAR = reg;
	app_regs.REG_DIGITAL_OUTPUT_STATE &= ~reg;

    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_TOGGLE                                            */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_TOGGLE(void) {}

bool app_write_REG_DIGITAL_OUTPUT_TOGGLE(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	if (reg & B_DO0) tgl_DO0;
	if (reg & B_DO1) tgl_DO1;
	if (reg & B_DO2) tgl_DO2;
	if (reg & B_DO3) tgl_DO3;

	app_regs.REG_DIGITAL_OUTPUT_TOGGLE = reg;
	app_regs.REG_DIGITAL_OUTPUT_STATE ^= reg;

    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_STATE                                             */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_STATE(void)
{
	app_regs.REG_DIGITAL_OUTPUT_STATE = (read_DO0) ? B_DO0 : 0;
	app_regs.REG_DIGITAL_OUTPUT_STATE |= (read_DO1) ? B_DO1 : 0;
	app_regs.REG_DIGITAL_OUTPUT_STATE |= (read_DO2) ? B_DO2 : 0;
	app_regs.REG_DIGITAL_OUTPUT_STATE |= (read_DO3) ? B_DO3 : 0;
}

bool app_write_REG_DIGITAL_OUTPUT_STATE(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	if (reg & B_DO0) set_DO0; else clr_DO0;
	if (reg & B_DO1) set_DO1; else clr_DO1;
	if (reg & B_DO2) set_DO2; else clr_DO2;
	if (reg & B_DO3) set_DO3; else clr_DO3;

	app_regs.REG_DIGITAL_OUTPUT_STATE = reg;
	
    return true;
}

/************************************************************************/
/* REG_ENABLE_EVENTS                                                    */
/************************************************************************/
void app_read_REG_ENABLE_EVENTS(void) {}

bool app_write_REG_ENABLE_EVENTS(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_ENABLE_EVENTS = reg;
    return true;
}
