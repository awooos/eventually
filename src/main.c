#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <event.h>

// ASSUMPTION: Maximum E_EVENT_MAX_EVENT_GROUPS event groups.
// ASSUMPTION: Maximum E_EVENT_MAX_HANDLERS_PER_GROUP handlers per event.

// A collection of event groups, initialized to null bytes.
static EEventGroup event_groups[E_EVENT_MAX_EVENT_GROUPS] = {{0,0,{0}}};

static size_t number_of_events = 0;

EEventGroup *_e_event_create_group(const char *event_name)
{
    EEventGroup *group;

    // Too many events. :(
    if (number_of_events > E_EVENT_MAX_EVENT_GROUPS) {
        return NULL;
    }

    group = &(event_groups[number_of_events]);

    group->name = event_name;
    number_of_events++;

    return group;
}

EEventGroup *_e_event_find_or_create_group(const char *event_name)
{
    for (size_t i = 0; i < number_of_events; i++){
        EEventGroup *group = &(event_groups[i]);

        if (strcmp(event_name, group->name) == 0) {
            return group;
        }
    }

    // If we get here, there's no group — so make one!
    return _e_event_create_group(event_name);
}

bool event_watch(const char *event_name, EEventHandler *handler)
{
    EEventGroup *group = _e_event_find_or_create_group(event_name);

    // If we couldn't find or create a group, return false.
    if (group == NULL) {
        return false;
    }

    // If there's too many handlers, return false.
    if (group->number_of_handlers > E_EVENT_MAX_HANDLERS_PER_GROUP) {
        return false;
    }

    group->handlers[group->number_of_handlers] = handler;
    group->number_of_handlers++;

    return true;
}

bool event_trigger(const char *event_name, void *data)
{
    EEventGroup *group = _e_event_find_or_create_group(event_name);

    // If no group is found, return false.
    if (group == NULL) {
        return false;
    }

    for (size_t i = 0; i < group->number_of_handlers; i++) {
        group->handlers[i](data);
    }

    return true;
}
