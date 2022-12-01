#include "hwbp_core.h"
#include "hwbp_core_regs.h"
#include "hwbp_core_types.h"

#include "app.h"
#include "app_funcs.h"
#include "app_ios_and_regs.h"

#define F_CPU 32000000
#include "util/delay.h"


/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;
extern uint8_t app_regs_type[];
extern uint16_t app_regs_n_elements[];
extern uint8_t *app_regs_pointer[];
extern void (*app_func_rd_pointer[])(void);
extern bool (*app_func_wr_pointer[])(void*);

/************************************************************************/
/* Initialize app                                                       */
/************************************************************************/
static const uint8_t default_device_name[] = "OpenEphysFPGATester";

void hwbp_app_initialize(void)
{
    /* Define versions */
    uint8_t hwH = 1;
    uint8_t hwL = 0;
    uint8_t fwH = 1;
    uint8_t fwL = 0;
    uint8_t ass = 0;
    
   	/* Start core */
    core_func_start_core(
        0,
        hwH, hwL,
        fwH, fwL,
        ass,
        (uint8_t*)(&app_regs),
        APP_NBYTES_OF_REG_BANK,
        APP_REGS_ADD_MAX - APP_REGS_ADD_MIN + 1,
        default_device_name,
        false,	// The device is not able to repeat the harp timestamp clock
        false	// The device is not able to generate the harp timestamp clock
    );
}

/************************************************************************/
/* Handle if a catastrophic error occur                                 */
/************************************************************************/
void core_callback_catastrophic_error_detected(void)
{
	
}

/************************************************************************/
/* User functions                                                       */
/************************************************************************/
/* Add your functions here or load external functions if needed */

#define write_address(add) PORTC_OUT = (PORTC_IN & 0x0F) | (add << 4)

float test_0_to_7[8];
#define LOGIC_HIGH_TH_V 1.5

uint8_t test_start_counter;

void read_analog_test_0_to_7 (void)
{
	test_0_to_7[0] = adc_A_read_channel(1) * 3.3/4096;
	test_0_to_7[1] = adc_A_read_channel(2) * 3.3/4096;
	test_0_to_7[2] = adc_A_read_channel(3) * 3.3/4096;
	test_0_to_7[3] = adc_A_read_channel(4) * 3.3/4096;
	test_0_to_7[4] = adc_A_read_channel(5) * 3.3/4096;
	test_0_to_7[5] = adc_A_read_channel(6) * 3.3/4096;
	test_0_to_7[6] = adc_A_read_channel(7) * 3.3/4096;
	test_0_to_7[7] = adc_A_read_channel(9) * 3.3/4096;
}

void read_analog_test_power (void)
{
	write_address(6);	_delay_us(10); app_regs.REG_J1_2V5_7 = adc_A_read_channel(10) * 3.3/4096;
	
	write_address(2); _delay_us(10); app_regs.REG_J1_3V3_9 = adc_A_read_channel(10) * 3.3/4096;
	write_address(1); _delay_us(10); app_regs.REG_J1_3V3_11 = adc_A_read_channel(10) * 3.3/4096;
	write_address(0); _delay_us(10); app_regs.REG_J1_3V3_13 = adc_A_read_channel(10) * 3.3/4096;
	
	write_address(3); _delay_us(10); app_regs.REG_J1_5V_1 = adc_A_read_channel(10) * 3.3/4096 * 2;
	write_address(4); _delay_us(10); app_regs.REG_J1_5V_3 = adc_A_read_channel(10) * 3.3/4096 * 2;
	write_address(5); _delay_us(10); app_regs.REG_J1_5V_5 = adc_A_read_channel(10) * 3.3/4096 * 2;
	
	write_address(8); _delay_us(10); app_regs.REG_J1_RAMVDD_4 = adc_A_read_channel(10) * 3.3/4096;
	write_address(9); _delay_us(10); app_regs.REG_J1_RAMVDD_6 = adc_A_read_channel(10) * 3.3/4096;

	write_address(10); _delay_us(10); app_regs.REG_J2_3V3_2 = adc_A_read_channel(10) * 3.3/4096;
	write_address(12); _delay_us(10); app_regs.REG_J2_3V3_4 = adc_A_read_channel(10) * 3.3/4096;
	write_address(13); _delay_us(10); app_regs.REG_J2_3V3_6 = adc_A_read_channel(10) * 3.3/4096;
	
	core_func_send_event(ADD_REG_J1_2V5_7, true);
	
	core_func_send_event(ADD_REG_J1_3V3_9, true);
	core_func_send_event(ADD_REG_J1_3V3_11, true);
	core_func_send_event(ADD_REG_J1_3V3_13, true);
	
	core_func_send_event(ADD_REG_J1_5V_1, true);
	core_func_send_event(ADD_REG_J1_5V_3, true);
	core_func_send_event(ADD_REG_J1_5V_5, true);
	
	core_func_send_event(ADD_REG_J1_RAMVDD_4, true);
	core_func_send_event(ADD_REG_J1_RAMVDD_6, true);
	
	core_func_send_event(ADD_REG_J2_3V3_2, true);
	core_func_send_event(ADD_REG_J2_3V3_4, true);
	core_func_send_event(ADD_REG_J2_3V3_6, true);
}

uint8_t increase_for_exceptions (uint8_t address_n, uint8_t test_n)
{
	if ((test_n == 1) && (address_n == 7)) return 1;
	
	if ((test_n == 3) && (address_n == 0)) return 1;
	if ((test_n == 3) && (address_n == 1)) return 1;
	if ((test_n == 3) && (address_n == 11)) return 1;
	
	if ((test_n == 5) && (address_n == 14)) return 1;
	if ((test_n == 5) && (address_n == 15)) return 1;
	
	if ((test_n == 6) && (address_n == 0)) return 1;
	if ((test_n == 6) && (address_n == 1)) return 1;
	if ((test_n == 6) && (address_n == 7)) return 1;
	
	return 0;
}

uint8_t count_number_of_high_pins (void)
{
	uint8_t count_highs = 0;
	
	/* Go through all addresses and read all test lines */
	for (uint8_t add_sweep = 0; add_sweep < 16; add_sweep++)
	{
		write_address(add_sweep);
		_delay_us(10);
		
		/* Read analog value from all the 8 test lines */
		read_analog_test_0_to_7();
		
		/* Apply a threshold to each test line and count the amount of 1s */
		for (uint8_t i = 0; i<8; i++)
		{
			if (test_0_to_7[i] > LOGIC_HIGH_TH_V)
			{
				count_highs++;
			}
		}
	}
	
	return count_highs;
}

/************************************************************************/
/* Initialization Callbacks                                             */
/************************************************************************/
void core_callback_define_clock_default(void) {}

void core_callback_initialize_hardware(void)
{
	/* Initialize IOs */
	/* Don't delete this function!!! */
	init_ios();
	
	/* Initialize ADCA with single ended input */
	adc_A_initialize_single_ended(ADC_REFSEL_AREFA_gc);	
}

void core_callback_reset_registers(void)
{
	/* Initialize registers */
	
}

void core_callback_registers_were_reinitialized(void)
{
	/* Update registers if needed */
	
}

/************************************************************************/
/* Callbacks: Visualization                                             */
/************************************************************************/
void core_callback_visualen_to_on(void)
{
	/* Update visual indicators */
	
}

void core_callback_visualen_to_off(void)
{
	/* Clear all the enabled indicators */
	
}

/************************************************************************/
/* Callbacks: Change on the operation mode                              */
/************************************************************************/
void core_callback_device_to_standby(void) {}
void core_callback_device_to_active(void) {}
void core_callback_device_to_enchanced_active(void) {}
void core_callback_device_to_speed(void) {}

/************************************************************************/
/* Callbacks: 1 ms timer                                                */
/************************************************************************/
void core_callback_t_before_exec(void) {}
void core_callback_t_after_exec(void) {}
void core_callback_t_new_second(void)
{
	/* FPGA LED status:
	   0-> Lit
      1-> Blinking
      2-> Lit when the reset condition is met, unlit when you start cycling
      3-> Blink at the TestClk speed (in this case, fast, but could be useful to debug if you slow it)
	*/
	
	if (!read_BUTTON)	
	{
		test_start_counter++;
		
		/* Start reset time = 3 seconds */
		clr_TEST_CLK;
		
		/* Change device to active mode */
		uint8_t common_reg = GM_OP_MODE_ACTIVE;
		hwbp_write_common_reg(ADD_R_OPERATION_CTRL, TYPE_U8, &common_reg, 1);		
		
		/* Check if 3 seconds elapsed (we are giving 4 seconds to make sure) */		
		if (test_start_counter == 5)
		{
			/* Indicate to user that test started */
			set_LED_D3;
			
			/* Indicate to Bonsai that test started */
			app_regs.REG_TEST_STARTED = true;
			core_func_send_event(ADD_REG_TEST_STARTED, true);
			
			/* Read all the analog power rails and send reading to Bonsai */
			read_analog_test_power();
			
			/* Go through all the pins */
			for (uint8_t test = 0; test < 8; test++)
			{
				for (uint8_t address = 0; address < 16; address++)
				{
					/* For each pin, fall clock before testing */
					clr_TEST_CLK;
					_delay_us(10);
					
					/* Check how many pins are at logic high */
					uint8_t count = count_number_of_high_pins();
					
					/* Add an extra high count when the tested test line is connected to GND */
					count += increase_for_exceptions(address, test);
					
					/* For each pin, rise clock after testing */
					set_TEST_CLK;
					_delay_us(10);
					
					/* Notify Bonsai when there's no signal or more that one logic high value (i.e, a shunt) */
					if (count != 1)
					{
						app_regs.REG_FAIL_EVENT[0] = address;
						app_regs.REG_FAIL_EVENT[1] = test;
						app_regs.REG_FAIL_EVENT[3] = count;
						core_func_send_event(ADD_REG_FAIL_EVENT, true);
					}
				}
			}
			
			/* Clear both LEDs */
			clr_LED_D2;
			clr_LED_D3;
			
			/* Indicate to user that the test is done */
			for (uint8_t i = 0; i < 20; i++)
			{
				_delay_ms(100);
				tgl_LED_D2;
				tgl_LED_D3;
			}
			
			/* Reset device */
			wdt_reset_device();
		}
	}
	else
	{
		/* Restart counter */
		test_start_counter = 0;
	}
}

void core_callback_t_500us(void) {}
void core_callback_t_1ms(void) {}

/************************************************************************/
/* Callbacks: clock control                                              */
/************************************************************************/
void core_callback_clock_to_repeater(void) {}
void core_callback_clock_to_generator(void) {}
void core_callback_clock_to_unlock(void) {}
void core_callback_clock_to_lock(void) {}

/************************************************************************/
/* Callbacks: uart control                                              */
/************************************************************************/
void core_callback_uart_rx_before_exec(void) {}
void core_callback_uart_rx_after_exec(void) {}
void core_callback_uart_tx_before_exec(void) {}
void core_callback_uart_tx_after_exec(void) {}
void core_callback_uart_cts_before_exec(void) {}
void core_callback_uart_cts_after_exec(void) {}

/************************************************************************/
/* Callbacks: Read app register                                         */
/************************************************************************/
bool core_read_app_register(uint8_t add, uint8_t type)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;
	
	/* Receive data */
	(*app_func_rd_pointer[add-APP_REGS_ADD_MIN])();	

	/* Return success */
	return true;
}

/************************************************************************/
/* Callbacks: Write app register                                        */
/************************************************************************/
bool core_write_app_register(uint8_t add, uint8_t type, uint8_t * content, uint16_t n_elements)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;

	/* Check if the number of elements matches */
	if (app_regs_n_elements[add-APP_REGS_ADD_MIN] != n_elements)
		return false;

	/* Process data and return false if write is not allowed or contains errors */
	return (*app_func_wr_pointer[add-APP_REGS_ADD_MIN])(content);
}