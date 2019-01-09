#include"Converter.h"

natural Converter::TableColumnLimit = 0;

void Converter::parse_Column_String( natural column, AeternalBuffer& bucket) noexcept{

	if( column > TableColumnLimit )
		fail_report("One column exceed the limit suported by the specified table program.",ERROR_CODE::_DOMAIN);

	char aux;

	if( column > 702 ){		//If it has 3 letters...

		aux = (column-703)/676;
		column -= (1+aux)*676;

		bucket << static_cast<char>( aux + 'A' );
	}

	if( column > 26 ){		//If it has 2 letters...

		aux = (column-27)/26;
		column -= (1+aux)*26;

		bucket << static_cast<char>( aux + 'A' );
	}

	bucket << static_cast<char>( column + 'A' -1 );
}


natural Converter::parse_String_Column( const char * const column) noexcept{

	if( column == nullptr || column[0] == '\0' )
		return 0;

	natural aux;

	if( column[1] == '\0' )			//Lenght equal to 1
		aux = column[0] - 'A' + 1;

	else if( column[2] == '\0' )	//Lenght equal to 2
		aux = ( column[1] - 'A' + 1 ) + 26 * ( column[0] - 'A' + 1 );

	else if( column[3] == '\0' )	//Lenght equal to 3
		aux = ( column[2] - 'A' + 1 ) + 26 * ( column[1] - 'A' + 1 ) + 676 * ( column[0] - 'A' + 1 );

	else
		fail_report("trying to parse invalid string to column in natural Converter::parse_String_Column( const char*)",ERROR_CODE::_DOMAIN);

	if( aux > TableLineLimit )
		fail_report("One line exceed the limit suported by the specified table program.",ERROR_CODE::_DOMAIN);

return aux;}
