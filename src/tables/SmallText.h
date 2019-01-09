#ifndef SMALL_TEXT_H_
#define SMALL_TEXT_H_

#include"Package_Table.h"

struct char8 final{

	const char value[8];

	inline constexpr char8( const char c1, const char c2, const char c3, const char c4, const char c5, const char c6, const char c7, const char c8) noexcept : value{c1,c2,c3,c4,c5,c6,c7,c8} {}
	inline ~char8() = default;

	inline constexpr char operator[]( const natural i) const noexcept{ return i == 8 ? '\0' : value[i];}
};

class SmallText : public CellPart{

/*
*	24 bytes text part.
*/

private: /* Attributes */

	const char8 text;

	inline SmallText( const char8 str) noexcept : text{str} {}

public: /* Methods */

	inline SmallText( const char c1, const char c2, const char c3, const char c4, const char c5, const char c6, const char c7, const char c8) noexcept : text(c1,c2,c3,c4,c5,c6,c7,c8) {}
	virtual inline ~SmallText() = default;

	virtual inline CellPart* applyInColumns( natural, int, operation) const noexcept override try{ return new SmallText(text); }catch(...){ fail_report("SmallText::applyInColumns(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);}
	virtual inline CellPart* applyInLines( natural, int, operation) const noexcept override try{ return new SmallText(text); }catch(...){ fail_report("SmallText::applyInLines(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);}

	virtual void print( const bool keepMarkUp = false) const noexcept override;
};

#endif /* SMALL_TEXT_H_ */
