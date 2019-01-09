#ifndef TABLE_H_
#define TABLE_H_

#include"Package_Table.h"

class Table final{

/*
*	16 bytes table representation.
*/

private: /* Attributes */

	TableLine * line;
	natural NbLines;

	inline constexpr Table(void) noexcept : line{nullptr}, NbLines{0} {}

public: /* Methods */

	inline ~Table() noexcept{ delete[] line;}
	Table( const char * const fName) noexcept;

	Table* create_table( const progression_t pt, const apply_on where, const int step, const natural NbIter) const noexcept;
	void print( const bool keepMarkUp = false) const noexcept;
};

#endif /* TABLE_H_ */
