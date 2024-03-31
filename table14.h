#ifndef __TABLE14_H__
#define __TABLE14_H__

#include <stdint.h>
#include <stdlib.h>

struct table14_t
{
    uint32_t meta[14];
    void *data;
};

#define TABLE14_CACHE_LINE 64

#define TABLE14(_table, ...)                                              \
    struct table14_t _table __attribute__((aligned(TABLE14_CACHE_LINE))); \
    enum _table##_cols                                                    \
    {                                                                     \
        __VA_ARGS__                                                       \
    }

#define TABLE14_ALIGNED_CAPACITY(_capacity) TABLE14_CACHE_LINE *((_capacity) / TABLE14_CACHE_LINE) + ((_capacity) % TABLE14_CACHE_LINE)

#define TABLE14_INIT_START(_table, _capacity)                                                                                  \
    {                                                                                                                          \
        struct table14_t *const table = &_table;                                                                               \
        uint32_t const capacity = (_capacity < TABLE14_CACHE_LINE) ? TABLE14_CACHE_LINE : TABLE14_ALIGNED_CAPACITY(_capacity); \
        uint32_t col = 0

#define TABLE14_INIT_COL(_col, _type)             \
    table->meta[_col] = sizeof(_type) * capacity; \
    col++

#define TABLE14_INIT_END                                      \
    for (int i = 1; i < col; ++i)                             \
        table->meta[i] += table->meta[i - 1];                 \
    uint32_t end_idx = table->meta[col - 1];                  \
    for (int i = col - 1; i > 0; --i)                         \
        table->meta[i] = table->meta[i - 1];                  \
    table->meta[0] = 0;                                       \
    table->data = aligned_alloc(TABLE14_CACHE_LINE, end_idx); \
    }

#define TABLE14_SIZE(_table) (_table.meta[0])

#define TABLE14_GET(_table, _col, _type) ((_type *)(&(((uint8_t *)(_table.data))[_table.meta[_col] * (_col > 0)])))

#define TABLE14_NEW(_table, _col, _type) TABLE14_GET(_table, _col, _type)[TABLE14_SIZE(_table)]

#define TABLE14_PUSH(_table) TABLE14_SIZE(_table)++

#endif /* __TABLE14_H__ */