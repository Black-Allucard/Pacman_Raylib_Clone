#pragma once
#define DISABLED_TRIGGER (-1)
#include "raylib.h"

typedef struct time_trigger {
	int trigger;
}trigger;

trigger set_trigger(int time);
trigger set_trigger_after(trigger t, int time);
bool now(trigger t, int time);
int since(trigger t, int time);
trigger disable_trigger();