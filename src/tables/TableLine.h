#ifndef TABLE_LINE_H_
#define TABLE_LINE_H_

#include"Package_Table.h"

class TableLine final{

/*
*	24 bytes table line.
*/

private: /* Attributes */

	const TableCell * FIRST;
	TableCell * LAST;

	natural NbCells;
	natural NbEmpty;

public: /* Methods */

	inline constexpr TableLine(void) noexcept : FIRST{nullptr}, LAST{nullptr}, NbCells{0}, NbEmpty{0} {}
	~TableLine() noexcept;

	void update_line( const progression_t pt, const apply_on where, const int step, const natural NbIter, const TableLine& other) noexcept;	//Adds to this line, the progression applied on other line.

	void print( const bool keepMarkUp) const noexcept;
	void setLine( const char * const line) noexcept;					//Get an Entire line to spread into several cells.

	inline natural getNbCells(void) const noexcept{ return NbCells;}
	void setCorrectNbCells( const natural how_many) noexcept;			//Corrects the number of cell based on the greater line of the table.
};

#endif /* TABLE_LINE_H_ */
