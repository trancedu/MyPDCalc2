#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <memory>
#include "observer.h"
using std::string;
using std::unique_ptr, std::shared_ptr;
using std::unordered_map;

class Publisher
{
	using ObserverUPtr = unique_ptr<Observer>;
private:
	unordered_map<string, unordered_map<string, ObserverUPtr>> events_;
public:
	void raise(const string& eventName, const std::any& message);
	void attach(const string& eventName, ObserverUPtr observer);
	void detach(const string& eventName, const string& observerName);
	virtual ~Publisher();
private:
	void checkEventNameInEvents(const string& eventName) const;
};