#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct {
   bool valid;      //флаг валидности последовательности
   uint64_t base;   //базовое значение последовательности
   uint64_t step;   //шаг инкремента
}seq_t;

seq_t * create_seq (void);
void delete_seq (seq_t * ps);
void set_param_seq (seq_t * ps, uint64_t base, uint64_t step);
uint8_t generate_seq (char * pbuf, uint32_t maxlen, seq_t * ps1, seq_t * ps2, seq_t * ps3);

#endif
