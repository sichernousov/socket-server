#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <inttypes.h>
#include "general_types.h"

typedef struct {
   bool valid;      //флаг валидности последовательности
   uint64_t base;   //базовое значение последовательности
   uint64_t step;   //шаг инкремента
   uint32_t itr;    //итерация для генерирования следующего элемента
}seq_t;

seq_t * create_seq (void);
void delete_seq (seq_t * ps);
void set_param_seq (seq_t * ps, uint64_t base, uint64_t step);
bool generate_seq(char *pbuf, uint32_t maxlen, seq_t *ps1, seq_t *ps2, seq_t *ps3);

#endif
