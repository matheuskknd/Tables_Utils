#ifndef RULE_H
#define RULE_H

#include"Package_Table.h"

class Rule : public CellPart{

/*
*	56 bytes rule part.
*/

private: /* Attributes */

	const CellPart* F_ruled;
	CellPart* L_ruled;

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

	inline constexpr Rule( const natural stp, const natural frec, const natural snc, const natural utl, const natural vgr, const progression_t pgrt, const apply_on apl) noexcept : F_ruled{nullptr}, L_ruled{nullptr}, frequency{frec}, step{stp}, since{snc}, until{utl}, vigor{vgr}, pgt{pgrt}, aplo{apl} {}
	virtual ~Rule() noexcept override;

	virtual inline void setNext( CellPart* const cp) noexcept override{ runtime_assert_nullptr_excpt(L_ruled,"virtual void Rule::setNext(CellPart*)"); this->CellPart::setNext(cp); L_ruled->setNext(cp);}
	inline void setLast( CellPart* const cp) noexcept{ L_ruled = cp;}

	virtual CellPart* applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept override;
	virtual CellPart* applyInLines( const natural iter, const int step, const operation oprtn) const noexcept override;

	virtual void print( const bool keepMarkUp) const noexcept override;

	inline void setRuling( const CellPart* const cp) noexcept{ F_ruled = cp;}
	inline const CellPart* getRuling(void) noexcept{ return F_ruled;}
};

#endif /* RULE_H */
