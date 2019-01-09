#ifndef TEXT_PART_H_
#define TEXT_PART_H_

#include"Package_Table.h"

class TextPart : public CellPart{

/*
*	24 bytes text part.
*/

private: /* Attributes */

	struct SharedString final{

		const char* const str;
		bigNatural NbPtrs;

		inline constexpr SharedString( const char* const s) noexcept : str{s}, NbPtrs{1} {}
		inline ~SharedString() noexcept{ delete str;}

		inline bool canBeDeleted(void) const noexcept{ return NbPtrs == 0;}
	};

	SharedString* string;

	inline TextPart( SharedString* const s) noexcept : string{s} { ++(s->NbPtrs);}

public: /* Methods */

	inline TextPart( const char* const s) noexcept try{ string = new SharedString(s); }catch(...){ fail_report("TextPart::TextPart(const char*)",ERROR_CODE::BAD_ALLOC);}
	virtual ~TextPart() noexcept override;

	virtual inline CellPart* applyInColumns( natural, int, operation) const noexcept override try{ return new TextPart(string); }catch(...){ fail_report("TextPart::applyInColumns(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);}
	virtual inline CellPart* applyInLines( natural, int, operation) const noexcept override try{ return new TextPart(string); }catch(...){ fail_report("TextPart::applyInLines(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);}

	virtual void print( const bool keepMarkUp = false) const noexcept override;
};

#endif /* TEXT_PART_H_ */
