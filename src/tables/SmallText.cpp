#include"SmallText.h"

#include<iostream>
using std::cout;

void SmallText::print( const bool keepMarkUp) const noexcept{

	natural i = 0;

	while( text[i] != '\0' )
		cout << text[(i += 1)-1];
}
