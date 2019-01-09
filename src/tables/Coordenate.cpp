#include"Coordenate.h"

void Coordenate::print( const bool keepMarkUp) const noexcept{

	static AeternalBuffer buf;	//Only one thread can print at a time...

	for( natural i = 0; i != 6 && pre_str[i] != '\0'; ++i)
		buf << pre_str[i];

	if( column_is_const )
		buf << '$';

	Converter::parse_Column_String(column,buf);

	if( line_is_const )
		buf << '$';

	buf << line;
	buf.showAndRelease();
}
