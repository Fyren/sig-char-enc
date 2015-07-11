#include "template.h"

static int GetNumPlayers2(IPluginContext* cx, double d, int& r) { return 0; }

void unit2() {
	const char* args;
	size_t n;

	dump(GetNumPlayers2);
}
