#ifndef EVENTUALLY_EVENT_H
#define EVENTUALLY_EVENT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void EEventHandler(void *data);

#define E_EVENT_MAX_EVENT_GROUPS 50
#define E_EVENT_MAX_HANDLERS_PER_GROUP 50

typedef struct eventually_event_group {
    const char *name;
    size_t number_of_handlers;
    EEventHandler *handlers[E_EVENT_MAX_HANDLERS_PER_GROUP];
} EEventGroup;

bool event_watch(const char *event_name, EEventHandler *handler);
bool event_trigger(const char *event_name, void *data);

#endif
