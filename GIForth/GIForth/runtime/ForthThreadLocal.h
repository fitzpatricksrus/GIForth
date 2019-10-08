//
// Created by stuff on 10/8/2019.
//

#ifndef GIFORTH_FORTHTHREADLOCAL_H
#define GIFORTH_FORTHTHREADLOCAL_H


#include <map>
#include "ForthThread.h"

template <class T>
class ForthThreadLocal {
public:
	ForthThreadLocal(T initialValue);
	const T& operator*() const;
	T& operator*();

private:
	static std::map<std::pair<ForthThreadLocal<T>*, const ForthThread*>, T> locals;
};

template <class T>
std::map<std::pair<ForthThreadLocal<T>*, const ForthThread*>, T> ForthThreadLocal<T>::locals;

template <class T>
ForthThreadLocal<T>::ForthThreadLocal(T initialValue) {
	std::pair<ForthThreadLocal<T>*, const ForthThread*> pair = std::make_pair(this, ForthThread::getCurrentThread());
	locals[pair] = initialValue;
}

template <class T>
const T& ForthThreadLocal<T>::operator*() const {
	std::pair<ForthThreadLocal<T>*, const ForthThread*> pair = std::make_pair(this, ForthThread::getCurrentThread());
	return locals[pair];
}

template <class T>
T& ForthThreadLocal<T>::operator*() {
	std::pair<ForthThreadLocal<T>*, const ForthThread*> pair = std::make_pair(this, ForthThread::getCurrentThread());
	return locals[pair];
}

#endif //GIFORTH_FORTHTHREADLOCAL_H
