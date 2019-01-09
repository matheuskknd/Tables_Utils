#ifndef CONVERTER_H_
#define CONVERTER_H_

#include"Package_Table.h"

class Converter final{

private: /* Attributes */

	static constexpr natural TableLineLimit = 1048576;	//Limit line for both
	static natural TableColumnLimit;

public: /* Methods */

	Converter(void) = delete;
	~Converter() = delete;

	inline static void setCompatibilityToExcel(void) noexcept{ if( TableColumnLimit == 0 ) TableColumnLimit = parse_String_Column("XFD");}
	inline static void setCompatilityToCalc(void) noexcept{ if( TableColumnLimit == 0 ) TableColumnLimit = parse_String_Column("AMJ");}

	inline static natural getColumnLimit(void) noexcept{ return TableColumnLimit;}
	inline static natural getLineLimit(void) noexcept{ return TableLineLimit;}

	static void parse_Column_String( const natural Column, AeternalBuffer& bucket) noexcept;
	static natural parse_String_Column( const char * const column) noexcept;

	inline static natural parse_Char_Column( const char column) noexcept{ return column - 'A' + 1;}
};

#endif /* CONVERTER_H_ */
