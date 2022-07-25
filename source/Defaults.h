#ifndef TB_DEFAULT_H_
#define TB_DEFAULT_H_

#include<stdlib.h>

#define STRUCT(name) typedef struct name name

#define MALLOC(Type) (Type*)malloc(sizeof(Type))
#define MALLOCEX(Type, Number) (Type*)malloc(Number * sizeof(Type))

#endif