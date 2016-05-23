#include "IRFrame.h"


map<std::string, const CTemp*> IRFrame::registersInit() {
	map<std::string, const CTemp*> regs;
	regs["eax"] = new CTemp("eax");
	regs["ebx"] = new CTemp("ebx");
	regs["ecx"] = new CTemp("ecx");
	regs["edx"] = new CTemp("edx");
	regs["ebp"] = new CTemp("ebp");
	regs["esp"] = new CTemp("esp");
	return regs;
};

map<std::string, const CTemp*> IRFrame::allRegisters = IRFrame::registersInit();