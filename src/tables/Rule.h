#ifndef RULE_H
#define RULE_H

#include"Package_Table.h"

class Rule : public CellPart{

/*
*	48 bytes rule part.
*/

private: /* Attributes */

	const CellPart* ruled;

	const natural frequency;
	const natural step;

	const natural since;
	const natural until;

	const natural vigor;

	const progression_t pgt;
	const apply_on aplo;

private: /* Methods */

	inline static constexpr natural times( const natural x, const int y) noexcept{ return y < 0 ? x/-y : x*y;}
	inline static constexpr natural plus( const natural x, const int y) noexcept{ return x + y;}
	inline static constexpr natural none( const natural x, const int) noexcept{ return x;}
	inline static natural pow( const natural base, const natural exp) noexcept;

public: /* Methods */

	inline constexpr Rule( const natural stp, const natural frec, const natural snc, const natural utl, const natural vgr, const progression_t pgrt, const apply_on apl) noexcept : ruled{nullptr}, frequency{frec}, step{stp}, since{snc}, until{utl}, vigor{vgr}, pgt{pgrt}, aplo{apl} {}
	virtual ~Rule() noexcept override;

	virtual CellPart* applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept override;
	virtual CellPart* applyInLines( const natural iter, const int step, const operation oprtn) const noexcept override;

	virtual void print( const bool keepMarkUp) const noexcept override;

	inline const CellPart*& getRuling(void) noexcept{ return ruled;}
};

#endif /* RULE_H */
