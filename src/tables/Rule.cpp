#include"Rule.h"

#include<iostream>
using std::cout;

CellPart* Rule::applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept{

#ifndef TESTING_PROGRAM
	#error missing real definition here...
#endif

	fail_report("call to incomplete method: CellPart* Rule::applyInColumns(natural,int,operation) const",ERROR_CODE::LOGIC);

return nullptr;}


CellPart* Rule::applyInLines( const natural iter, const int step, const operation oprtn) const noexcept{

#ifndef TESTING_PROGRAM
	#error missing real definition here...
#endif

	fail_report("call to incomplete method: CellPart* Rule::applyInLines(natural,int,operation) const",ERROR_CODE::LOGIC);

return nullptr;}


void Rule::print( const bool keepMarkUp) const noexcept{

	if( keepMarkUp )
		cout << "-&#" << ( pgt == AP ? 'A' : 'G' ) << '#' << ( aplo == LINE ? 'L' : 'C' ) << '#' << step << '#' << frequency << '#' << since << '#' << until << '#' << vigor << '#';

	if( ruled != nullptr ){

		const CellPart* browser = ruled;

		do{

			browser->print(keepMarkUp);

		}while( ( browser = browser->getNext() ) != next );
	}

	if( keepMarkUp )
		cout << "#&-";
}


Rule::~Rule() noexcept{

	if( ruled != nullptr ){

		const CellPart * clean, * browser = ruled;

		do{

			clean = browser;
			browser = browser->getNext();

			delete clean;

		}while( browser != next );
	}
}
