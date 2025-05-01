#pragma once
#include "Time_trigger.h"

trigger set_trigger(int time) {
	trigger t = { time };
	return t;

};
trigger set_trigger_after(trigger t, int time) {
	if (t.trigger != DISABLED_TRIGGER) {
		t.trigger += time;

	}
	else {
		t.trigger = DISABLED_TRIGGER;
	}
	return t;


};

bool now(trigger t, int time) {
	if (t.trigger != DISABLED_TRIGGER) {
		return (t.trigger == time);
	}
	else {
		return false;
	}
};
int since(trigger t, int time) {
	int since;
	if (t.trigger != DISABLED_TRIGGER) {
		since = time - t.trigger;
	}
	else {
		since = DISABLED_TRIGGER;
	}
	return abs(since);
};
trigger disable_trigger() {
	trigger t = { DISABLED_TRIGGER };
	return t;
}