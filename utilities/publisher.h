#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <memory>
#include "observer.h"
#include "export.h"

using std::string;
using std::unique_ptr, std::shared_ptr;
using std::unordered_map;

class UTILITIES_API Publisher
{
	using ObserverSPtr = shared_ptr<Observer>;
private:
	unordered_map<string, unordered_map<string, ObserverSPtr>> events_;
public:
	void attach(const string& eventName, ObserverSPtr observer);
	void detach(const string& eventName, const string& observerName);
	virtual ~Publisher() = default;
protected:
	void raise(const string& eventName, const std::any& message);
private:
	void checkEventNameInEvents(const string& eventName) const;
};