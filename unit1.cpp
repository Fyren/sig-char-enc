#include "template.h"

void unit2();

static int GetNumPlayers(IPluginContext* cx, double d, int& r) { return 0; }
static double GetDouble(IPluginContext *cx) { return 0.0; }
static void NoRet(IPluginContext *cx) { }
static void CharPtr(IPluginContext *cx, char* s) { }
static void CharArr(IPluginContext *cx, char s[]) { }
static double BadNative(int i) { return 0.0; }
static void CharStringTest(char c, char& c2, char* s, char** s2, char**& s3) { }

void printargs(char const* name, size_t n, const char* args) {
	std::cout << name << " (" << (void*) args << "): ";
	for (size_t i = 0; i < n; i++) 
		std::cout << args[i];
	std::cout << std::endl;
}

int main() {
	const char* args;
	size_t n;

	dump(GetNumPlayers);
	dump(GetDouble);
	dump(NoRet);
	dump(CharPtr);
	dump(CharArr);
	dump(CharStringTest);	

	unit2();
	return 0;
}
