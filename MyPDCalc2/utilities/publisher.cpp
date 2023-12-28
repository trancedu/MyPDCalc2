#include "publisher.h"
#include "exception.h"
#include <format>

Publisher::~Publisher() = default;

void Publisher::raise(const string& eventName, const std::any& message)
{
	checkEventNameInEvents(eventName);

	for (const auto& [observerName, observer] : events_.at(eventName)) {
		observer->notify(message);
	}
}

void Publisher::attach(const string& eventName, ObserverUPtr observer)
{
	checkEventNameInEvents(eventName);
	if (!events_.at(eventName).contains(observer->name())) {
		events_.at(eventName)[observer->name()] = std::move(observer);
	}
}

void Publisher::detach(const string& eventName, const string& observerName)
{
	checkEventNameInEvents(eventName);
	if (events_.at(eventName).contains(observerName)) {
		events_.at(eventName).erase(observerName);
	}
}


void Publisher::checkEventNameInEvents(const string& eventName) const
{
	if (!events_.contains(eventName)) {
		throw Exception{ std::format("No eventName {} in events_", eventName) };
	}
}
