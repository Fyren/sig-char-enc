#include <stdint.h>
#include <iostream>

class IPluginContext;

template<char...> struct CharPack { static const char c = '?'; typedef CharPack<> next; };
template<typename T> struct val { typedef CharPack<'?'> CP; };

#include "types.i"
DeclVoid();
DeclType(int, 'i');
DeclType(double, 'd');
DeclType(float, 'f');
DeclType(IPluginContext, 'C');
DeclType(char*, 's');
DeclCharPack('c');
DeclTypeAndRef(char, 'c');

template<char... Chars> struct Sig {
	static const char args[sizeof...(Chars)];
	static const size_t n = sizeof...(Chars);
};

template<char... Chars> 
const char Sig<Chars...>::args[sizeof...(Chars)] = { Chars... };

template<typename...> 
struct ArgPack {};

template<typename CP, typename Types, char... Chars>
struct gen2;

template<typename CP, typename Types, char... Chars> 
struct gen2 {
	typedef typename gen2<typename CP::next, Types, Chars..., CP::c>::res res;
};

template<typename First, typename... Rest, char... Chars> 
struct gen2<CharPack<>, ArgPack<First, Rest...>, Chars...> {
	typedef typename gen2<typename val<First>::CP, ArgPack<Rest...>, Chars...>::res res;
};

template<char... Chars> 
struct gen2<CharPack<>, ArgPack<>, Chars...> {
	typedef Sig<Chars...> res;
};

template<typename... Args>
struct gen {
	typedef typename gen2<CharPack<>, ArgPack<Args...>>::res res;
};

template <typename R, typename... Args>
size_t deduce(R (func)(Args...), const char** args) {
	typedef gen<R, Args...> res;
	*args = res::res::args;
	return res::res::n;
}

void printargs(char const* name, size_t n, const char* args); 
#define dump(x) n = deduce(x, &args); printargs(#x, n, args);
