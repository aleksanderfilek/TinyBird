#ifndef TB_FFDATA_H_
#define TB_FFDATA_H_

typedef struct FFData
{
    void* ptr;
    void (*destroy)(void* ptr);
} FFData;

#endif