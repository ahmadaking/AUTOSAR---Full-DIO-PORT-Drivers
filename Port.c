 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmad Samir Atta
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"
//#include "Port_Cbk.h"

//#include "Dem.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"

/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigChannel * Port_PortChannels = NULL_PTR;
STATIC volatile uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name		: Port_Init
* Service ID[hex]	: 0x00
* Sync/Async		: Synchronous
* Reentrancy		: Non reentrant
* Parameters(in)	: ConfigPtr - Pointer to configuration set.
* Parameters(inout)	: None
* Parameters(out)	: None
* Return value		: None
* Description		: Function to Initialize the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
	#if (DIO_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if (NULL_PTR == ConfigPtr)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
							PORT_INIT_SID, PORT_E_PARAM_CONFIG);
		}
		else
		{
			/* code */
		}	
	#endif

	typedef enum  {A,B,C,D,E,F}PORT; 									/* Port Names values 0,1,2,3,4,5*/ 
	typedef enum  {PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7}PIN; /* Pin Names values 0,1,2,3,4,5,6,7*/
	
	
	
	/* for loop on num.of pins to configure them */
	int ChannelId;
	boolean JTAG_statuse;		/* to protect JTAG pins [PC0 to PC3]*/
	for ( ChannelId = 0; ChannelId <= 42; ChannelId++)
	{		
		volatile uint32 * PortGpio_Ptr = NULL_PTR; 		/* point to the required Port Registers base address */
		volatile uint32 delay = 0;
		JTAG_statuse = FALSE;
		/* Avoid Invalid Port Pin ID requested Or virtual pin */
		{
		/*
		 * Set the module state to initialized and 
		 */
		Port_Status = PORT_INITIALIZED;
		Port_PortChannels = ConfigPtr -> Channels; /* address of the first Channels structure --> Channels[0] */
		}

		/* 1- Choose Port Base Address and assign it in "PortGpio_Ptr" */
		switch(Port_PortChannels[ChannelId].port_num)
		{
			case  A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					 break;
			case  B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					 break;
			case  C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
				 	 break;
			case  D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					 break;
			case  E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					 break;
			case  F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					 break;
		}
		/* 2- Enable clock for PORT and allow time for clock to start*/
		SYSCTL_REGCGC2_REG |= (1<<Port_PortChannels[ChannelId].port_num);
		delay = SYSCTL_REGCGC2_REG;
		
		/* 3- unlock specific pis & protect JTAG pins */
			/* unlock specific pis */
			/* PD7 or PF0 */
		if( ((D == Port_PortChannels[ChannelId].port_num) && (PIN_7 == Port_PortChannels[ChannelId].pin_num)) || ((F == Port_PortChannels[ChannelId].port_num) && (PIN_0 == Port_PortChannels[ChannelId].pin_num)) ) 
		{
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;   
				/* Unlock the GPIOCR register */   
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);  
				/* Set the corresponding bit in GPIOCR register to allow changes on this pin */
		}
			/* protect JTAG pins */
			/* PC0 to PC3 */
		else if( (C == Port_PortChannels[ChannelId].port_num) && (Port_PortChannels[ChannelId].pin_num <= PIN_3) ) 
		{
			/* Do Nothing ...  this is the JTAG pins */
			JTAG_statuse = TRUE;
		}
		/* MISRA rule, each if has else */
		else
		{
			/* Do Nothing ... No need to unlock the commit register for this pin */
		}

		/* 4- for corresponding pins :
						* 4.1 Initialize Direction (INPUT/OUTPUT)
						* 4.2 Initialize pin value (HIGH/LOW)
						* 4.3 Initialize pin resistor value (PULL-UP/DOWN)
		*/
		/* 4.1 Initialize Direction (INPUT/OUTPUT) */
		if( (PORT_PIN_OUT == Port_PortChannels[ChannelId].initDirection) && (FALSE == JTAG_statuse))
		{
					/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
			
				/* 4.2 Initialize pin value (HIGH/LOW) */
			if(PORT_PIN_LEVEL_HIGH == Port_PortChannels[ChannelId].initial_value)
			{
					/* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 	
			}
			else
			{
					/* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);  
			}
				
				/* 4.3 Disable Resistor for Output pin*/
					/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
					/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */	
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
									
		}
		/* 4.1 Initialize Direction (INPUT/OUTPUT) */
		else if ( (PORT_PIN_IN == Port_PortChannels[ChannelId].initDirection) && (FALSE == JTAG_statuse))
		{
					/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);  		
				/* 5.3 Initialize Pin Resistor value (PULL-UP/DOWN) */
			if(PULL_UP == Port_PortChannels[ChannelId].resistor)
			{
					/* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);    
			}
			else if(PULL_DOWN == Port_PortChannels[ChannelId].resistor)
			{
					/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
			}
			else 
			{
					/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);     
					/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
			}
		}
		/* MISRA rule, each if has else */
		else
		{
			/* Do Nothing */
		}
			
		/*******************************************************************************
		* Description : Configuring Each pin Depinding on its Configured Mode choosed in PBfg.h file
		* Note 	   	  : Eatch pin has its functionalities (ECU Dependant)
		*******************************************************************************/
		/*
		 * Initialize pins for DIO 
		 */
		if (FALSE == JTAG_statuse)
		{
			if (PORT_PIN_MODE_DIO == Port_PortChannels[ChannelId].initMode)
			{
				
				/* 5- for corresponding pins :
								* 5.1 Disable analog functionality 
								* 5.2 Disable Alternative function 
								* 5.3 Clear the PMCx (CTL_REG) bits GPIO pin
								* 5.4 Enable Digital funtionality on this pin
				*/
			
							/* 5.1 Disable analog functionality by Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
				
							/* 5.2 Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
				
							/* 5.3 Clear the PMCx (CTL_REG) bits GPIO pin */
				*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[ChannelId].pin_num * 4));     

							/* 5.4 Enable Digital funtionality on this pin by Setting the corresponding bit in the GPIODEN register  */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
			}

			/*
			* Initialize pins for ADC 
			*/
			else if (PORT_PIN_MODE_ADC == Port_PortChannels[ChannelId].initMode)
			{
				/* 
				* Configer Only pins which have ADC functionality, which are [20 pins] :
				* 	PB0 - PB1 - PB4 - PB5 - [ PC4 to PC7 ] - [ PD0 to PD5] - [ PE0 to PE5]
				*/
				if ( ((8 == ChannelId) || (9 == ChannelId) || (12 == ChannelId) || (13 == ChannelId) ) || 
					( (20 == ChannelId) && (29 == ChannelId) ) || ( (32 == ChannelId) && (37 == ChannelId) ) )
				{
					
					/* 5- for corresponding pins :
									* 5.1 Enable analog functionality 
									* 5.2 Disable Alternative function
									* 5.3 Disable Digital funtionality on this pin 
					*/
							/* 5.1 Enable analog functionality by SET the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
					
							/* 5.2 Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
					
							/* 5.3 Disable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
				}
			}

			/* Initialize pins for Alternative function */
			else 
			{
				switch (Port_PortChannels[ChannelId].initMode)
				{
					/* Initialize pins for CAN */
					case PORT_PIN_MODE_CAN :
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config CAN pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config CAN pin */
								/* 
								* Config pins with CAN functionality with PMCx value (8), which are :
								*  PA0 - PA1 - PB4 - PB5 - PE4 - PE5
								*/
								if ( (0== ChannelId) || (1== ChannelId) || (12== ChannelId) || (13== ChannelId) ||
									(36== ChannelId) || (37== ChannelId) )
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}

								/* 
								* Config pins with CAN functionality with PMCx value (3), which are :
								*  PF0 - PF3
								*/
								else if ( (38== ChannelId) || (41== ChannelId) )
								{
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000003 << (Port_PortChannels[ChannelId].pin_num * 4)); 
								}

								else
								{
									/* Do Nothing */
								}

											
								break; 
					/* Initialize pins for UART_1x driver */
					case PORT_PIN_MODE_UART_1x : 	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_1x pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);  			
										
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_1x pin */  
								/* 
								* Config pins with UART_1x functionality with PMCx value (2), which are :
								*  [PC4 - PC5]
								*/
								if ( (20== ChannelId) || (21== ChannelId) )
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}
								/* 
								* Config pins with UART functionality with PMCx value (1), which are :
								*  [PB0-PB1]
								*/
								else
								{
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (Port_PortChannels[ChannelId].pin_num * 4));
								}
								
								break;

					/* Initialize pins for UART_TS driver */
					case PORT_PIN_MODE_UART_TS : 	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_TS pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);       	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_TS pin */  
								/* 
								* Config pins with UART_TS functionality with PMCx value (8), which are :
								*  [PC4 - PC5]
								*/
								if ( (20== ChannelId) || (21== ChannelId) )
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}
								/* 
								* Config pins with UART functionality with PMCx value (1), which are :
								*  [PF0-PF1]
								*/
								else
								{
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (Port_PortChannels[ChannelId].pin_num * 4));
								}
								
								break;
					
					/* Initialize pins for UART_0234567x driver */
					case PORT_PIN_MODE_UART_0234567x : 	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_0234567x pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_0234567x pin */  
								/* 
								* Config pins with UART_0234567x functionality with PMCx value (1), which are :
								*  [PA0-PA1] - [PB0-PB1] - [PC4-PC7] - [PD4-PD7] - [PE0-PE1] - [PE4-PE5]
								*/
								if ( (0== ChannelId) || (1== ChannelId) || (8== ChannelId) || (9== ChannelId) 
									|| (20== ChannelId) || (21== ChannelId) || (22== ChannelId) || (23== ChannelId)
										|| (28== ChannelId) || (29== ChannelId) || (30== ChannelId) || (31== ChannelId)
										|| (32== ChannelId) || (33== ChannelId) || (36== ChannelId) || (37== ChannelId))
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}
								else
								{
									/* Do Nothing */
								} 			
								break;


					/* Initialize pins for Synchronous Serial Interface 1 (SSI = SPI) driver */
					case PORT_PIN_MODE_SSI_1 :	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_1 pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_1 pin */  
								/* 
								* Config pins with SSI_1 functionality with PMCx value (2), which are :
								*  [PD0-PD3] - [PF0-PF3]
								*/
								if ( (24== ChannelId) || (25== ChannelId) || (26== ChannelId) || (27== ChannelId)
									|| (38== ChannelId) || (39== ChannelId) || (40== ChannelId) || (41== ChannelId))
															{
																*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (Port_PortChannels[ChannelId].pin_num * 4)); 
								}
								/* MISRA rules */
								else
								{
									/* Do Nothing */
								}

								break;

					/* Initialize pins for Synchronous Serial Interface 2 (SSI = SPI) driver */
					case PORT_PIN_MODE_SSI_2 :	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_2 pin
												
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_2 pin */  
								/* 
								* Config pins with SSI_2 functionality with PMCx value (2), which are :
								*  [PA2-PA5]
								*/
								if ( (2== ChannelId) || (3== ChannelId) || (4== ChannelId) || (5== ChannelId) )
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}
								/* MISRA rules */
								else
								{
									/* Do Nothing */
								}

								break;  

					/* Initialize pins for Synchronous Serial Interface 3 (SSI = SPI) driver */
					case PORT_PIN_MODE_SSI_3 :	
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_3 pin
												
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);  
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
										
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config SSI_3 pin */  
								/* 
								* Config pins with SSI_3 functionality with PMCx value (1), which are :
								*  [PD0-PD3]
								*/
								if ( (24== ChannelId) || (25== ChannelId) || (26== ChannelId) || (27== ChannelId) )
									{
										*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (Port_PortChannels[ChannelId].pin_num * 4)); 
									}
								/* MISRA rules */
								else
								{
									/* Do Nothing */
								}

								break;

					/* Initialize pins for DIO. It shall be used under control of the general purpose timer driver. */
					case PORT_PIN_MODE_DIO_GPT : 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin
												* 5.4 SET the PMCx (CTL_REG) bits with value to config GPT pin
												
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config GPT pin */  
								/* 
								* Config pins with GPT functionality with PMCx value (7), which are :
								*  [PB0-PB7] - [PC0-PC7] - [PD0-PD7]
								*/
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000007 << (Port_PortChannels[ChannelId].pin_num * 4)); 
								
								break; 
					/* Initialize pins for Analog Comparator driver */
					case PORT_PIN_MODE_ANALOG_COMP :
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config Analog Comparator pin
												
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config Analog Comparator pin */  
								/* 
								* Config pins with Analog Comparator functionality with PMCx value (9), which are :
								*  [PF0-PF1]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000009 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break; 

					/* Initialize pins for System Control & Clocks NMI driver */
					case PORT_PIN_MODE_SYS_CONTROL_CLOCKS_NMI : 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config System Control & Clocks NMI pin
												
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to config System Control & Clocks NMI pin */  
								/* 
								* Config pins with System Control & Clocks NMI functionality with PMCx value (8), which are :
								*  [PD7]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for I2C driver */
					case PORT_PIN_MODE_I2C : 
								/* 2- Enable clock for PORT and allow time for clock to start*/
								SYSCTL_REGCGC2_REG |= (1<<Port_PortChannels[ChannelId].port_num);
								delay = SYSCTL_REGCGC2_REG;
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config I2C pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to I2C pin */  
								/* 
								* Config pins with I2C functionality with PMCx value (3), which are :
								*  [PA6-PA7] - [PB2-PB3] - [PD0-PD1]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000003 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for PWM_0 driver */
					case PORT_PIN_MODE_PWM_0 	: 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config PWM_0 pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to PWM_0 pin */  
								/* 
								* Config pins with PWM_0 functionality with PMCx value (4), which are :
								*  [PC4-PC5] - [PB4-PB7] - [PD0-PD2] - [PD6] - [PE4-PE5] - [PF2]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000004 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for PWM_1 driver */
					case PORT_PIN_MODE_PWM_1 	: 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config PWM_1 pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to PWM_1 pin */  
								/* 
								* Config pins with PWM_0 functionality with PMCx value (5), which are :
								*   [PD0-PD1] - [PD6] - [PE4-PE5] - [PF0-PF4]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000005 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for USB driver */
					case PORT_PIN_MODE_USB 	: 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config USB pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to USB pin */  
								/* 
								* Config pins with USB functionality with PMCx value (8), which are :
								*  [PC6-PC7] - [PD2-PD3] - [PD6] - [PF4]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for Quadrature Encoder Interface driver. */
					case PORT_PIN_MODE_QEI : 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config Quadrature Encoder Interface pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to Quadrature Encoder Interface pin */  
								/* 
								* Config pins with Quadrature Encoder Interface functionality with PMCx value (6), which are :
								*  [PC4-PC6] - [PD3] - [PD6-PD7] - [PF0-PF1] -[PF4]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000006 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for JTAG/SWD/SWO driver. */
					case PORT_PIN_MODE_JTAG_SWD_SWO : 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config JTAG/SWD/SWO pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.4 SET the PMCx (CTL_REG) bits with value to JTAG/SWD/SWO pin */  
								/* 
								* Config pins with JTAG/SWD/SWO functionality with PMCx value (1), which are :
								*  [PC0-PC3]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break;

					/* Initialize pins for Core (Trace) driver. */
					case PORT_PIN_MODE_CORE_TRACE : 
								
								/* 5- for corresponding pins :
												* 5.1 Enable analog functionality 
												* 5.2 Disable Alternative function 
												* 5.3 Enable Digital funtionality on this pin 
												* 5.4 SET the PMCx (CTL_REG) bits with value to config Core (Trace) pin
								*/
											/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
								CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
								
											/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
											/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
								SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);        	
								
											/* 5.3 SET the PMCx (CTL_REG) bits with value to Core (Trace) pin */  
								/* 
								* Config pins with Core (Trace) functionality with PMCx value (14 = 0xE), which are :
								*  [PF1-PF3]
								*/
								
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x0000000E << (Port_PortChannels[ChannelId].pin_num * 4)); 
							
								break; 

					default :	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
											PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);
								break;			
							/* In case of Invalid Mode */
				}
			}
		}
	}
}

/************************************************************************************
* Service Name		: Port_SetPinDirection
* Service ID[hex]	: 0x01
* Sync/Async		: Synchronous
* Reentrancy		: Reentrant
* Parameters(in)	: - Pin 		 : Port Pin ID number
					  - Direction 	 : Direction
* Parameters(inout)	: None
* Parameters(out)	: None
* Return value		: None
* Description		: Sets the port pin direction
************************************************************************************/
	/* 
	 * The function "Port_SetPinDirection" only available to the user If:
	 *    - the pre-compile parameter "PORT_SET_PIN_DIRECTION_API" is set to TRUE,
	 * 	  		if set to FALSE, the function "Port_SetPinDirection" is not available.
	*/
#if ( STD_ON == PORT_SET_PIN_DIRECTION_API )
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	boolean error = FALSE;
	boolean channelValidity = FALSE;
	boolean dir_changabilityValidity = FALSE;
	volatile uint8   ChannelId = Pin;		        	/* Getting Channel_id from Pin num */
	//Port_PortChannels = Port_Configuration -> Channels; /* address of the first Channels structure --> Channels[0] */
	#if (DIO_DEV_ERROR_DETECT == STD_ON)
		/* 1- Check if the Driver is initialized before using this function */
		if (PORT_NOT_INITIALIZED == Port_Status)
		{
			/* Driver is Not-initialized before using this function */
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinDirection_SID, PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{
			/* Do Nothing*/
		}

		/* 2- Check Invalid Port Pin ID requested Or virtual pin */    
		if ( !((0 <= ChannelId) && (ChannelId <= 42)) )
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinDirection_SID, PORT_E_PARAM_PIN);
		}
		/* Invalid Port Pin ID requested Or virtual pin */
		else 
		{
			channelValidity = TRUE;
		}

		/* 3- Ckeck Pin Direction changability */ 
		if (STD_OFF == Port_PortChannels[Pin].dirChangeability)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinDirection_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		}
		/* Pin Direction changability Invalid */
		else 
		{
			dir_changabilityValidity = TRUE;
		}
		
	#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	
	/* 
	* Check If :
	*		 - Driver is initialized before using this function
	*        - Pin Direction changability is available
	*		 - Pin is Not-Virtual	
	*/	
	if ((FALSE == error) && (TRUE == dir_changabilityValidity) && (TRUE == channelValidity))
	{	
		Port_PinType GpioPort_Num ;						/* Getting Port ID from Pin ID 0,1,2,3,4,5,6,7 */
		STATIC Port_PinType PortPin_Num ;				/* for Pint Num 0,1,2,3,4,5,6,7 */
		volatile uint32 * PortGpio_Ptr = NULL_PTR;  	/* point to the required Port Registers base address */
		typedef enum  {A,B,C,D,E,F}PORT; 				/* Port names values 0,1,2,3,4,5,6,7*/
		typedef enum  {PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7}PIN;

		/*
		 * Getting the equivalent Pin Num 0,1,2,3,4,5,6,7 from func input Pin
		*/
		if ( (0==Pin) || (8==Pin) || (16==Pin) || (24==Pin) || (32==Pin) || (38==Pin) )
		{
			PortPin_Num = PIN_0;
		}
		else if ( (1==Pin) || (9==Pin) || (17==Pin) || (25==Pin) || (33==Pin) || (39==Pin) )
		{
			PortPin_Num = PIN_1;
		}
		else if ( (2==Pin) || (10==Pin) || (18==Pin) || (26==Pin) || (34==Pin) || (40==Pin) )
		{
			PortPin_Num = PIN_2;
		}
		else if ( (3==Pin) || (11==Pin) || (19==Pin) || (27==Pin) || (35==Pin) || (41==Pin) )
		{
			PortPin_Num = PIN_3;
		}
		else if ( (4==Pin) || (12==Pin) || (20==Pin) || (28==Pin) || (36==Pin) || (42==Pin) )
		{
			PortPin_Num = PIN_4;
		}
		else if ( (5==Pin) || (13==Pin) || (21==Pin) || (29==Pin) || (37==Pin) )
		{
			PortPin_Num = PIN_5;
		}
		else if ( (6==Pin) || (14==Pin) || (22==Pin) || (30==Pin) )
		{
			PortPin_Num = PIN_6;
		}
		else if ( (7==Pin) || (15==Pin) || (23==Pin) || (31==Pin) )
		{
			PortPin_Num = PIN_7;
		}

		/*
		 * Getting Port ID from Port ID 0,1,2,3,4,5,6
		*/
		if ( (0==Pin) || (1<=Pin<=7) )
		{
			GpioPort_Num = A;
		}
		else if (8<=Pin<=15)
		{
			GpioPort_Num = B;
		}
		else if (16<=Pin<=23)
		{
			GpioPort_Num = C;
		}
		else if (24<=Pin<=31)
		{
			GpioPort_Num = D;
		}
		else if (32<=Pin<=37)
		{
			GpioPort_Num = E;
		}
		else if (38<=Pin<=42)
		{
			GpioPort_Num = F;
		}
		
		
		/* 1- Choose Port Base Address and assign it in "PortGpio_Ptr" */
		switch (GpioPort_Num)
		{
			case  A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					 break;
			case  B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					 break;
			case  C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
					 break;
			case  D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					 break;
			case  E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					 break;
			case  F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					 break;
		}
			
		/* 2- Setting Pin Direction
		 * If Output : 
		 * 		- Setting Direction Output
		 * 		- Disable Resistor (pull-up & pull-down)
		 * If Input :
		 * 		- Setting Direction Input
		 * 		- Initialize pull-up resistor
		 */
		if(Direction == PORT_PIN_OUT)
		{
			/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), PortPin_Num);                
		}
		else if(Direction == PORT_PIN_IN)
		{
			/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), PortPin_Num);                    
		}
		/* MISRA rules, each if has else */
		else
		{
			/* Do Nothing*/
		}
		
	}	
	/* MISRA rules, each if has else */
	else 
	{
		/* Do Nothing*/
	}
}
#endif  /* STD_ON == PORT_SET_PIN_DIRECTION_API */


/************************************************************************************
* Service Name		: Port_RefreshPortDirection
* Service ID[hex]	: 0x02
* Sync/Async		: Synchronous
* Reentrancy		: Non-Reentrant
* Parameters (in)	: None
* Parameters (inout): None
* Parameters (out)	: None
* Return value		: None
* Description		: Refreshes port direction
************************************************************************************/
void Port_RefreshPortDirection(void )
{
	boolean volatile error = FALSE;
	
	#if (DIO_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if (PORT_NOT_INITIALIZED == Port_Status)
		{
			/* Driver is Not-initialized before using this function */
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_RefreshPortDirection_SID, PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{
			/* code */
		}
		
	#endif


	typedef enum  {A,B,C,D,E,F}PORT; 				/* Port names values 0,1,2,3,4,5,6,7*/
	typedef enum  {PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7}PIN;
	
	/* for loop on num.of pins to configure them */
	for (uint8 ChannelId = 0; ChannelId <= 42; ChannelId++)
	{		
		/*  This Function is avilable in case the pin is configured as direction unchangeable  */
		if (STD_OFF == Port_PortChannels[ChannelId].initDirection)
		{
			volatile uint32 * PortGpio_Ptr = NULL_PTR; 		/* point to the required Port Registers base address */
			volatile uint32 delay = 0;
			/* Avoid Invalid Port Pin ID requested Or virtual pin */
	
			/* 1- Choose Port Base Address and assign it in "PortGpio_Ptr" */
			switch(Port_PortChannels[ChannelId].port_num)
			{
				case  A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
						break;
				case  B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
						break;
				case  C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
						break;
				case  D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
						break;
				case  E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
						break;
				case  F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
						break;
			}
	
			if(PORT_PIN_OUT == Port_PortChannels[ChannelId].initDirection)
			{
						/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[ChannelId].pin_num);   
			}
			
			else if(PORT_PIN_IN == Port_PortChannels[ChannelId].initDirection)
			{
						/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[ChannelId].pin_num); 
			}
			/* MISRA rules, each if has else */
			else 
			{
				/* Do Nothing */
			}
		}
	}
}

/************************************************************************************
* Service Name		: Port_GetVersionInfo
* Service ID[hex]	: 0x03
* Sync/Async		: Synchronous
* Reentrancy		: Non-Reentrant
* Parameters (in)	: None
* Parameters (inout): None
* Parameters (out)	: versioninfo (Pointer to where to store the version information of this module.)
* Return value		: None
* Description		: Returns the version information of this module.
************************************************************************************/
#if ( STD_ON == PORT_VERSION_INFO_API)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	#if (STD_ON == DIO_DEV_ERROR_DETECT)
		/* check if the input configuration pointer is not a NULL_PTR */
		if (NULL_PTR == versioninfo)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
							Port_GetVersionInfo_SID, PORT_E_PARAM_POINTER);
		}
		else
	#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */

	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif /* PORT_VERSION_INFO_API == STD_ON */


/************************************************************************************
* Service Name		: Port_SetPinMode
* Service ID[hex]	: 0x04
* Sync/Async		: Synchronous
* Reentrancy		: Reentrant
* Parameters (in)	: - Pin : Port Pin ID number
					  - Mode: New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out)	: versioninfo (Pointer to where to store the version information of this module.)
* Return value		: None
* Description		: Sets the port pin mode.
************************************************************************************/
	/* 
	 * The function "Port_SetPinMode" only available to the user If:
	 *    - the pre-compile parameter "PORT_SET_PIN_MODE_API" is set to STD_ON,
	 * 	  		if set to FALSE, the function "Port_SetPinMode" is not available.
	*/
#if ( STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
	boolean error = FALSE;
	boolean channelValidity = FALSE;
	boolean modeValidity = FALSE;
	boolean mode_changabilityValidity = FALSE;
	uint8   ChannelId = Pin;		        	/* Getting Channel_id from Pin num */
	
	#if (DIO_DEV_ERROR_DETECT == STD_ON)
		/* 1- Check if the Driver is initialized before using this function */
		if (PORT_NOT_INITIALIZED == Port_Status)
		{
			/* Driver is Not-initialized before using this function */
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinMode_SID, PORT_E_UNINIT);
			error = TRUE;
			
		}
		else
		{
			/* code */
		}
		
		/* 2- Check Invalid Port Pin ID requested */    
		if ( !((0 <= ChannelId) && (ChannelId <= 42)) )
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinMode_SID, PORT_E_PARAM_PIN);
		}
		/* Valid Port Pin ID requested */
		else 
		{
			channelValidity = TRUE;
		}

		/* 3- Ckeck Pin Mode changability */ 
		if (STD_OFF == Port_PortChannels[Pin].modeChangeability)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinMode_SID, PORT_E_MODE_UNCHANGEABLE);
		}
		/* Valid Pin Mode changability */
		else 
		{
			mode_changabilityValidity = TRUE;
		}

		/* 4- Check Mode Validity */
		if ( !( (PORT_PIN_MODE_DIO) || (PORT_PIN_MODE_ADC) || (PORT_PIN_MODE_CAN) || \\
				(PORT_PIN_MODE_DIO_GPT) || (PORT_PIN_MODE_DIO_WDG) || (PORT_PIN_MODE_ICU) || \\
				(PORT_PIN_MODE_LIN) || (PORT_PIN_MODE_MEM) || (PORT_PIN_MODE_PWM) || \\
				(PORT_PIN_MODE_SPI)) )
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							Port_SetPinMode_SID, PORT_E_PARAM_INVALID_MODE);
		}
		else
		{
			modeValidity == TRUE;
		}
		

	#endif
	
	/* 
	* Check If :
	 *		 - Driver is initialized before using this function
	 *       - Pin Mode changability is available
	 *		 - Pin ID is Valid	
	 *		 - Mode Validity
	 */
	if ( (FALSE == error) && (TRUE == mode_changabilityValidity) && (TRUE == channelValidity) && (TRUE == modeValidity))
	{	
		Port_PinType GpioPort_Num ;						/* Getting Port ID from Pin ID */
		STATIC volatile Port_PinType PortPin_Num ;		/* for Pint Num 0,1,2,3,4,5,6,7 */
		volatile uint32 * PortGpio_Ptr = NULL_PTR;  	/* point to the required Port Registers base address */
		volatile uint32 delay = 0;
		typedef enum  {A,B,C,D,E,F}PORT; 				/* Port names values 0,1,2,3,4,5,6,7*/
		typedef enum  {PIN_0,PIN_1,PIN_2,PIN_3,PIN_4,PIN_5,PIN_6,PIN_7}PIN;
		/*
		 * Getting the equivalent Pin Num 0,1,2,3,4,5,6,7 from func input Pin
		*/
		if ( (0==Pin) || (8==Pin) || (16==Pin) || (24==Pin) || (32==Pin) || (38==Pin) )
		{
			PortPin_Num = PIN_0;
		}
		else if ( (1==Pin) || (9==Pin) || (17==Pin) || (25==Pin) || (33==Pin) || (39==Pin) )
		{
			PortPin_Num = PIN_1;
		}
		else if ( (2==Pin) || (10==Pin) || (18==Pin) || (26==Pin) || (34==Pin) || (40==Pin) )
		{
			PortPin_Num = PIN_2;
		}
		else if ( (3==Pin) || (11==Pin) || (19==Pin) || (27==Pin) || (35==Pin) || (41==Pin) )
		{
			PortPin_Num = PIN_3;
		}
		else if ( (4==Pin) || (12==Pin) || (20==Pin) || (28==Pin) || (36==Pin) || (42==Pin) )
		{
			PortPin_Num = PIN_4;
		}
		else if ( (5==Pin) || (13==Pin) || (21==Pin) || (29==Pin) || (37==Pin) )
		{
			PortPin_Num = PIN_5;
		}
		else if ( (6==Pin) || (14==Pin) || (22==Pin) || (30==Pin) )
		{
			PortPin_Num = PIN_6;
		}
		else if ( (7==Pin) || (15==Pin) || (23==Pin) || (31==Pin) )
		{
			PortPin_Num = PIN_7;
		}

		/*
		 * Getting Port ID from Port ID 0,1,2,3,4,5,6
		*/
		if ( (0==Pin) || (1<=Pin<=7) )
		{
			GpioPort_Num = A;
		}
		else if (8<=Pin<=15)
		{
			GpioPort_Num = B;
		}
		else if (16<=Pin<=23)
		{
			GpioPort_Num = C;
		}
		else if (24<=Pin<=31)
		{
			GpioPort_Num = D;
		}
		else if (32<=Pin<=37)
		{
			GpioPort_Num = E;
		}
		else if (38<=Pin<=42)
		{
			GpioPort_Num = F;
		}
		
		
		/* 1- Choose Port Base Address and assign it in "PortGpio_Ptr" */
			switch (GpioPort_Num)
		{
			case  A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
					 break;
			case  B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
					 break;
			case  C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
					 break;
			case  D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
					 break;
			case  E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
					 break;
			case  F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
					 break;
		}

		/* 2- No need to Enable clock for PORT,  port init already handled it.*/

		/* 3- unlock specific pins and protect JTAG pins */
			/* PD7 or PF0 */
		if( ((D == GpioPort_Num) && (PIN_7 == PortPin_Num)) || ((F == GpioPort_Num) && (PIN_0 == PortPin_Num)) ) 
		{
			/* Unlock the GPIOCR register */ 
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; 
				/* Set the corresponding bit in GPIOCR register to allow changes on this pin */    
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), PortPin_Num);  
		}
			/* PC0 to PC3 */
		else if( (C == GpioPort_Num) && (PortPin_Num <= PIN_3) ) 
		{
			/* Do Nothing ...  this is the JTAG pins */
		}
		/* MISRA rule, each if has else */
		else
		{
			/* Do Nothing ... No need to unlock the commit register for this pin */
		}

		/* 4- Setting Pin mode depending on its mode value in Port_Configuration structure*/

		/*
		 * Initialize pins for DIO 
		 */
		if (PORT_PIN_MODE_DIO == Mode)
		{
			
			/* 5- for corresponding pins :
						* 5.1 Disable analog functionality 
						* 5.2 Disable Alternative function 
						* 5.3 Clear the PMCx (CTL_REG) bits GPIO pin
						* 5.4 Enabling Digital functionality
			*/
					/* 5.1 Disable analog functionality on this pin by Clear the corresponding bit in the GPIOAMSEL register*/
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num);      
					/* 5.2 Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);        	
					/* 5.3 Clear the PMCx bits for this pin */
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortPin_Num * 4));     
					/* 5.4 Enabling Digital functionality on this pin by Set the corresponding bit in the GPIODEN register */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);   
			
		}

		/*
		 * Initialize pins for ADC 
		 */
		else if (PORT_PIN_MODE_ADC == Mode)
		{
			/* 
			 * Configer Only pins which have ADC functionality, which are [20 pins] :
			 * 	PB0 - PB1 - PB4 - PB5 - [ PC4 to PC7 ] - [ PD0 to PD5] - [ PE0 to PE5]
			 */
			if ( ((8 == ChannelId) || (9 == ChannelId) || (12 == ChannelId) || (13 == ChannelId) ) || 
			     ( (20 == ChannelId) && (29 == ChannelId) ) || ( (32 == ChannelId) && (37 == ChannelId) ) )
			{
											
				/* 5- for corresponding pins :
								* 5.1 Enable analog functionality 
								* 5.2 Disable Alternative function 
								* 5.3 Disable Digital funtionality 
				*/
							/* 5.1 Enable analog functionality by SET the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
				
							/* 5.2 Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);        	

							/* 5.3 Disable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);   
			}
		}
		
		/*
		 * Initialize pins for Alternative function 
		 */
		else
		{
			switch (Mode)
			{
				/* Initialize pins for CAN */
				case PORT_PIN_MODE_CAN :
							
							/* 5- for corresponding pins :
											* 5.1 Enable analog functionality 
											* 5.2 Disable Alternative function 
											* 5.3 Enable Digital funtionality on this pin 
											* 5.4 SET the PMCx (CTL_REG) bits with value to config CAN pin
							*/
										/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);        	
							
										/* 5.4 SET the PMCx (CTL_REG) bits with value to config CAN pin */
							/* 
							 * Config pins with CAN functionality with PMCx value (8), which are :
							 *  PA0 - PA1 - PB4 - PB5 - PE4 - PE5
							 */
							if ( (0== ChannelId) || (1== ChannelId) || (12== ChannelId) || (13== ChannelId) ||
								 (36== ChannelId) || (37== ChannelId) )
								 {
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (PortPin_Num * 4)); 
								 }

							/* 
							 * Config pins with CAN functionality with PMCx value (3), which are :
							 *  PF0 - PF3
							 */
							else if ( (38== ChannelId) || (41== ChannelId) )
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000003 << (PortPin_Num * 4)); 
							}

							/* MISRA rule, each if has else */
							else
							{
								/* Do Nothing */
							}  			
							break; 

				/* Initialize pins for UART_1x driver */
				case PORT_PIN_MODE_UART_1x : 	
							
							/* 5- for corresponding pins :
											* 5.1 Disable analog functionality 
											* 5.2 Enable Alternative function 
											* 5.3 Enable Digital funtionality
											* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_1x pin
							*/
										/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num); 
										/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);       	
							
										/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_1x pin */  
							/* 
							 * Config pins with UART_1x functionality with PMCx value (2), which are :
							 *  [PC4 - PC5]
							 */
							if ( (20== ChannelId) || (21== ChannelId) )
								 {
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (PortPin_Num * 4)); 
								 }
							/* 
							 * Config pins with UART functionality with PMCx value (1), which are :
							 *  [PB0-PB1]
							 */
							else
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (PortPin_Num * 4));
							}  			
							break;

				/* Initialize pins for UART_TS driver */
				case PORT_PIN_MODE_UART_TS : 	

							/* 5- for corresponding pins :
											* 5.1 Disable analog functionality 
											* 5.2 Enable Alternative function 
											* 5.3 Enable Digital funtionality
											* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_TS pin
							*/
										/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);          	
							
										/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_TS pin */  
							/* 
							 * Config pins with UART_TS functionality with PMCx value (8), which are :
							 *  [PC4 - PC5]
							 */
							if ( (20== ChannelId) || (21== ChannelId) )
								 {
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (PortPin_Num * 4)); 
								 }
							/* 
							 * Config pins with UART functionality with PMCx value (1), which are :
							 *  [PF0-PF1]
							 */
							else
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (PortPin_Num * 4));
							}			
							break;
				
				/* Initialize pins for UART_0234567x driver */
				case PORT_PIN_MODE_UART_0234567x : 	
							
							/* 5- for corresponding pins :
											* 5.1 Disable analog functionality 
											* 5.2 Enable Alternative function 
											* 5.3 Enable Digital funtionality
											* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_0234567x pin
							*/
										/* 5.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 5.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 5.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			        	
							
										/* 5.4 SET the PMCx (CTL_REG) bits with value to config UART_0234567x pin */  
							/* 
							 * Config pins with UART_0234567x functionality with PMCx value (1), which are :
							 *  [PA0-PA1] - [PB0-PB1] - [PC4-PC7] - [PD4-PD7] - [PE0-PE1] - [PE4-PE5]
							 */
							if ( (0== ChannelId) || (1== ChannelId) || (8== ChannelId) || (9== ChannelId) 
								|| (20== ChannelId) || (21== ChannelId) || (22== ChannelId) || (23== ChannelId)
									 || (28== ChannelId) || (29== ChannelId) || (30== ChannelId) || (31== ChannelId)
									  || (32== ChannelId) || (33== ChannelId) || (36== ChannelId) || (37== ChannelId))
								 {
									*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (PortPin_Num * 4)); 
								 }
							
							/* MISRA rule, each if has else */
							else
							{
								/* Do Nothing */
							}
							break;


				/* Initialize pins for Synchronous Serial Interface 1 (SSI = SPI) driver */
				case PORT_PIN_MODE_SSI_1 :	
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_1 pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_1 pin */  
							/* 
							 * Config pins with SSI_1 functionality with PMCx value (2), which are :
							 *  [PD0-PD3] - [PF0-PF3]
							 */
							if ( (24== ChannelId) || (25== ChannelId) || (26== ChannelId) || (27== ChannelId)  
								 || (38== ChannelId) || (39== ChannelId) || (40== ChannelId) || (41== ChannelId) )
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (PortPin_Num * 4)); 
							}
							/* MISRA rule, each if has else */
							else
							{
								/* Do Nothing */
							}
							break;

				/* Initialize pins for Synchronous Serial Interface 2 (SSI = SPI) driver */
				case PORT_PIN_MODE_SSI_2 :
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_2 pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num); 
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							       	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_2 pin */  
							/* 
							 * Config pins with SSI_2 functionality with PMCx value (2), which are :
							 *  [PA2-PA5]
							 */
							if ( (2== ChannelId) || (3== ChannelId) || (4== ChannelId) || (5== ChannelId) )
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000002 << (PortPin_Num * 4)); 
							}
							/* MISRA rule, each if has else */
							else
							{
								/* Do Nothing */
							}

							break;  

				/* Initialize pins for Synchronous Serial Interface 3 (SSI = SPI) driver */
				case PORT_PIN_MODE_SSI_3 :	
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_3 pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config SSI_3 pin */  
							/* 
							 * Config pins with SSI_3 functionality with PMCx value (1), which are :
							 *  [PD0-PD3]
							 */
							if ( (24== ChannelId) || (25== ChannelId) || (26== ChannelId) || (27== ChannelId) )
							{
								*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (PortPin_Num * 4)); 
							}
							/* MISRA rule, each if has else */
							else
							{
								/* Do Nothing */
							}

							break;

				/* Initialize pins for DIO. It shall be used under control of the general purpose timer driver. */
				case PORT_PIN_MODE_DIO_GPT : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
	
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config UART pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config GPT pin */  
							/* 
							 * Config pins with GPT functionality with PMCx value (7), which are :
							 *  [PB0-PB7] - [PC0-PC7] - [PD0-PD7]
							 */
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000007 << (PortPin_Num * 4)); 

							break; 
				/* Initialize pins for Analog Comparator driver */
				case PORT_PIN_MODE_ANALOG_COMP : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config UART pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config Analog Comparator pin */  
							/* 
							 * Config pins with GPT functionality with PMCx value (9), which are :
							 *  [PF0-PF1]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000009 << (PortPin_Num * 4)); 

							break; 

				/* Initialize pins for System Control & Clocks NMI driver */
				case PORT_PIN_MODE_SYS_CONTROL_CLOCKS_NMI : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/

							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config System Control & Clocks NMI pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to config System Control & Clocks NMI pin */  
							/* 
							 * Config pins with System Control & Clocks NMI functionality with PMCx value (8), which are :
							 *  [PD7]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (PortPin_Num * 4)); 
							
							break;

				/* Initialize pins for I2C driver */
				case PORT_PIN_MODE_I2C : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config I2C pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to I2C pin */  
							/* 
							 * Config pins with I2C functionality with PMCx value (3), which are :
							 *  [PA6-PA7] - [PB2-PB3] - [PD0-PD1]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000003 << (PortPin_Num * 4)); 
						
							break;

				/* Initialize pins for PWM_0 driver */
				case PORT_PIN_MODE_PWM_0 	: 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config PWM_0  pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num); 
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							       	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to PWM_0 pin */  
							/* 
							 * Config pins with PWM_0 functionality with PMCx value (4), which are :
							 *  [PC4-PC5] - [PB4-PB7] - [PD0-PD2] - [PD6] - [PE4-PE5] - [PF2]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000004 << (PortPin_Num * 4)); 
						
							break;

				/* Initialize pins for PWM_1 driver */
				case PORT_PIN_MODE_PWM_1 	: 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config PWM_1 pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num); 
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							       	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to PWM_1 pin */  
							/* 
							 * Config pins with PWM_0 functionality with PMCx value (5), which are :
							 *   [PD0-PD1] - [PD6] - [PE4-PE5] - [PF0-PF4]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000005 << (PortPin_Num * 4)); 
						
							break;

				/* Initialize pins for USB driver */
				case PORT_PIN_MODE_USB 	: 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config USB pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num); 
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							       	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to USB pin */  
							/* 
							 * Config pins with USB functionality with PMCx value (8), which are :
							 *  [PC6-PC7] - [PD2-PD3] - [PD6] - [PF4]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000008 << (PortPin_Num * 4)); 
				
							break;

				/* Initialize pins for Quadrature Encoder Interface driver. */
				case PORT_PIN_MODE_QEI : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config Quadrature Encoder Interface pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to Quadrature Encoder Interface pin */  
							/* 
							 * Config pins with Quadrature Encoder Interface functionality with PMCx value (6), which are :
							 *  [PC4-PC6] - [PD3] - [PD6-PD7] - [PF0-PF1] -[PF4]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000006 << (PortPin_Num * 4)); 
						
							break;

				/* Initialize pins for JTAG/SWD/SWO driver. */
				case PORT_PIN_MODE_JTAG_SWD_SWO : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to config JTAG/SWD/SWO pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to JTAG/SWD/SWO pin */  
							/* 
							 * Config pins with JTAG/SWD/SWO functionality with PMCx value (1), which are :
							 *  [PC0-PC3]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x00000001 << (PortPin_Num * 4)); 
						
							break;

				/* Initialize pins for Core (Trace) driver. */
				case PORT_PIN_MODE_CORE_TRACE : 
							/* 1- No need to Enable clock for PORT,  port init already handled it.*/
							
							/* 2- for corresponding pins :
											* 2.1 Disable analog functionality 
											* 2.2 Enable Alternative function 
											* 2.3 Enable Digital funtionality
											* 2.4 SET the PMCx (CTL_REG) bits with value to Core (Trace) pin
							*/
										/* 2.1 Disable analog functionality by CLEAR the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
							CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PortPin_Num); 
							
										/* 2.2 Enable Alternative function for this pin by SET the corresponding bit in GPIOAFSEL register */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), PortPin_Num);
										/* 2.3 Enable Digital funtionality on this pin by Clearing the corresponding bit in the GPIODEN register  */
							SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PortPin_Num);  			
							        	
							
										/* 2.4 SET the PMCx (CTL_REG) bits with value to Core (Trace) pin */  
							/* 
							 * Config pins with Core (Trace) functionality with PMCx value (14 = 0xE), which are :
							 *  [PF1-PF3]
							 */
							
							*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= (0x0000000E << (PortPin_Num * 4)); 
						
							break;
							 
				/* In case of Invalid Mode */
				default :	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
										PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);
							break;
						
			}
		}	
	}
	/* MISRA rule, each if has else */
	/* Port Did not Initialized */
	else 
	{
		/* Do Nothing*/
	}	
}
#endif /* PORT_SET_PIN_MODE_API == STD_ON */