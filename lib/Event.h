#ifndef EVENT_230958
#define EVENT_230958

#include <functional>
#include "Collision.h"

class Event {
public:
	std::function<void(Collision collision)> callback;
	Event() {
		
	}
	Event(std::function<void(Collision collision)> fn) : callback(fn) {
	}
	void operator()(Collision collision) {
		return this->callback(collision);
	}
};

#endif