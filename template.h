#include <stdint.h>
#include <iostream>

class IPluginContext;

template<char...> struct CharPack { static const char c = '?'; typedef CharPack<> next; };
template<typename T> struct val { typedef CharPack<'?'> x; };

#include "types.i"
DeclVoid();
DeclType(int, 'i');
DeclType(double, 'd');
DeclType(float, 'f');
DeclType(IPluginContext, 'C');
DeclType(char*, 's');
DeclCharPack('c');
DeclTypeAndRef(char, 'c');

template<char... Args> struct Sig {
	static const char args[sizeof...(Args)];
	static const size_t n = sizeof...(Args);
};

template<char... Args> 
const char Sig<Args...>::args[sizeof...(Args)] = { Args... };

template<typename...> 
struct ArgTypes {};

template<typename CP, typename Types, char... ArgVals>
struct gen2;

template<typename CP, typename Types, char... Vals> 
struct gen2 {
	typedef typename gen2<typename CP::next, Types, Vals..., CP::c>::res res;
};

template<typename First, typename... Rest, char... Vals> 
struct gen2<CharPack<>, ArgTypes<First, Rest...>, Vals...> {
	typedef typename gen2<typename val<First>::x, ArgTypes<Rest...>, Vals...>::res res;
};

template<char... Vals> 
struct gen2<CharPack<>, ArgTypes<>, Vals...> {
	typedef Sig<Vals...> res;
};

template<typename... Args>
struct gen {
	typedef typename gen2<CharPack<>, ArgTypes<Args...>>::res res;
};

template <typename R, typename... Args>
size_t deduce(R (func)(Args...), const char** args) {
	typedef gen<R, Args...> res;
	*args = res::res::args;
	return res::res::n;
}

void printargs(char const* name, size_t n, const char* args); 
#define dump(x) n = deduce(x, &args); printargs(#x, n, args);
