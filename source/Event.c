#include"Event.h"

#include<stdlib.h>

Event* EventCreate()
{
  Event* event = (Event*)malloc(sizeof(Event));
  event->functions = NULL;
  event->count = 0;
  return event;
}

void EventDestroy(Event* event)
{
  EventClear(event);
  free(event);
}

void EventAdd(Event* event, EventFunction function)
{
  event->count++;
  event->functions = (EventFunction*)realloc(event->functions, event->count * sizeof(EventFunction));
  event->functions[event->count-1] = function;
}

void EventInvoke(Event* event, void* object, void *args, int argc)
{
  for(int i = 0; i < event->count; i++)
  {
    event->functions[i](object, args, argc);
  }
}

void EventClear(Event* event)
{
  free(event->functions);
  event->functions = NULL;
  event->count = 0;
}