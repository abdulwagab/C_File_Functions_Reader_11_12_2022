/*!
 * Project Name: S9KEAZN8_BSW
 *
 * Compiler : CodeWarrior Development Studio V10.6 (arm-none-eabi-gcc-4_7_3)
 *
 *--------------------------------------------------------------------------------------------
 *				 C O P Y R I G H T
 *--------------------------------------------------------------------------------------------
 * Copyright (c) by Body Platform Team, all rights reserved
 *
 *--------------------------------------------------------------------------------------------
 *				 A U T H O R   I D E N T I T Y
 *--------------------------------------------------------------------------------------------
 * Initials 	| Name			| Company 							| E-mail
 * -------------|---------------|-----------------------------------|-------------------------
 * kitewin		| jeonsy		| SL Corporation Body Platform Team	| jeongsy@slworld.com
 *
 *--------------------------------------------------------------------------------------------
 *				 R E V I S I O N   H I S T O R Y
 *--------------------------------------------------------------------------------------------
 * Date         |   Ver		    | Author         | Description
 *--------------|---------------|----------------|-------------
 * 2015-02-05   | 1.00.00	    | jeongsy        | Creation
 *--------------------------------------------------------------------------------------------
*/

/*!
 * @file	drv_adc.c
 * @brief 	S9KEAZN8_BSW adc
 *
 *--------------------------------------------------------------------------------------------
 *				 M E M O R Y    U S A G E
 *--------------------------------------------------------------------------------------------
 * RAM Size                     |   ROM Size
 *------------------------------|------------------------------
 * 256byte                      |   128byte
 *--------------------------------------------------------------------------------------------
*/

#include "bsp_inc.h"

/*--------------------------------------------------------------------------------------------
                                    PreProcessor
--------------------------------------------------------------------------------------------*/
/* none */

/*--------------------------------------------------------------------------------------------
                              DATA STRUCTURE  (ENUMS / STRUCTURES /UNIONS)
--------------------------------------------------------------------------------------------*/
/* none */

/*--------------------------------------------------------------------------------------------
                               GLOBAL VARIABLE DECLARATIONS
--------------------------------------------------------------------------------------------*/
static ADC_StatusType g_ADC_ConverState = ADC_UNINIT;						/**< adc interrupt complete */
static ADC_IrqStatusType g_ADC_IrqState = ADC_IDLE;						/**< adc interrupt complete */

tU16 adc_c_data[(ADC_FIFO_LEVEL<<1)] = {0};		/**< adc conversion complete, get contiuous result vatiable */
static tU16 check_adc[(ADC_FIFO_LEVEL<<1)] = {0};	/**< adc conversion complete, get contiuous result vatiable */

/*--------------------------------------------------------------------------------------------
                                 FUNCTION PROTO TYPE
--------------------------------------------------------------------------------------------*/
/* none */


/*!
 @brief initilize adc driver
 @author jeongsy
 @date 2015-02-05
 @see references function none
 @param[in] none
 @param[out] none
 @param[inout] none
 @exception none
 @return none
 @bug none
*/
void Init_ADC(void)
{
	/*----------------------------------------------------------------------
	-- ADC_APCTL1 	:	Pin Control 1 Register
	------------------------------------------------------------------------
	-- ADPC<15~0>	:	ADC Pin Control
	------------------------------------------------------------------------*/

	ADC_APCTL1 = (tU32)0x00000000
				| (0U << 16)							/* Bit [31~16]	Reserved */
			#ifdef ADC_CH15
				| (ADC_EN << 15)					/* Bit [15]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				|(ADC_DIS << 15)					/* Bit [15]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH15 */
			#ifdef ADC_CH14
				| (ADC_EN << 14)					/* Bit [14]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 14)					/* Bit [14]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH14 */
			#ifdef ADC_CH13
				| (ADC_EN << 13)					/* Bit [13]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 13)					/* Bit [13]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH13 */
			#ifdef ADC_CH12
				| (ADC_EN << 12)					/* Bit [12]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 12)					/* Bit [12]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH12 */
			#ifdef ADC_CH11
				| (ADC_EN << 11)					/* Bit [11]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 11)					/* Bit [11]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH11 */
			#ifdef ADC_CH10
				| (ADC_EN << 10)					/* Bit [10]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 10)					/* Bit [10]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH10 */
			#ifdef ADC_CH9
				| (ADC_EN << 9)						/* Bit [9]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 9)					/* Bit [9]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH9 */
			#ifdef ADC_CH8
				| (ADC_EN << 8)						/* Bit [8]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 8)					/* Bit [8]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH8 */
			#ifdef ADC_CH7
				| (ADC_EN << 7)						/* Bit [7]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 7)					/* Bit [7]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH7 */
			#ifdef ADC_CH6
				| (ADC_EN << 6)						/* Bit [6]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 6)					/* Bit [6]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH6 */
			#ifdef ADC_CH5
				| (ADC_EN << 5)						/* Bit [5]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 5)					/* Bit [5]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH5 */
			#ifdef ADC_CH4
				| (ADC_EN << 4)						/* Bit [4] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 4)					/* Bit [4] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH4 */
			#ifdef ADC_CH3
				| (ADC_EN << 3)						/* Bit [3] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 3)					/* Bit [3] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH3 */
			#ifdef ADC_CH2
				| (ADC_EN << 2)						/* Bit [2] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 2)					/* Bit [2] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH2 */
			#ifdef ADC_CH1
				| (ADC_EN << 1)						/* Bit [1] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 1)					/* Bit [1] 		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH1 */
			#ifdef ADC_CH0
				| (ADC_EN << 0); 					/* Bit [0]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#else
				| (ADC_DIS << 0); 					/* Bit [0]		0:ADx pin I/O control enabled 1:ADx pin I/O control disabled */
			#endif /* ADC_CH0 */





	/*----------------------------------------------------------------------
	-- ADC_SC3 		:	Status and Control Register 2
	------------------------------------------------------------------------
	-- ADLPC<7>		:	Compare Function Enable
	-- ADIV<6~5>	:	Compare Function Greater Than Enable
	-- ADLSMP<4>	:	Long Sample Time Configuration
	-- MODE<3~2>	:	Result FIFO full
	-- ADICLK<1~0>	:	Voltage Reference Selection
	------------------------------------------------------------------------*/
	ADC_SC3 = (tU32)0x00000000
			| (0U << 8)						/* Bit [31~8]	Reserved */
			| (0U << 7)						/* Bit [7] 		ADLPC 0:High speed configuration 1:Low power configuration */
			| (ADC_Input_clk_by2 << 5)		/* Bit [6~5] 	ADIV
				00:Divide ration = 1, and clock rate = Input clock
				01:Divide ration = 2, and clock rate = Input clock �� 2
				10:Divide ration = 3, and clock rate = Input clock �� 4
				11: Divide ration = 4, and clock rate = Input clock �� 8*/
			| (1U << 4)						/* Bit [4] 		ADLSMP 0:Short sample time 1:Long sample time */
			| (ADC_10bit << 2)				/* Bit [3~2] 	MODE
				00 		8-bit conversion (N = 8)
				01		10-bit conversion (N = 10)
				10		12-bit conversion (N = 12)
				11 		Reserved*/
			| (ADC_Dividedby2 << 0); 		/* Bit [1~0]	ADICLK
				00    	Bus clock
				01    	Bus clock divided by 2
				10    	Alternate clock (ALTCLK)
				11 		Asynchronous clock (ADACK)*/

	/*----------------------------------------------------------------------
	-- ADC_SC4 		:	Status and Control Register 4
	------------------------------------------------------------------------
	-- HTRGME<8>	:	Hardware Trigger Multiple Conversion Enable
	-- ASCANE<6>	:	FIFO Scan Mode Enable
	-- ACFSEL<5>	:	Compare Function Selection
	-- AFDEP<2~0>	:	FIFO Depth
	------------------------------------------------------------------------*/
	ADC_SC4 = (tU32)0x00000000
			| (0U << 9)						/* Bit [31~9]	Reserved */
			| (0U << 8)						/* Bit [8]		HTRGME 0: One hardware trigger pulse triggers one conversion 1:One hardware trigger pulse triggers multiple conversions in fifo mode */
			| (0U << 7)						/* Bit [7] 		Reserved */
		#ifdef ADC_FIFO_SCAN_MODE
			| (1U << 6)						/* Bit [6]	 	ASCANE 0:FIFO scan mode disabled 1: FIFO scan mode enabled */
		#else
			| (0U << 6)						/* Bit [6]	 	ASCANE 0:FIFO scan mode disabled 1: FIFO scan mode enabled */
		#endif /*ADC_FIFO_SCAN_MODE*/
			| (0U << 5)						/* Bit [5] 		ACFSEL 0:OR all of compare trigger 1:AND all of compare trigger */
			| (0U << 3)						/* Bit [4~3] 	Reserved */
		#ifdef ADC_FIFO_DISABLE
			| (ADC_FIFO_DISABLE<< 0);
		#endif/* ADC_FIFO_DISABLE */
		#ifdef ADC_FIFO_2
			| (ADC_FIFO_2<< 0);
		#endif/* ADC_FIFO_2 */
		#ifdef ADC_FIFO_3
			| (ADC_FIFO_3<< 0);
		#endif/* ADC_FIFO_3 */
		#ifdef ADC_FIFO_4
			| (ADC_FIFO_4<< 0);
		#endif/* ADC_FIFO_4 */
		#ifdef ADC_FIFO_5
			| (ADC_FIFO_5<< 0);
		#endif/* ADC_FIFO_5 */
		#ifdef ADC_FIFO_6
			| (ADC_FIFO_6<< 0);
		#endif/* ADC_FIFO_6 */
		#ifdef ADC_FIFO_7
			| (ADC_FIFO_7<< 0);
		#endif/* ADC_FIFO_7 */
		#ifdef ADC_FIFO_8
			| (ADC_FIFO_8<< 0);
		#endif/* ADC_FIFO_8 */

		#ifdef ADC_FIFO_LEVEL
			| ((ADC_FIFO_LEVEL-1U)<< 0);
		#endif/* ADC_FIFO_LEVEL */
											/* Bit [1~0]	AFDEP
													000    FIFO is disabled.
													001    2-level FIFO is enabled
													010    3-level FIFO is enabled
													011    4-level FIFO is enabled
													100    5-level FIFO is enabled
													101    6-level FIFO is enabled
													110    7-level FIFO is enabled
													111    8-level FIFO is enabled*/

	/*----------------------------------------------------------------------
	-- ADC_CV 		:	Compare Value Register
	------------------------------------------------------------------------
	-- CV<11~0>		:	Conversion Result
	------------------------------------------------------------------------*/
	ADC_CV = (tU32)0x00000000
			| (0U << 12)						/* Bit [31~12] 	Reserved */
			| (ADC_COMPARE_VAULE << 0); 	/* Bit [11~0]	CV Conversion Result[11:0]*/

	/*----------------------------------------------------------------------
	-- ADC_SC2 		:	Status and Control Register 2
	------------------------------------------------------------------------
	-- ADACT<7>		:	Conversion Active
	-- ADTRG<6>		:	Conversion Trigger Select
	-- ACFE<5>		:	Compare Function Enable
	-- ACFGT<4>		:	Compare Function Greater Than Enable
	-- FEMPTY<3>	:	Result FIFO empty
	-- FFULL<2>		:	Result FIFO full
	-- REFSEL<1~0>	:	Voltage Reference Selection
	------------------------------------------------------------------------*/
	ADC_SC2 = (tU32)0x00000000
			| (0U << 8)						/* Bit [31~8]	Reserved */
			| (0U << 7)						/* Bit [7]		ADACT 0:Conversion not in progress 1:Conversion in progress*/
		#ifdef ADC_SWT
			| (0U << 6)						/* Bit [6] 		ADTRG 0:Software trigger selected 1: Hardware trigger selected*/
		#endif/**/
		#ifdef ADC_HWT
			| (1U << 6)						/* Bit [6] 		ADTRG 0:Software trigger selected 1: Hardware trigger selected*/
		#endif/**/
			| (0U << 5)						/* Bit [5] 		ACFE 0:Compare function disabled 1:Compare function enabled*/
			| (1U << 4)						/* Bit [4] 		ACFGT 0:Compare triggers when input is less than compare level 1:Compare triggers when input is greater than or equal to compare level */
			| (0U << 3)						/* Bit [3] 		FEMPTY 0:Indicates that ADC result FIFO have at least one valid new data 1:Indicates that ADC result FIFO have no valid new data */
			| (0U << 2)						/* Bit [2] 		FFULL 0:Indicates that ADC result FIFO is not full and next conversion data still can be stored into FIFO 1:indicates that ADC result FIFO is full and next conversion will override old data in case of no read action */
			| (VREFH_VREFL << 0); 			/* Bit [1~0]	REFSEL
				00    	Default voltage reference pin pair (VREFH/VREFL)
				01    	Analog supply pin pair (VDDA/VSSA).
				10    	Reserved
				11 		Reserved*/

	/*----------------------------------------------------------------------
	-- ADC_SC1		:	Status and Control Register 1
	------------------------------------------------------------------------
	-- COCO<7>		:	Conversion Complete Flag
	-- AIEN<6>		:	Interrupt Enable
	-- ADCO<5>		:	Continuous Conversion Enable
	-- ADCH<4~0>	:	Input Channel Select
	------------------------------------------------------------------------*/

	/* interrupt disable */
	(void)BME_LAC1_32B(&ADC_SC1,6); /* Bit [6]			AIEN 0:Conversion complete interrupt disabled 1:Conversion complete interrupt enabled */

	/* one shot */
	(void)BME_LAC1_32B(&ADC_SC1,5); /* Bit [5]			ADCO 0:One conversion 1:Continuous conversions */

	(void)BME_BFI_32B(&ADC_SC1, ADC_DISABLE, 0, 5);

	g_ADC_ConverState = (ADC_StatusType)ADC_INIT;
}


/*!
 @brief get adc single fifo data
 @author jeongsy
 @date 2016-03-09
 @see references function
 @param[in] none
 @param[out] none
 @param[inout] none
 @exception none
 @return none
 @bug none
*/
void Get_S_ADC(void)
{

	tU08 get_adc_index;

	/* adc conversion time check */

	/*----------------------------------------------------------------------
	-- ADC_SC1		:	Status and Control Register 1
	------------------------------------------------------------------------
	-- COCO<7>		:	Conversion Complete Flag
	-- AIEN<6>		:	Interrupt Enable
	-- ADCO<5>		:	Continuous Conversion Enable
	-- ADCH<4~0>	:	Input Channel Select
	------------------------------------------------------------------------*/

	/* one shot */
	(void)BME_LAC1_32B(&ADC_SC1,5U); /* Bit [5]			ADCO 0:One conversion 1:Continuous conversions */

	/* interrupt disable */
	(void)BME_LAC1_32B(&ADC_SC1,6U); /* Bit [6]			AIEN 0:Conversion complete interrupt disabled 1:Conversion complete interrupt enabled */


#ifdef ADC_CH0
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH0, 0U, 5U);
#endif/*ADC_CH0*/

#ifdef ADC_CH1
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH1, 0U, 5U);
#endif/*ADC_CH1*/

#ifdef ADC_CH2
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH2, 0U, 5U);
#endif/*ADC_CH2*/

#ifdef ADC_CH3
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH3, 0U, 5U);
#endif/*ADC_CH3*/

#ifdef ADC_CH4
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH4, 0U, 5U);
#endif/*ADC_CH4*/

#ifdef ADC_CH5
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH5, 0U, 5U);
#endif/*ADC_CH5*/

#ifdef ADC_CH6
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH6, 0U, 5U);
#endif/*ADC_CH6*/

#ifdef ADC_CH7
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH7, 0U, 5U);
#endif/*ADC_CH7*/

#ifdef ADC_CH8
		(void)BME_BFI_32B(&ADC_SC1, ADC_CH8, 0U, 5U);
#endif/*ADC_CH8*/

#ifdef ADC_CH9
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH9, 0U, 5U);
#endif/*ADC_CH9*/


#ifdef ADC_CH10
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH10, 0U, 5U);
#endif/*ADC_CH10*/

#ifdef ADC_CH11
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH11, 0U, 5U);
#endif/*ADC_CH11*/


	while(((ADC_SC1 & (tU32)0x80) >> 7U) != 1U)
	{
		__asm("nop");
	}

	/* adc conversion time check */

	
	for(get_adc_index=0; get_adc_index < ADC_FIFO_LEVEL; get_adc_index++)
	{
		check_adc[get_adc_index] = (tU16)ADC_R_ADR(ADC_R);

		if(check_adc[(tU16)get_adc_index]<=1023U)
		{
			adc_c_data[get_adc_index] = check_adc[get_adc_index];
		}
		else
		{
			adc_c_data[get_adc_index] = adc_c_data[get_adc_index];
		}
	}

	(void)BME_BFI_32B(&ADC_SC1, ADC_DISABLE, 0U, 5U);

	/* sw trigger delay*/
	__asm("nop");




#ifdef ADC_CH12
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH12, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH13
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH13, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH14
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH14, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH15
	(void)BME_BFI_32B(&ADC_SC1, ADC_CH15, 0U, 5U);
#endif/*ADC_CH11*/


#ifdef ADC_Temperature
	(void)BME_BFI_32B(&ADC_SC1, ADC_Temperature, 0U, 5U);
#endif/*ADC_Temperature*/

#ifdef ADC_Bandgap
	(void)BME_BFI_32B(&ADC_SC1, ADC_Bandgap, 0U, 5U);
#endif/*ADC_Bandgap*/

#ifdef ADC_V_REFH
	(void)BME_BFI_32B(&ADC_SC1, ADC_V_REFH, 0, 5);
#endif/*ADC_V_REFH*/

#ifdef ADC_V_REFL
	(void)BME_BFI_32B(&ADC_SC1, ADC_V_REFL, 0U, 5U);
#endif/*ADC_V_REFL*/

	/* adc conversion time check */


	while(((ADC_SC1 & (tU32)0x80) >> 7U) != 1U)
	{
		__asm("nop");
	}

	/* adc conversion time check */


	for(get_adc_index=ADC_FIFO_LEVEL; get_adc_index < (ADC_FIFO_LEVEL<<1); get_adc_index++)
	{
		check_adc[get_adc_index] = (tU16)ADC_R_ADR(ADC_R);

		if(check_adc[(tU16)get_adc_index]<=1023U)
		{
			adc_c_data[get_adc_index] = check_adc[get_adc_index];
		}
		else
		{
			adc_c_data[get_adc_index] = adc_c_data[get_adc_index];
		}
	}

	(void)BME_BFI_32B(&ADC_SC1, ADC_DISABLE, 0U, 5U);

	/* adc conversion time check */




}



/*!
 @brief get adc continuous fifo data
 @author jeongsy
 @date 2016-03-09
 @see references function
 @param[in] none
 @param[out] none
 @param[inout] none
 @exception none
 @return none
 @bug none
*/
void Start_C_ADC(void)
{

		if((((ADC_SC2&ADC_SC2_ADACT_MASK)) >> ADC_SC2_ADACT_SHIFT) == 0U)
		{
			if((g_ADC_ConverState == (ADC_StatusType)ADC_INIT) && (g_ADC_IrqState == (ADC_IrqStatusType)ADC_IDLE))
			{
				/* Interrupt Mode Enable */
				(void)BME_LAS1_32B(&ADC_SC1,6); /* Bit [6]			AIEN 0:Conversion complete interrupt disabled 1:Conversion complete interrupt enabled */

				/* one shot */
				(void)BME_LAC1_32B(&ADC_SC1,5); /* Bit [5]			ADCO 0:One conversion 1:Continuous conversions */

#ifdef ADC_CH0
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH0, 0U, 5U);
#endif/*ADC_CH0*/

#ifdef ADC_CH1
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH1, 0U, 5U);
#endif/*ADC_CH1*/

#ifdef ADC_CH2
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH2, 0U, 5U);
#endif/*ADC_CH2*/

#ifdef ADC_CH3
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH3, 0U, 5U);
#endif/*ADC_CH3*/

#ifdef ADC_CH4
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH4, 0U, 5U);
#endif/*ADC_CH4*/

#ifdef ADC_CH5
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH5, 0U, 5U);
#endif/*ADC_CH5*/

#ifdef ADC_CH6
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH6, 0U, 5U);
#endif/*ADC_CH6*/

#ifdef ADC_CH7
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH7, 0U, 5U);
#endif/*ADC_CH7*/

#ifdef ADC_CH8
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH8, 0U, 5U);
#endif/*ADC_CH8*/

#ifdef ADC_CH9
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH9, 0U, 5U);
#endif/*ADC_CH9*/

#ifdef ADC_CH10
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH10, 0U, 5U);
#endif/*ADC_CH10*/

#ifdef ADC_CH11
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH11, 0U, 5U);
#endif/*ADC_CH11*/


				g_ADC_IrqState = ADC_READY;




			}

			else if((g_ADC_ConverState == (ADC_StatusType)ADC_1st_FLG) && (g_ADC_IrqState == (ADC_IrqStatusType)ADC_IDLE))
			{
				/* Interrupt Mode Enable */
				(void)BME_LAS1_32B(&ADC_SC1,6U); /* Bit [6]		AIEN 0:Conversion complete interrupt disabled 1:Conversion complete interrupt enabled */

				/* one shot */
				(void)BME_LAC1_32B(&ADC_SC1,5U); /* Bit [5]			ADCO 0:One conversion 1:Continuous conversions */




#ifdef ADC_CH12
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH12, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH13
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH13, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH14
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH14, 0U, 5U);
#endif/*ADC_CH11*/

#ifdef ADC_CH15
			(void)BME_BFI_32B(&ADC_SC1, ADC_CH15, 0U, 5U);
#endif/*ADC_CH11*/


#ifdef ADC_Temperature
		(void)BME_BFI_32B(&ADC_SC1, ADC_Temperature, 0U, 5U);
#endif/*ADC_Bandgap*/

#ifdef ADC_Bandgap
			(void)BME_BFI_32B(&ADC_SC1, ADC_Bandgap, 0U, 5U);
#endif/*ADC_Bandgap*/

#ifdef ADC_V_REFH
			(void)BME_BFI_32B(&ADC_SC1, ADC_V_REFH, 0U, 5U);
#endif/*ADC_V_REFH*/

#ifdef ADC_V_REFL
			(void)BME_BFI_32B(&ADC_SC1, ADC_V_REFL, 0U, 5U);
#endif/*ADC_V_REFL*/

			g_ADC_IrqState = (ADC_IrqStatusType)ADC_READY;

			}


			else
			{
				g_ADC_IrqState = (ADC_IrqStatusType)ADC_IDLE;
				g_ADC_ConverState = (ADC_StatusType)ADC_INIT;
			}
		}
		else
		{
			__asm("nop");
		}

}

/*!
 @brief get adc single fifo data
 @author jeongsy
 @date 2016-03-09
 @see references function
 @param[in] none
 @param[out] none
 @param[inout] none
 @exception none
 @return none
 @bug none
*/
void ADC_Int_handler(void)
{
		tU08 get_adc_index;

		/* Interrupt call Time 70us */

		/* Interrupt Operation Time 10us */


		if((g_ADC_ConverState == (ADC_StatusType)ADC_INIT) && (g_ADC_IrqState == (ADC_IrqStatusType)ADC_READY))
		{
			if(((ADC_SC1&(tU32)0x80)>>7U) == 1U)
			{
				g_ADC_IrqState = ADC_DURING;

				for(get_adc_index=0; get_adc_index < ADC_FIFO_LEVEL; get_adc_index++)
				{
					check_adc[get_adc_index] = (tU16)ADC_R_ADR(ADC_R);

					if(check_adc[(tU16)get_adc_index]<=1023U)
					{
						adc_c_data[get_adc_index] = check_adc[get_adc_index];
					}
					else
					{
						adc_c_data[get_adc_index] = adc_c_data[get_adc_index];
					}
				}

				(void)BME_BFI_32B(&ADC_SC1, ADC_DISABLE, 0, 5);

/*----------------------------------------------------------------------------------------------*/

				g_ADC_ConverState = (ADC_StatusType)ADC_1st_FLG;

				if(g_ADC_IrqState == (ADC_IrqStatusType)ADC_DURING)
				{
					g_ADC_IrqState =(ADC_IrqStatusType)ADC_IDLE;
				}


				/* adc conversion time check */

			}
			else
			{
				__asm("nop");
				g_ADC_IrqState = (ADC_IrqStatusType)ADC_IDLE;
				g_ADC_ConverState = (ADC_StatusType)ADC_INIT;

			}
		}

		else if((g_ADC_ConverState == (ADC_StatusType)ADC_1st_FLG) && (g_ADC_IrqState == (ADC_IrqStatusType)ADC_READY))
		{
			if(((ADC_SC1&(tU32)0x80)>>7U) == 1U)
			{

				g_ADC_IrqState = (ADC_IrqStatusType)ADC_DURING;

				for(get_adc_index=ADC_FIFO_LEVEL; get_adc_index < (ADC_FIFO_LEVEL<<1); get_adc_index++)
				{
					check_adc[get_adc_index] = (tU16)ADC_R_ADR(ADC_R);

					if(check_adc[(tU16)get_adc_index]<=1023U)
					{
						adc_c_data[get_adc_index] = check_adc[get_adc_index];
					}
					else
					{
						adc_c_data[get_adc_index] = adc_c_data[get_adc_index];
					}
				}

				(void)BME_BFI_32B(&ADC_SC1, ADC_DISABLE, 0U, 5U);

				/* sw trigger delay*/
				__asm("nop");

/*----------------------------------------------------------------------------------*/
				g_ADC_ConverState = (ADC_StatusType)ADC_INIT;

				if(g_ADC_IrqState == (ADC_IrqStatusType)ADC_DURING)
				{
					g_ADC_IrqState = (ADC_IrqStatusType)ADC_IDLE;
				}

				/* adc conversion time check */

			}
			else
			{
				__asm("nop");
				g_ADC_IrqState = (ADC_IrqStatusType)ADC_IDLE;
				g_ADC_ConverState = (ADC_StatusType)ADC_INIT;
			}
		}
		else
		{
			__asm("nop");
			g_ADC_IrqState = (ADC_IrqStatusType)ADC_IDLE;
			g_ADC_ConverState = (ADC_StatusType)ADC_INIT;
		}


}






/*!
 @brief Check ADC Reference Voltage
 @author jeongsy
 @date 2016-07-01
 @see references function
 @param[in] none
 @param[out] none
 @param[inout] none
 @exception none
 @return none
 @bug none
*/
void Check_ADCRef(void)
{	
	tU16 ref_dif ;
	tU08 refcheck;
	tU08 refcount = RefTimeout;

	while((refcount != 0U))
	{
		Get_S_ADC();

		ref_dif = adc_c_data[(ADC_FIFO_LEVEL<<1)-2U] - adc_c_data[(ADC_FIFO_LEVEL<<1)-1U]; /* IVREFH - IVREFL */

		if(ref_dif > REFdiff)  /* 1020 */
		{
			if((adc_c_data[(ADC_FIFO_LEVEL<<1)-3U] >= IVBANDGAP_L) && (adc_c_data[(ADC_FIFO_LEVEL<<1)-3U] <= IVBANDGAP_H))  /* if((IVBANDGAP >= 230) || IVBANDGAP <= 245)) */
			{
				refcheck = 1U;
			}
			else
			{
				refcheck = 0U;
			}
		}

		else
		{
			refcheck = 0U;
		}

		refcount--;


		if(refcheck == 1U)
		{
			break;
		}
		else
		{
			__asm("nop");
		}

	}
}








