#ifndef CONVERTER_H_
#define CONVERTER_H_

#include"Package_Table.h"

class Converter final{

private: /* Attributes */

	enum GREATER{ NATURAL = static_cast<natural>(-1) };

	static constexpr natural TableLineLimit = 1048576;	//Limit line for both
	static natural TableColumnLimit;

public: /* Methods */

	Converter(void) = delete;
	~Converter() = delete;

	inline static void setCompatibilityToExcel(void) noexcept{ if( TableColumnLimit == GREATER::NATURAL ) TableColumnLimit = parse_String_Column(3,"XFD");}
	inline static void setCompatilityToCalc(void) noexcept{ if( TableColumnLimit == GREATER::NATURAL ) TableColumnLimit = parse_String_Column(3,"AMJ");}

	inline static natural getColumnLimit(void) noexcept{ return TableColumnLimit;}
	inline static natural getLineLimit(void) noexcept{ return TableLineLimit;}

	static natural parse_String_Column( natural legth, const char * const column) noexcept;
	static void parse_Column_String( natural Column, AeternalBuffer& bucket) noexcept;

	inline static constexpr natural parse_Char_Column( const char column) noexcept{ return column - 'A' + 1;}
};

#endif /* CONVERTER_H_ */
