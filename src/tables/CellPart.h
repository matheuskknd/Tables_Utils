#ifndef CELL_PART_H_
#define CELL_PART_H_

#include"Package_Table.h"

class CellPart{

protected:

	using operation = natural (*)(natural,int) noexcept;

	CellPart* next;

	inline constexpr CellPart(void) noexcept : next{nullptr} {}

public:

	virtual inline ~CellPart() = default;

	virtual CellPart* applyInColumns( const natural iter, const int step, const operation oprtn) const = 0;	//The natural "iter" is the current iteration number
	virtual CellPart* applyInLines( const natural iter, const int step, const operation oprtn) const = 0;	//The natural "iter" is the current iteration number

	virtual inline void setNext( CellPart* const cp) noexcept final{ runtime_assert(!next,"memory leak detected on virtual void CellPart::attach(CellPart*) final",ERROR_CODE::LOGIC); next = cp;}

	virtual inline CellPart* getNext(void) const noexcept final{ return next;}
	virtual bool isLast(void) const noexcept final{ return next == nullptr;}

	virtual void print( const bool keepMarkUp) const = 0;
};

#endif /* CELL_PART_H_ */
