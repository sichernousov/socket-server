#ifndef PARSE_H
#define PARSE_H

#include <inttypes.h>
#include "general_types.h"

#define CMD_SET1 "seq1"
#define CMD_SET2 "seq2"
#define CMD_SET3 "seq3"
#define CMD_EXP  "export seq"

typedef enum cmd_t{
  CMD_Err         = 0,
  CMD_SetSeq1     = 1,
  CMD_SetSeq2     = 2,
  CMD_SetSeq3     = 3,
  CMD_ExportSeq   = 9
} cmd_t;

typedef struct {
   cmd_t cmd;
   uint64_t param1;
   uint64_t param2;
}parse_t;

bool parse_buf(char *pbuf, parse_t *p);

#endif
