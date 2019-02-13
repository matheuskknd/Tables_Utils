#include"Converter.h"

natural Converter::TableColumnLimit = GREATER::NATURAL;

void Converter::parse_Column_String( natural column, AeternalBuffer& bucket) noexcept{

//The parse is made correctly until: "MWLQKWU" == "4294967295", that is the biggest natural number on 32 bits variable.

	if( column > TableColumnLimit )
		fail_report("One column exceeds the limit suported by the specified table program.",ERROR_CODE::_DOMAIN);

	long int aux = 26, sum = 26;

	while( sum < column )
		sum += ( aux *= 26 );

	sum -= aux;

	while( ( aux /= 26 ) != 0 ){

		const char&& temp = (column-sum-1)/aux;
		column -= (1+temp)*aux;

		bucket << static_cast<char>( temp + 'A' );
		sum -= aux;
	}
}


natural Converter::parse_String_Column( natural legth, const char * const column) noexcept{

//The parse is made correctly until: "MWLQKWU" == "4294967295", that is the biggest natural number on 32 bits variable.

	bigNatural aux = 1, sum = 0;

	if( column != nullptr ){

		while( legth != 0 ){

			sum += aux * ( column[ legth -= 1 ] - 'A' + 1 );
			aux *= 26;
		}

		if( sum > TableColumnLimit )
			fail_report("One column exceeds the limit suported by the specified table program.",ERROR_CODE::_DOMAIN);
	}

return sum;}
