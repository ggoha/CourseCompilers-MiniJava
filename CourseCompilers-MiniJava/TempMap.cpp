#include "IRTemp.h"
#include "TempMap.h"

//--------------------------------------------------------------------------------------------------------------
// CCombineMap
//--------------------------------------------------------------------------------------------------------------

CCombineMap::CCombineMap(CTempMap* _tmapFirst, CTempMap* _tmapSecond) : tmapFirst(_tmapFirst), tmapSecond(_tmapSecond) {}


const std::string& CCombineMap::tempMap(const CTemp* t) {
	const std::string& s = tmapFirst->tempMap(t);
	if (!s.empty()) {
		return s;
	}
	else {
		return tmapSecond->tempMap(t);
	}
}

//--------------------------------------------------------------------------------------------------------------
// CDefaultMap
//--------------------------------------------------------------------------------------------------------------

const std::string& CDefaultMap::tempMap(const CTemp* t) {
	return t->Name();
}