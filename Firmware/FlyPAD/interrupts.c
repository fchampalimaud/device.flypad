#include "cpu.h"
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"
#include "app_funcs.h"
#include "hwbp_core.h"

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;

/************************************************************************/
/* Interrupts from Timers                                               */
/************************************************************************/
// ISR(TCC0_OVF_vect, ISR_NAKED)
// ISR(TCD0_OVF_vect, ISR_NAKED)
// ISR(TCE0_OVF_vect, ISR_NAKED)
// ISR(TCF0_OVF_vect, ISR_NAKED)
// 
// ISR(TCC0_CCA_vect, ISR_NAKED)
// ISR(TCD0_CCA_vect, ISR_NAKED)
// ISR(TCE0_CCA_vect, ISR_NAKED)
// ISR(TCF0_CCA_vect, ISR_NAKED)
// 
// ISR(TCD1_OVF_vect, ISR_NAKED)
// 
// ISR(TCD1_CCA_vect, ISR_NAKED)

/************************************************************************/
/* DI0                                                                  */
/************************************************************************/
ISR(PORTB_INT0_vect, ISR_NAKED)
{
	uint8_t reg_port_dis = app_regs.REG_DIGITAL_INPUT_STATE;
	
	app_regs.REG_DIGITAL_INPUT_STATE &= ~B_DI0;
	app_regs.REG_DIGITAL_INPUT_STATE |= (read_DI0) ? B_DI0 : 0;
	
	if (app_regs.REG_ENABLE_EVENTS & B_DIGITAL_INPUTS)
	{
		if (reg_port_dis != app_regs.REG_DIGITAL_INPUT_STATE)
		{
			core_func_send_event(ADD_REG_DIGITAL_INPUT_STATE, true);
		}
	}

	reti();
}

/************************************************************************/
/* DI1                                                                  */
/************************************************************************/
ISR(PORTC_INT0_vect, ISR_NAKED)
{
	uint8_t reg_port_dis = app_regs.REG_DIGITAL_INPUT_STATE;
	
	app_regs.REG_DIGITAL_INPUT_STATE &= ~B_DI1;
	app_regs.REG_DIGITAL_INPUT_STATE |= (read_DI1) ? B_DI1 : 0;
	
	if (app_regs.REG_ENABLE_EVENTS & B_DIGITAL_INPUTS)
	{
		if (reg_port_dis != app_regs.REG_DIGITAL_INPUT_STATE)
		{
			core_func_send_event(ADD_REG_DIGITAL_INPUT_STATE, true);
		}
	}

	reti();
}
