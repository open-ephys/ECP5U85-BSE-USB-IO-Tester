#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"


/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_TEST_STARTED,
	&app_read_REG_FAIL_EVENT,
	&app_read_REG_J1_2V5_7,
	&app_read_REG_J1_3V3_9,
	&app_read_REG_J1_3V3_11,
	&app_read_REG_J1_3V3_13,
	&app_read_REG_J1_5V_1,
	&app_read_REG_J1_5V_3,
	&app_read_REG_J1_5V_5,
	&app_read_REG_J1_RAMVDD_4,
	&app_read_REG_J1_RAMVDD_6,
	&app_read_REG_J2_3V3_2,
	&app_read_REG_J2_3V3_4,
	&app_read_REG_J2_3V3_6
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_TEST_STARTED,
	&app_write_REG_FAIL_EVENT,
	&app_write_REG_J1_2V5_7,
	&app_write_REG_J1_3V3_9,
	&app_write_REG_J1_3V3_11,
	&app_write_REG_J1_3V3_13,
	&app_write_REG_J1_5V_1,
	&app_write_REG_J1_5V_3,
	&app_write_REG_J1_5V_5,
	&app_write_REG_J1_RAMVDD_4,
	&app_write_REG_J1_RAMVDD_6,
	&app_write_REG_J2_3V3_2,
	&app_write_REG_J2_3V3_4,
	&app_write_REG_J2_3V3_6
};


/************************************************************************/
/* REG_TEST_STARTED                                                     */
/************************************************************************/
void app_read_REG_TEST_STARTED(void)
{
	//app_regs.REG_TEST_STARTED = 0;

}

bool app_write_REG_TEST_STARTED(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_TEST_STARTED = reg;
	return true;
}


/************************************************************************/
/* REG_FAIL_EVENT                                                       */
/************************************************************************/
// This register is an array with 4 positions
void app_read_REG_FAIL_EVENT(void)
{
	//app_regs.REG_FAIL_EVENT[0] = 0;

}

bool app_write_REG_FAIL_EVENT(void *a)
{
	uint8_t *reg = ((uint8_t*)a);

	app_regs.REG_FAIL_EVENT[0] = reg[0];
	return true;
}


/************************************************************************/
/* REG_J1_2V5_7                                                         */
/************************************************************************/
void app_read_REG_J1_2V5_7(void)
{
	//app_regs.REG_J1_2V5_7 = 0;

}

bool app_write_REG_J1_2V5_7(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_2V5_7 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_3V3_9                                                         */
/************************************************************************/
void app_read_REG_J1_3V3_9(void)
{
	//app_regs.REG_J1_3V3_9 = 0;

}

bool app_write_REG_J1_3V3_9(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_3V3_9 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_3V3_11                                                        */
/************************************************************************/
void app_read_REG_J1_3V3_11(void)
{
	//app_regs.REG_J1_3V3_11 = 0;

}

bool app_write_REG_J1_3V3_11(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_3V3_11 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_3V3_13                                                        */
/************************************************************************/
void app_read_REG_J1_3V3_13(void)
{
	//app_regs.REG_J1_3V3_13 = 0;

}

bool app_write_REG_J1_3V3_13(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_3V3_13 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_5V_1                                                          */
/************************************************************************/
void app_read_REG_J1_5V_1(void)
{
	//app_regs.REG_J1_5V_1 = 0;

}

bool app_write_REG_J1_5V_1(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_5V_1 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_5V_3                                                          */
/************************************************************************/
void app_read_REG_J1_5V_3(void)
{
	//app_regs.REG_J1_5V_3 = 0;

}

bool app_write_REG_J1_5V_3(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_5V_3 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_5V_5                                                          */
/************************************************************************/
void app_read_REG_J1_5V_5(void)
{
	//app_regs.REG_J1_5V_5 = 0;

}

bool app_write_REG_J1_5V_5(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_5V_5 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_RAMVDD_4                                                      */
/************************************************************************/
void app_read_REG_J1_RAMVDD_4(void)
{
	//app_regs.REG_J1_RAMVDD_4 = 0;

}

bool app_write_REG_J1_RAMVDD_4(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_RAMVDD_4 = reg;
	return true;
}


/************************************************************************/
/* REG_J1_RAMVDD_6                                                      */
/************************************************************************/
void app_read_REG_J1_RAMVDD_6(void)
{
	//app_regs.REG_J1_RAMVDD_6 = 0;

}

bool app_write_REG_J1_RAMVDD_6(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J1_RAMVDD_6 = reg;
	return true;
}


/************************************************************************/
/* REG_J2_3V3_2                                                         */
/************************************************************************/
void app_read_REG_J2_3V3_2(void)
{
	//app_regs.REG_J2_3V3_2 = 0;

}

bool app_write_REG_J2_3V3_2(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J2_3V3_2 = reg;
	return true;
}


/************************************************************************/
/* REG_J2_3V3_4                                                         */
/************************************************************************/
void app_read_REG_J2_3V3_4(void)
{
	//app_regs.REG_J2_3V3_4 = 0;

}

bool app_write_REG_J2_3V3_4(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J2_3V3_4 = reg;
	return true;
}


/************************************************************************/
/* REG_J2_3V3_6                                                         */
/************************************************************************/
void app_read_REG_J2_3V3_6(void)
{
	//app_regs.REG_J2_3V3_6 = 0;

}

bool app_write_REG_J2_3V3_6(void *a)
{
	float reg = *((float*)a);

	app_regs.REG_J2_3V3_6 = reg;
	return true;
}