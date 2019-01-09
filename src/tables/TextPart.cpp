#include"TextPart.h"

#include<iostream>
using std::cout;

void TextPart::print( const bool keepMarkUp) const noexcept{

	cout << string->str;
}


TextPart::~TextPart() noexcept{

	--(string->NbPtrs);

	if( string->canBeDeleted() )
		delete string;
}
