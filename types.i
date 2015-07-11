#define DeclTypeAndRef(type, char)\
template<> struct val<type> { typedef CharPack<char> x; };\
template<> struct val<type&> { typedef CharPack<'&', char> x; };

#define DeclPtrs(type, char)\
template<> struct val<type*> { typedef CharPack<'[', char> x; };\
template<> struct val<type**> { typedef CharPack<'[', '[', char> x; };\
template<> struct val<type***> { typedef CharPack<'[', '[', '[', char> x; };\
template<> struct val<type****> { typedef CharPack<'[', '[', '[', '[', char> x; };\

#define DeclPtrRefs(type, char)\
template<> struct val<type*&> { typedef CharPack<'[', '&', char> x; };\
template<> struct val<type**&> { typedef CharPack<'[', '[', '&', char> x; };\
template<> struct val<type***&> { typedef CharPack<'[', '[', '[', '&', char> x; };\
template<> struct val<type****&> { typedef CharPack<'[', '[', '[', '[', '&', char> x; };\

#define DeclCharPack(x) template<char... Rest>\
struct CharPack<x, Rest...> { static const char c = x; typedef CharPack<Rest...> next; };\
template<>\
struct CharPack<x> { static const char c = x; typedef CharPack<> next; };

#define DeclType(type, char)\
DeclCharPack(char);\
DeclTypeAndRef(type, char);\
DeclPtrs(type, char);\
DeclPtrRefs(type, char);

#define DeclVoid()\
DeclCharPack('v');\
template<> struct val<void> { typedef CharPack<'v'> x; };\
DeclPtrs(void, 'v');\
DeclPtrRefs(void, 'v');

DeclCharPack('[');
DeclCharPack('&');
