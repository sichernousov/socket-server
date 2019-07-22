#include "sequence.h"

static void calc_valid (seq_t * ps) {
    ps->valid = (ps->step && ps->base) ? TRUE : FALSE;
}

/* PUBLIC FUNCS */
seq_t * create_seq (void)
{
    seq_t * ps = NULL;
    ps = (seq_t *) malloc(sizeof(seq_t));
    if (ps != NULL) {
        ps->valid = FALSE;
        ps->base = 0;
        ps->step = 0;
    }
    return ps;
}

void delete_seq (seq_t * ps)
{
    ps->valid = FALSE;
    ps->base = 0;
    ps->step = 0;
    free(ps);
}

void set_param_seq (seq_t * ps, uint64_t base, uint64_t step)
{
    ps->base = base;
    ps->step = step;
    calc_valid(ps);
}

uint8_t generate_one (char * pbuf, seq_t * ps1, seq_t * ps2, seq_t * ps3, uint32_t itr)
{
    if (!(ps1->valid || ps2->valid || ps3->valid))
        return 1; //error

    if (ps1->valid)
    {
      uint64_t seq_elem = ps1->base + (ps1->step * itr);
      char tmp_buf[20];
      memset(tmp_buf, '\0', 20);
      sprintf(tmp_buf, "%" PRIu64, seq_elem);
      pbuf = strcat (pbuf, tmp_buf);
      pbuf = strcat (pbuf, " ");
    }

    if (ps2->valid)
    {
      uint64_t seq_elem = ps2->base + (ps2->step * itr);
      char tmp_buf[20];
      memset(tmp_buf, '\0', 20);
      sprintf(tmp_buf, "%" PRIu64, seq_elem);
      pbuf = strcat (pbuf, tmp_buf);
      pbuf = strcat (pbuf, " ");
    }

    if (ps3->valid)
    {
      uint64_t seq_elem = ps3->base + (ps3->step * itr);
      char tmp_buf[20];
      memset(tmp_buf, '\0', 20);
      sprintf(tmp_buf, "%" PRIu64, seq_elem);
      pbuf = strcat (pbuf, tmp_buf);
      pbuf = strcat (pbuf, " ");
    }

    return 0;
}
