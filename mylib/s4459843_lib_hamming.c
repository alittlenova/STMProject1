#include "s4459843_lib_hamming.h"
void s4459843_lib_hamming_init(void) 
{
	HammingFsmCurrentstate=IDLE_STATE;
	BRD_LEDGreenOn();
}
void s4459843_lib_hamming_fsmprocessing(unsigned char State)
{
	HammingFsmCurrentstate=State;
}
unsigned char s4459843_lib_hammingFsm_read_status(void)
{
	 return HammingFsmCurrentstate;
}
uint16_t s4459843_lib_hamming_byte_encode(uint8_t input)
{
	uint16_t out;

	/* first encode D0..D3 (first 4 bits),
	 * then D4..D7 (second 4 bits).
	 */
	out = hamming_hbyte_encode(input & 0xF) |
		(hamming_hbyte_encode(input >> 4) << 8);
 
	return(out);
}
uint8_t s4459843_lib_hamming_byte_decode(uint8_t input)
{
	uint8_t error = 0;
    uint8_t corrected = 0;
    uint8_t s0,s1,s2;
    uint8_t syndrome;
    uint8_t newbyte;
    s0 = (!!(input & 0x02)) ^ (!!(input & 0x04)) ^ (!!(input & 0x08)) ^ (!!(input & 0x10));
    s1 = (!!(input & 0x01)) ^ (!!(input & 0x04)) ^ (!!(input & 0x08)) ^ (!!(input & 0x20));
    s2 = (!!(input & 0x01)) ^ (!!(input & 0x02)) ^ (!!(input & 0x08)) ^ (!!(input & 0x40));
    syndrome = (s0 << 2) | (s1 << 1) | s2;
    if((syndrome|0x00)==0x00)
    {
        newbyte = input;
	}
	else if((syndrome|0x00)==0x01)
	{
		error++;
        newbyte = input ^ (1 << 6);
        corrected++;
	}
	else if((syndrome|0x00)==0x02)
	{
		error++;
        newbyte = input ^ (1 << 5);
        corrected++;
	}
	else if((syndrome|0x00)==0x03)
	{
		error++;
        newbyte = input;
        corrected++;
	}
	else if((syndrome|0x00)==0x04)
	{
		error++;
        newbyte = input ^ (1 << 4);
        corrected++;
	}
	else if((syndrome|0x00)==0x05)
	{
		error++;
        newbyte = input ^ (1 << 1);
        corrected++;
	}
	else if((syndrome|0x00)==0x06)
	{
		error++;
        newbyte = input ^ (1 << 2);
        corrected++;
	}
	else if((syndrome|0x00)==0x07)
	{
		error++;
        newbyte = input ^ (1 << 2);
        corrected++;
	}
	
	if(s4459843_lib_hamming_parity_error(newbyte) != ( (newbyte >>7) & 0x01))
	{
        if((syndrome|0x00)==0x00)
        {
            corrected--;
		}
        else
        {
            error++;
            corrected++;
		}
	}
	return (((!!s4459843_lib_hamming_parity_error(newbyte) )<<1)&0x03)|((!!corrected)&0x01);
}
uint8_t hamming_hbyte_encode(uint8_t in)
{
	
	uint8_t d0, d1, d2, d3;
	uint8_t p0 = 0, h0, h1, h2;
	uint8_t z;
	uint8_t out;

	/* extract bits */
	d0 = !!(in & 0x1);
	d1 = !!(in & 0x2);
	d2 = !!(in & 0x4);
	d3 = !!(in & 0x8);

	/* calculate hamming parity bits */
	h0 = d1 ^ d2 ^ d3;
	h1 = d0 ^ d2 ^ d3;
	h2 = d0 ^ d1 ^ d3;

	/* generate out byte without parity bit P0 */
	out = (h0 << 1) | (h1 << 2) | (h2 << 3) |
		(d0 << 4) | (d1 << 5) | (d2 << 6) | (d3 << 7);

	/* calculate even parity bit */
	for (z = 1; z<8; z++)
		p0 = p0 ^ !!(out & (1 << z));

	out |= p0;

	return(out);

}
uint8_t s4459843_lib_hamming_parity_error(uint8_t newbyte)
{
	uint8_t p=0x00;
	for(int i=0;i<7;i++)
	{
        p ^= (newbyte >> i) & 0x01;
	}
	return p;
}
