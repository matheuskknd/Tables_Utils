#include"TableLine.h"

#include<new>
using std::bad_alloc;

#include<iostream>
using std::cout;

#ifdef PARALLELIZING

	#include<thread>
	using std::thread;

	#include<list>
	using std::list;

#endif

inline natural TableLine::pow( const natural base, const natural exp) noexcept{

	natural aux = 1;

	for( natural i = 0; i != exp; ++i)
		aux *= base;

return aux;}


void TableLine::setLine( const char * const line) noexcept try{

	natural i = 0, empty = 0;
	bool isLast = false;
	AeternalBuffer buf;
	char aux;

#ifdef PARALLELIZING

	list<thread> workerList;	//Each element works on a cell.

#endif

	while( !isLast ){

		aux = line[i];

		if( isLast = ( aux == '\0' ) )
			aux = '\t';

		if( aux == '\t' ){

			if( buf.empty() )		//If no content were found sinse the last cell, it counts as an empty cell.
				++empty;

			else if( this->NbCells == 0 ){		//If it's the first cell with real content.

				this->NbCells = 1 + ( NbEmpty = empty );
				empty = 0;

#ifdef PARALLELIZING

				const char* const auxT = buf.compileAndRelease();
				TableCell* const tempCell = new TableCell;
				FIRST = ( LAST = tempCell );

				workerList.emplace_back( [tempCell,auxT](void) noexcept -> void{ tempCell->setCell(auxT); } );
#else

				FIRST = ( LAST = new TableCell );
				LAST->setCell(buf.compileAndRelease());
#endif
			}else{								//If it's any other cell with real content.

				LAST->setNbNextEmpty(empty);
				this->NbCells += 1 + empty;
				empty = 0;

#ifdef PARALLELIZING

				const char* const auxT = buf.compileAndRelease();
				TableCell* const tempCell = new TableCell;

				workerList.emplace_back( [tempCell,auxT](void) noexcept -> void{ tempCell->setCell(auxT); } );

				LAST->setNext(tempCell);
				LAST = tempCell;
#else

				auto aux = new TableCell;
				aux->setCell(buf.compileAndRelease());

				LAST->setNext(aux);
				LAST = aux;
#endif
			}

		}else
			buf << aux;

		++i;
	}

	delete[] line;

#ifdef PARALLELIZING

	for( thread& it : workerList )
		if( it.joinable() )
			it.join();
#endif

}catch(bad_alloc){

	fail_report("void TableLine::setLine(const char*)",ERROR_CODE::BAD_ALLOC);
}


void TableLine::update_line( const progression_t pt, const apply_on where, const int step, const natural NbIter, const TableLine& other) noexcept{

	const TableCell * aux = other.FIRST;

	if( aux == nullptr )
		return ;

	if( this->FIRST == nullptr ){	//An empty line

		this->FIRST = ( this->LAST = aux->getCellApplying(pt,where,pt == progression_t::GP ? pow(step,NbIter) : step*NbIter,NbIter) );
		aux = aux->getNext();

		this->NbCells = other.NbCells;
		this->NbEmpty = other.NbEmpty;

	}else
		this->NbCells += other.NbCells;

	TableCell * temp;

	while( aux != nullptr ){

		temp = aux->getCellApplying(pt,where,pt == progression_t::GP ? pow(step,NbIter) : step*NbIter,NbIter);
		aux = aux->getNext();

		this->LAST->setNext(temp);
		this->LAST = temp;
	}
}


void TableLine::print( const bool keepMarkUp) const noexcept{

	if( FIRST != nullptr ){

		for( natural i = 0; i != NbEmpty; ++i)
			cout << '\t';

		const TableCell* browser = FIRST;

		do{

			browser->print(keepMarkUp);

			if( browser = browser->getNext() )
				cout << '\t';
			else
				break;

		}while( true );
	}

	cout << '\n';
}


void TableLine::setCorrectNbCells( const natural how_many) noexcept{

	if( FIRST != nullptr ){

		LAST->setNbNextEmpty(how_many - this->NbCells);
		this->NbCells = how_many;
	}
}


TableLine::~TableLine() noexcept{

	const TableCell * clean, * browser = FIRST;

	while( browser != nullptr ){

		clean = browser;
		browser = browser->getNext();

		delete clean;
	}
}
