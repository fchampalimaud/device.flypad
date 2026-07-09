#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"


/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_ENABLE_ACQUISITION,
	&app_read_REG_CAPACITANCE_VALUES,
	&app_read_REG_DI0_STATE,
	&app_read_REG_DI1_STATE,
	&app_read_REG_DIGITAL_OUTPUT_SET,
	&app_read_REG_DIGITAL_OUTPUT_CLEAR,
	&app_read_REG_DIGITAL_OUTPUT_TOGGLE,
	&app_read_REG_DIGITAL_OUTPUT_STATE,
	&app_read_REG_ENABLE_EVENTS
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_ENABLE_ACQUISITION,
	&app_write_REG_CAPACITANCE_VALUES,
	&app_write_REG_DI0_STATE,
	&app_write_REG_DI1_STATE,
	&app_write_REG_DIGITAL_OUTPUT_SET,
	&app_write_REG_DIGITAL_OUTPUT_CLEAR,
	&app_write_REG_DIGITAL_OUTPUT_TOGGLE,
	&app_write_REG_DIGITAL_OUTPUT_STATE,
	&app_write_REG_ENABLE_EVENTS
};

/************************************************************************/
/* REG_ENABLE_ACQUISITION                                               */
/************************************************************************/
void app_read_REG_ENABLE_ACQUISITION(void)
{
	//app_regs.REG_ENABLE_ACQUISITION = 0;

}

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
void app_read_REG_CAPACITANCE_VALUES(void)
{
	//app_regs.REG_CAPACITANCE_VALUES[0] = 0;

}

bool app_write_REG_CAPACITANCE_VALUES(void *a) { return false; }

/************************************************************************/
/* REG_DI0_STATE                                                        */
/************************************************************************/
void app_read_REG_DI0_STATE(void)
{
	//app_regs.REG_DI0_STATE = 0;

}

bool app_write_REG_DI0_STATE(void *a) { return false; }

/************************************************************************/
/* REG_DI1_STATE                                                        */
/************************************************************************/
void app_read_REG_DI1_STATE(void)
{
	//app_regs.REG_DI1_STATE = 0;

}

bool app_write_REG_DI1_STATE(void *a) { return false; }

/************************************************************************/
/* REG_DIGITAL_OUTPUT_SET                                               */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_SET(void)
{
	//app_regs.REG_DIGITAL_OUTPUT_SET = 0;

}

bool app_write_REG_DIGITAL_OUTPUT_SET(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_DIGITAL_OUTPUT_SET = reg;
    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_CLEAR                                             */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_CLEAR(void)
{
	//app_regs.REG_DIGITAL_OUTPUT_CLEAR = 0;

}

bool app_write_REG_DIGITAL_OUTPUT_CLEAR(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_DIGITAL_OUTPUT_CLEAR = reg;
    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_TOGGLE                                            */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_TOGGLE(void)
{
	//app_regs.REG_DIGITAL_OUTPUT_TOGGLE = 0;

}

bool app_write_REG_DIGITAL_OUTPUT_TOGGLE(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_DIGITAL_OUTPUT_TOGGLE = reg;
    return true;
}

/************************************************************************/
/* REG_DIGITAL_OUTPUT_STATE                                             */
/************************************************************************/
void app_read_REG_DIGITAL_OUTPUT_STATE(void)
{
	//app_regs.REG_DIGITAL_OUTPUT_STATE = 0;

}

bool app_write_REG_DIGITAL_OUTPUT_STATE(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_DIGITAL_OUTPUT_STATE = reg;
    return true;
}

/************************************************************************/
/* REG_ENABLE_EVENTS                                                    */
/************************************************************************/
void app_read_REG_ENABLE_EVENTS(void)
{
	//app_regs.REG_ENABLE_EVENTS = 0;

}

bool app_write_REG_ENABLE_EVENTS(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_ENABLE_EVENTS = reg;
    return true;
}
