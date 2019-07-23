#include "parse.h"

/* PRIVATE FUNCS */
static bool get_cmd(char *pbuf, parse_t *p)
{
    if (strncmp(pbuf, CMD_EXP, strlen(CMD_EXP)) == 0)
    {
        p->cmd = CMD_ExportSeq;
        return TRUE;
    }

    if (strncmp(pbuf, CMD_SET1, strlen(CMD_SET1)) == 0)
    {
        p->cmd = CMD_SetSeq1;
        return TRUE;
    }

    if (strncmp(pbuf, CMD_SET2, strlen(CMD_SET2)) == 0)
    {
        p->cmd = CMD_SetSeq2;
        return TRUE;
    }

    if (strncmp(pbuf, CMD_SET3, strlen(CMD_SET3)) == 0)
    {
        p->cmd = CMD_SetSeq3;
        return TRUE;
    }

    p->cmd = CMD_Err;
    return FALSE;
}

static bool get_params(char *pbuf, parse_t *p)
{
    char tmp_buf[BUF_LEN];
    uint32_t i = 5,
             j = 0;
    uint8_t num = 0;

    //get param1
    memset(tmp_buf, '\0', BUF_LEN);
    while ((i <= BUF_LEN) && (*(pbuf + i) >= '0') && (*(pbuf + i) <= '9'))
    {
        tmp_buf[j] = *(pbuf + i);
        i++;
        j++;
    }
    if (tmp_buf[0] == '\0') return FALSE;

    num = sscanf(tmp_buf, "%" SCNu64, &(p->param1));
    if (num == 0) return FALSE;

    //get param2
    memset(tmp_buf, '\0', BUF_LEN);
    j = 0; i++;
    while ((i <= BUF_LEN) && (*(pbuf + i) >= '0') && (*(pbuf + i) <= '9'))
    {
        tmp_buf[j] = *(pbuf + i);
        i++;
        j++;
    }
    if (tmp_buf[0] == '\0') return FALSE;

    num = sscanf(tmp_buf, "%" SCNu64, &(p->param2));
    if (num == 0) return FALSE;

    return TRUE;
}

/* PUBLIC FUNCS */
bool parse_buf(char *pbuf, parse_t *p)
{
    if (!get_cmd(pbuf, p))
        return FALSE;

    if (p->cmd == CMD_ExportSeq)
        return TRUE;

    if ((p->cmd >= CMD_SetSeq1) && (p->cmd <= CMD_SetSeq3))
        return get_params(pbuf, p);

    return FALSE;
}
