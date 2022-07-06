#ifndef TB_EVENT_H_
#define TB_EVENT_H_

typedef void (*EventFunction)(void* object, void *args, int argc);

#define EventFunction(name) void name(void* object, void *args, int argc)

typedef struct 
{
  EventFunction* functions;
  int count;
}Event;

Event* EventCreate();
void EventDestroy(Event* event);
void EventAdd(Event* event, EventFunction function);
void EventInvoke(Event* event, void* object, void *args, int argc);
void EventClear(Event* event);

#endif