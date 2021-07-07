/** 
 **************************************************************
 * @file mylib/s4459843_reg_lta1000g.c
 * @author Yang Zheng - 44598435
 * @date 14032021
 * @brief LTA 1000g LED bar display
*         mylib register driver
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************

 *************************************************************** 
 */
#include "s4459843_reg_lta1000g.h"


void s4459843_reg_lta1000g_init(void){
    BRD_LEDInit();		//Initialise LEDS
	BRD_LEDBlueOff();

	// Enable the GPIO C,B,A Clock
   __GPIOC_CLK_ENABLE();
   __GPIOB_CLK_ENABLE();
   __GPIOA_CLK_ENABLE();

  //Initialise PC6 as an output.
  GPIOC->MODER &= ~(0x03 << (6 * 2));  //clear bits
  GPIOC->MODER |= (0x01 << (6 * 2));   //Set for push pull

  GPIOC->OSPEEDR &= ~(0x03<<(6 * 2));
  GPIOC->OSPEEDR |=   0x02<<(6 * 2);  // Set for Fast speed

  GPIOC->OTYPER &= ~(0x01 << 6);       //Clear Bit for Push/Pull utput

  //Initialise PB15 as an output.
  GPIOB->MODER &= ~(0x03 << (15 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (15 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(15 * 2));
  GPIOB->OSPEEDR |=   0x02<<(15 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 15);       //Clear Bit for Push/Pull utput

  //Initialise PB13 as an output.
  GPIOB->MODER &= ~(0x03 << (13 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (13 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(13 * 2));
  GPIOB->OSPEEDR |=   0x02<<(13 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 13);       //Clear Bit for Push/Pull utput

  //Initialise PB12 as an output.
  GPIOB->MODER &= ~(0x03 << (12 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (12 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(12 * 2));
  GPIOB->OSPEEDR |=   0x02<<(12 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 12);       //Clear Bit for Push/Pull utput

  //Initialise PA15 as an output.
  GPIOA->MODER &= ~(0x03 << (15 * 2));  //clear bits
  GPIOA->MODER |= (0x01 << (15 * 2));   //Set for push pull

  GPIOA->OSPEEDR &= ~(0x03<<(15 * 2));
  GPIOA->OSPEEDR |=   0x02<<(15 * 2);  // Set for Fast speed

  GPIOA->OTYPER &= ~(0x01 << 15);       //Clear Bit for Push/Pull utput

  //Initialise PC7 as an output.
  GPIOC->MODER &= ~(0x03 << (7 * 2));  //clear bits
  GPIOC->MODER |= (0x01 << (7 * 2));   //Set for push pull

  GPIOC->OSPEEDR &= ~(0x03<<(7 * 2));
  GPIOC->OSPEEDR |=   0x02<<(7 * 2);  // Set for Fast speed

  GPIOC->OTYPER &= ~(0x01 << 7);       //Clear Bit for Push/Pull utput

  //Initialise PB5 as an output.
  GPIOB->MODER &= ~(0x03 << (5 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (5 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(5 * 2));
  GPIOB->OSPEEDR |=   0x02<<(5 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 5);       //Clear Bit for Push/Pull utput

  //Initialise PB3 as an output.
  GPIOB->MODER &= ~(0x03 << (3 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (3 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(3 * 2));
  GPIOB->OSPEEDR |=   0x02<<(3 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 3);       //Clear Bit for Push/Pull utput

  //Initialise PA4 as an output.
  GPIOA->MODER &= ~(0x03 << (4 * 2));  //clear bits
  GPIOA->MODER |= (0x01 << (4 * 2));   //Set for push pull

  GPIOA->OSPEEDR &= ~(0x03<<(4 * 2));
  GPIOA->OSPEEDR |=   0x02<<(4 * 2);  // Set for Fast speed

  GPIOA->OTYPER &= ~(0x01 << 4);       //Clear Bit for Push/Pull utput

   //Initialise PB4 as an output.
  GPIOB->MODER &= ~(0x03 << (4 * 2));  //clear bits
  GPIOB->MODER |= (0x01 << (4 * 2));   //Set for push pull

  GPIOB->OSPEEDR &= ~(0x03<<(4 * 2));
  GPIOB->OSPEEDR |=   0x02<<(4 * 2);  // Set for Fast speed

  GPIOB->OTYPER &= ~(0x01 << 4);       //Clear Bit for Push/Pull utput
}
//PC6;PB15;  PB13;PB12;PA15;PC7;  PB5;PB3;PA4;PB4
void s4459843_reg_lta1000g_write_value_h2bit(uint16_t hex_value)
{
	if((hex_value & 0x02) == 0x02) //hex=xxxxxx1x
	{
		//PC6 On
		GPIOC->ODR |= (0x01 << 6);
	}
	else
	{
		//PC6 Off
		GPIOC->ODR &= ~(0x01 << 6); 
	}
	if((hex_value & 0x01) == 0x01) //hex=xxxxxxx1
	{
		//PB15 On
		GPIOB->ODR |= (0x01 << 15);
	}
	else
	{
		//PB15 Off
		GPIOB->ODR &= ~(0x01 << 15); 
	}
}
void s4459843_reg_lta1000g_write_value_8bit(uint16_t hex_value)
{
	if((hex_value & 0x80) == 0x80) //hex=1xxxxxxx
	{
		//PB13 On
		GPIOB->ODR |= (0x01 << 13);
	}
	else
	{
		//PB13 Off
		GPIOB->ODR &= ~(0x01 << 13); 
	}
	if((hex_value & 0x40) == 0x40) //hex=x1xxxxxx
	{
		//PB12 On
		GPIOB->ODR |= (0x01 << 12);
	}
	else
	{
		//PB12 Off
		GPIOB->ODR &= ~(0x01 << 12); 
	}
	if((hex_value & 0x20) == 0x20) //hex=xx1xxxxx
	{
		//PA15 On
		GPIOA->ODR |= (0x01 << 15);
	}
	else
	{
		//PA15 Off
		GPIOA->ODR &= ~(0x01 << 15); 
	}
	if((hex_value & 0x10) == 0x10) //hex=xxx1xxxx
	{
		//PC7 On
		GPIOC->ODR |= (0x01 << 7);
	}
	else
	{
		//PC7 Off
		GPIOC->ODR &= ~(0x01 << 7); 
	}
	
	
	if((hex_value & 0x08) == 0x08) //hex=1xxx
	{
		//PB5 On
		GPIOB->ODR |= (0x01 << 5);
	}
	else
	{
		//PB5 Off
		GPIOB->ODR &= ~(0x01 << 5); 
	}
	
	if((hex_value & 0x04) == 0x04) //hex=x1xx
	{
		//PB3 On
		GPIOB->ODR |= (0x01 << 3);
	}
	else
	{
		//PB3 Off
		GPIOB->ODR &= ~(0x01 << 3); 
	}
	
	if((hex_value & 0x02) == 0x02) //hex=xx1x
	{
		//PA4 On
		GPIOA->ODR |= (0x01 << 4);
	}
	else
	{
		//PA4 Off
		GPIOA->ODR &= ~(0x01 << 4);
	}
	if((hex_value & 0x01) == 0x01) //hex=xxx1 
	{
		//PB4 On
		GPIOB->ODR |= (0x01 << 4);
	}
	else
	{
		//PB4 Off
		GPIOB->ODR &= ~(0x01 << 4);
	}
}
void s4459843_reg_lta1000g_write_value(unsigned char hex_value)
{
	if((hex_value & 0x08) == 0x08) //hex=1xxx
	{
		//PB5 On
		GPIOB->ODR |= (0x01 << 5);
	}
	else
	{
		//PB5 Off
		GPIOB->ODR &= ~(0x01 << 5); 
	}
	
	if((hex_value & 0x04) == 0x04) //hex=x1xx
	{
		//PB3 On
		GPIOB->ODR |= (0x01 << 3);
	}
	else
	{
		//PB3 Off
		GPIOB->ODR &= ~(0x01 << 3); 
	}
	
	if((hex_value & 0x02) == 0x02) //hex=xx1x
	{
		//PA4 On
		GPIOA->ODR |= (0x01 << 4);
	}
	else
	{
		//PA4 Off
		GPIOA->ODR &= ~(0x01 << 4);
	}
	if((hex_value & 0x01) == 0x01) //hex=xxx1 
	{
		//PB4 On
		GPIOB->ODR |= (0x01 << 4);
	}
	else
	{
		//PB4 Off
		GPIOB->ODR &= ~(0x01 << 4);
	}
}
/*void s4459843_reg_lta1000g_write_keypad(void)
{
	int keypadstatus;
	unsigned char keypressed_value;
	keypadstatus=s4459843_reg_keypad_read_status();
	keypressed_value=s4459843_reg_keypad_read_hex();
	if(keypadstatus==1)
	{
		s4459843_reg_lta1000g_write_value_h2bit(0x00);
		s4459843_reg_lta1000g_write_value_8bit(keypressed_value);
		if(keypressed_value==0x0e)//pressed E
		{
			buffer1= (buffer1<<4)| keypressed_value;
		}
		else if(keypressed_value==0x0d)//pressed D
		{
			buffer1= (buffer1<<4)| keypressed_value;
		}
		else if(keypressed_value==0x0f)//pressed F
		{
			buffer1= (buffer1<<4)| keypressed_value;
		}
		else
		{
			buffer1=0x00;
		}
		//buffer2 AE   press F  buffer2 EF
		buffer2 = (buffer2<<4)| keypressed_value;//Record the recent 2 key pressed hex value
		//EyFy
		buffer2_Encode=s4459843_lib_hamming_byte_encode(buffer2);//Compute encode value for the the 2 recent data input
		buffer2_Decode=s4459843_lib_hamming_byte_decode(((buffer2 & 0xf0) >> 4)| ((buffer2 & 0x0f) << 4));
		//Hamming FSM changing
		if( (buffer1==0xee) && (s4459843_lib_hammingFsm_read_status()!=ENCODE_STATE) )
		{
			s4459843_lib_hamming_fsmprocessing(ENCODE_STATE);//Change the state to encode
			BRD_LEDBlueOn();
			BRD_LEDRedOff();
			BRD_LEDGreenOff();
			buffer1=0x00;//refresh buffer after each changing state
			buffer2=0x00;
		}
		if( (buffer1==0xdd) && (s4459843_lib_hammingFsm_read_status()!=DECODE_STATE) )
		{
			s4459843_lib_hamming_fsmprocessing(DECODE_STATE);//Change the state to decode
			BRD_LEDBlueOff();
			BRD_LEDRedOn();
			BRD_LEDGreenOff();
			buffer1=0x00;//refresh buffer after each changing state
			buffer2=0x00;
		}
		if( (buffer1==0xff) && (s4459843_lib_hammingFsm_read_status()!=IDLE_STATE) )
		{
			s4459843_lib_hamming_fsmprocessing(IDLE_STATE);//Change the state to idle
			BRD_LEDBlueOff();
			BRD_LEDRedOff();
			BRD_LEDGreenOn();
			buffer1=0x00;//refresh buffer after each changing state
			buffer2=0x00;
		}
	}
	else
	{
		if(s4459843_lib_hammingFsm_read_status()==IDLE_STATE)
		{
			s4459843_reg_lta1000g_write_value_8bit(0x00);//When it is on idle state, and no key pressed, nothing will be display
		}
		if(s4459843_lib_hammingFsm_read_status()==ENCODE_STATE)//x1x1x1x1y1y1y1y1   x2x2x2x2y2y2y2y2
		{
			if(highorlow==0)//Low 4 bits
			{
				s4459843_reg_lta1000g_write_value_8bit((uint8_t)(buffer2_Encode & 0x00FF));//When it is on encode state, and no key pressed, encode value of buffer2 will be displayed
			}
			else//High 4 bits
			{
				s4459843_reg_lta1000g_write_value_8bit((uint8_t)((buffer2_Encode & 0xFF00) >> 8));//When it is on encode state, and no key pressed, encode value of buffer2 will be displayed
			}
		}
		if(s4459843_lib_hammingFsm_read_status()==DECODE_STATE)//x1x1x1x1y1y1y1y1
		{
			s4459843_reg_lta1000g_write_value_8bit( ((buffer2 & 0xf0) >> 4)| ((buffer2 & 0x0f) << 4));//When it is on decode state, and no key pressed, data bit of buffer2 will be displayed
			s4459843_reg_lta1000g_write_value_h2bit(buffer2_Decode);
		}
	}
}
*/
/*
void s4459843_reg_lta1000g_write1(void){
    GPIOC->ODR |= (0x01 << 6);   //Set the bit in the ODR
    GPIOB->ODR |= (0x01 << 15);
    HAL_Delay(1000);		//Delay for 1s

    GPIOC->ODR &= ~(0x01 << 6);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 15);
    GPIOB->ODR |= (0x01 << 13);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 15);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 13);
    GPIOB->ODR |= (0x01 << 12);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 13);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 12);
    GPIOA->ODR |= (0x01 << 15);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 12);   //Clear the bit in the ODR
    GPIOA->ODR |= (0x01 << 15);
    GPIOC->ODR |= (0x01 << 7);
    HAL_Delay(1000);

    GPIOA->ODR &= ~(0x01 << 15);   //Clear the bit in the ODR
    GPIOC->ODR |= (0x01 << 7);
    GPIOB->ODR |= (0x01 << 5);
    HAL_Delay(1000);

    GPIOC->ODR &= ~(0x01 << 7);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 5);
    GPIOB->ODR |= (0x01 << 3);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 5);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 3);
    GPIOA->ODR |= (0x01 << 4);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 3);   //Clear the bit in the ODR
    GPIOA->ODR |= (0x01 << 4);
    GPIOB->ODR |= (0x01 << 4);
    HAL_Delay(1000);

    GPIOA->ODR &= ~(0x01 << 4);   //Clear the bit in the ODR
    GPIOB->ODR &= ~(0x01 << 4);   //Clear the bit in the ODR
    HAL_Delay(1000);
}

void s4459843_reg_lta1000g_write2(){
    GPIOB->ODR |= (0x01 << 4);   //Set the bit in the ODR
    GPIOA->ODR |= (0x01 << 4);
    HAL_Delay(1000);		//Delay for 1s

    GPIOB->ODR &= ~(0x01 << 4);   //Clear the bit in the ODR
    GPIOA->ODR |= (0x01 << 4);
    GPIOB->ODR |= (0x01 << 3);
    HAL_Delay(1000);

    GPIOA->ODR &= ~(0x01 << 4);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 3);
    GPIOB->ODR |= (0x01 << 5);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 3);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 5);
    GPIOC->ODR |= (0x01 << 7);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 5);   //Clear the bit in the ODR
    GPIOA->ODR |= (0x01 << 15);
    GPIOC->ODR |= (0x01 << 7);
    HAL_Delay(1000);

    GPIOC->ODR &= ~(0x01 << 7);   //Clear the bit in the ODR
    GPIOA->ODR |= (0x01 << 15);
    GPIOB->ODR |= (0x01 << 12);
    HAL_Delay(1000);

    GPIOA->ODR &= ~(0x01 << 15);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 13);
    GPIOB->ODR |= (0x01 << 12);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 12);   //Clear the bit in the ODR
    GPIOB->ODR |= (0x01 << 13);
    GPIOB->ODR |= (0x01 << 15);
    HAL_Delay(1000);

    GPIOB->ODR &= ~(0x01 << 13);   //Clear the bit in the ODR
    GPIOC->ODR |= (0x01 << 6);
    GPIOB->ODR |= (0x01 << 15);
    HAL_Delay(1000);

    GPIOC->ODR &= ~(0x01 << 6);   //Clear the bit in the ODR
    GPIOB->ODR &= ~(0x01 << 15);   //Clear the bit in the ODR
    HAL_Delay(1000);
}

void s4459843_reg_lta1000g_write3(){
    GPIOC->ODR &= ~(0x01 << 6);
    GPIOB->ODR &= ~(0x01 << 15);
    GPIOB->ODR &= ~(0x01 << 13);
    GPIOB->ODR &= ~(0x01 << 12);
    GPIOA->ODR &= ~(0x01 << 15);
    GPIOC->ODR &= ~(0x01 << 7);
    GPIOB->ODR &= ~(0x01 << 5);
    GPIOB->ODR &= ~(0x01 << 3);
    GPIOA->ODR &= ~(0x01 << 4);
    GPIOB->ODR &= ~(0x01 << 4);
}
*/
