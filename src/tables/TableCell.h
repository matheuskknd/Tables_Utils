#ifndef TABLE_CELL_H_
#define TABLE_CELL_H_

#include"Package_Table.h"

class TableCell final{

/*
*	24 bytes table cell.
*/

private: /* Attributes */

	const TableCell * next;	//Next cell on the same line.
	const CellPart * FIRST;	//First part of it.

	natural NbNextEmpty;	//Number of empty cells until the first with content.
	natural NbPartes;		//Total number of parts.

private: /* Methods */

	inline static constexpr natural times( const natural x, const int y) noexcept{ return y < 0 ? x/-y : x*y;}
	inline static constexpr natural plus( const natural x, const int y) noexcept{ return x + y;}

	inline static natural process_rule( AeternalBuffer& text, AeternalBuffer& auxBuf, const char* const begin, const CellPart *& FIRST, CellPart *& LAST) noexcept;
	inline constexpr TableCell( const natural NbE, const natural NbP) noexcept : next{nullptr}, FIRST{nullptr}, NbNextEmpty{NbE}, NbPartes{NbP} {}

public: /* Methods */

	inline constexpr TableCell(void) noexcept : next{nullptr}, FIRST{nullptr}, NbNextEmpty{0}, NbPartes{0} {}
	~TableCell() noexcept;

	void setCell( const char * const from) noexcept;

	inline void setNbNextEmpty( const natural NbNextEmpty) noexcept{ this->NbNextEmpty = NbNextEmpty;}
	inline void setNext( const TableCell* next) noexcept{ this->next = next;}

	inline const TableCell * getNext(void) const noexcept{ return next;}
	void print( const bool keepMarkUp) const noexcept;

	TableCell* getCellApplying( const progression_t pt, const apply_on where, const int step, const natural NbIter) const noexcept;
};

#endif /* TABLE_CELL_H_ */
