#include "sequence.h"

/* PRIVATE FUNCS */
static void calc_valid (seq_t * ps) {
    ps->valid = (ps->step && ps->base) ? TRUE : FALSE;
}

//вычисляет следующий элемент в последовательности ps, преобразовывает его в строку и добавляет в конец буфера pbuf
static void add_seq_elem_to_buf (seq_t * ps, char * pbuf, uint32_t * len, uint32_t maxlen)
{
    if ((ps->valid) && (*len < maxlen))
    {
        uint64_t seq_elem = ps->base + (ps->step * ps->itr);
        char tmp_buf[20];
        memset(tmp_buf, '\0', 20);
        sprintf(tmp_buf, "%" PRIu64, seq_elem);
        *len += strlen(tmp_buf);
        if (*len < maxlen)
        {
          pbuf = strcat (pbuf, tmp_buf);
          *len += 1;
          if (*len < maxlen)
            pbuf = strcat (pbuf, " ");
        }

        //случай если переполнение
        if ((0xFFFFFFFFFFFFFFFF - seq_elem) < ps->step)
            ps->itr = 0;
        else
            ps->itr += 1;
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
        ps->itr  = 0;
    }
    return ps;
}

void delete_seq (seq_t * ps)
{
    ps->valid = FALSE;
    ps->base = 0;
    ps->step = 0;
    ps->itr  = 0;
    free(ps);
}

void set_param_seq (seq_t * ps, uint64_t base, uint64_t step)
{
    ps->base = base;
    ps->step = step;
    calc_valid(ps);
}

//генерирует последовательность из 3х подпоследовательностей. См. README
bool generate_seq (char *pbuf, uint32_t maxlen, seq_t *ps1, seq_t *ps2, seq_t *ps3)
{
    if (!(ps1->valid || ps2->valid || ps3->valid))
        return FALSE;

    uint32_t len = 0; 
    while (len < maxlen) {
        add_seq_elem_to_buf(ps1, pbuf, &len, maxlen);
        add_seq_elem_to_buf(ps2, pbuf, &len, maxlen);
        add_seq_elem_to_buf(ps3, pbuf, &len, maxlen);
    }
    ps1->itr = 0;
    ps2->itr = 0;
    ps3->itr = 0;

    return TRUE;
}
