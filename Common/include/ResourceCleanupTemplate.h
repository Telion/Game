#pragma once

#include "pch.h"

#define MAKE_RESOURCE_CLASS(ClassType, ResourceType, defaultResourceValue, deleterFunc) \
class ClassType \
{ \
	ResourceType resource; \
	ClassType(const ClassType& rhs); \
	ClassType& operator =(const ClassType& rhs); \
public: \
	ClassType() : \
		resource(defaultResourceValue) \
	{} \
	ClassType(ResourceType t) : \
		resource(t) \
	{} \
	ResourceType const & get() const \
	{ \
		return resource; \
	} \
	ClassType(ClassType&& rhs) : \
		resource(std::move(rhs.resource)) \
	{ \
		rhs.resource = defaultResourceValue; \
	} \
	ClassType& operator =(ClassType&& rhs) \
	{ \
		resource = std::move(rhs.resource); \
		rhs.resource = defaultResourceValue; \
	} \
	~ClassType() \
	{ \
		if(resource != defaultResourceValue) \
		{ \
			deleterFunc; \
		} \
	} \
};

#define MAKE_CLEANUP_CLASS(ClassType, deleterFunc) \
class ClassType \
{ \
	bool enabled; \
	ClassType(const ClassType& rhs); \
	ClassType& operator =(const ClassType& rhs); \
public: \
	ClassType() : \
		enabled(true) \
	{} \
	ClassType(ClassType&& rhs) : \
		enabled(rhs.enabled) \
	{ \
		rhs.enabled = false; \
	} \
	ClassType& operator =(ClassType&& rhs) \
	{ \
		enabled = rhs.enabled; \
		rhs.enabled = false; \
	} \
	void cleanup() \
	{ \
		if(enabled) \
		{ \
			enabled = false; \
			deleterFunc; \
		} \
	} \
	~ClassType() \
	{ \
		cleanup(); \
	} \
};