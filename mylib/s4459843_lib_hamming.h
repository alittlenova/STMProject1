#ifndef HAMMING_H
#define HAMMING_H
#include "board.h"
#include "processor_hal.h"
extern void s4459843_lib_hamming_init(void);
extern void s4459843_lib_hamming_fsmprocessing(unsigned char State);
extern unsigned char s4459843_lib_hammingFsm_read_status(void);
uint16_t s4459843_lib_hamming_byte_encode(uint8_t input);
uint8_t s4459843_lib_hamming_byte_decode(uint8_t input);
uint8_t hamming_hbyte_encode(uint8_t in);
uint8_t s4459843_lib_hamming_parity_error(uint8_t in);
unsigned char HammingFsmCurrentstate;
#define IDLE_STATE 0x00
#define ENCODE_STATE 0x01
#define DECODE_STATE 0x02
#endif
