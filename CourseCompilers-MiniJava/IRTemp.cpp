#include "IRTemp.h" 

int CTemp::nextUniqueId = 0;
int CLabel::nextUniqueId = 0;

CTempList::CTempList(const CTemp* _head, CTempList* _tail) : head(_head), tail(_tail) {}


CLabelList::CLabelList(const CLabel* _head, CLabelList* _tail) : head(_head), tail(_tail) {}