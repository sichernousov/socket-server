#include "sequence.h"

/* PRIVATE FUNCS */
static void calc_valid (seq_t * ps) {
    ps->valid = (ps->step && ps->base) ? TRUE : FALSE;
}

static void add_seq_elem_to_buf (seq_t * ps, char * pbuf, uint32_t * len, uint32_t maxlen, uint32_t itr)
{
    if ((ps->valid) && (*len < maxlen))
    {
        uint64_t seq_elem = ps->base + (ps->step * itr);
        char tmp_buf[20];
        memset(tmp_buf, '\0', 20);
        sprintf(tmp_buf, "%" PRIu64, seq_elem);
        *len += strlen(tmp_buf);
        if (*len < maxlen)
        {
          pbuf = strcat (pbuf, tmp_buf);
          pbuf = strcat (pbuf, " ");
        }
    }
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


uint8_t generate_seq (char * pbuf, uint32_t maxlen, seq_t * ps1, seq_t * ps2, seq_t * ps3)
{
    if (!(ps1->valid || ps2->valid || ps3->valid))
        return 1; //error

    uint32_t len = 0;
    uint32_t itr = 0;
    while (len < maxlen) {
        add_seq_elem_to_buf(ps1, pbuf, &len, maxlen, itr);
        add_seq_elem_to_buf(ps2, pbuf, &len, maxlen, itr);
        add_seq_elem_to_buf(ps3, pbuf, &len, maxlen, itr);
        itr++;
    }

    return 0;
}
