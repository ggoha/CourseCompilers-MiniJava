#pragma once
#include "IRTemp.h"

class CTempMap {
public:
	virtual const std::string& tempMap(const CTemp* t) = 0;
};



class CCombineMap : public CTempMap {
public:

	CCombineMap(CTempMap* _tmapFirst, CTempMap* _tmapSecond);

	CTempMap* tmapFirst;
	CTempMap* tmapSecond;

	const std::string& tempMap(const CTemp* t);

};

class CDefaultMap : public CTempMap {
public:
	const std::string& tempMap(const CTemp* t);
};

