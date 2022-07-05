#ifndef TB_MODULE_H_
#define TB_MODULE_H_

typedef struct Module
{
    void* data;
    void (*update)(void* ptr, double elapsed);
    void (*destroy)(void* ptr);
} Module;

#endif