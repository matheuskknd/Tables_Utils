#ifndef PRE_COMPILING_ACKNOWLEDGEMENTS_H
#define PRE_COMPILING_ACKNOWLEDGEMENTS_H

//Start: Global Main definitions
	#define TESTING_PROGRAM
//End: Global Main definitions

//Start: Global Classes pre-definitions
	template< unsigned int N>
	class CircularBuffer;

	class AeternalBuffer;
	class ConstBufferable;
	class Bufferable;

	class Converter;
	class Table;

	class TableLine;
	class TableCell;
	class CellPart;
	class TextPart;
	class Coordenate;
	class Rule;
//End: Global Classes pre-definitions

//Start: Global Types definitions
	using slimNatural = unsigned char;

	using bigNatural = unsigned long int;
	using ltNatural = unsigned short int;
	using natural = unsigned int;

	using nullptr_t = decltype(nullptr);

	enum apply_on : char{ LINE, COLUMN};
	enum progression_t : char{ AP, GP};
//End: Global Types definitions

//Start: Global debbuging-tools

enum ERROR_CODE{ RUNTIME = -1, _DOMAIN = -2, LOGIC = -4, BAD_ALLOC = -16, UNEXPECTED = -32};

[[noreturn]] void fail_report( const char * const description, const ERROR_CODE) noexcept;	//Defined on main.cpp

#ifdef TESTING_PROGRAM

	#define runtime_assert_nullptr_excpt(prt,where) if( prt == nullptr ) fail_report("Nullptr exception detected in "#where,ERROR_CODE::LOGIC)
	#define runtime_assert(condition,description,error_id) if( !(condition) ) fail_report(description,error_id)

#else

	#define runtime_assert(condition,description,error_id)
	#define runtime_assert_nullptr_excpt(prt,where)

#endif
//End: Global debbuging-tools

#endif /* PRE_COMPILING_ACKNOWLEDGEMENTS_H */
