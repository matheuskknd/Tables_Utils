#ifndef PACKAGE_TABLE_H
#define PACKAGE_TABLE_H

	#include"../PCA.h"

	#if defined( CELL_PART_H_ )		//It is calling...

	#elif defined( CONVERTER_H_ )	//It is calling...

		#include"../buffers/AeternalBuffer.h"

	#elif defined( COORDENATE_H_ )	//It is calling...

		#include"CellPart.h"
		#include"../buffers/AeternalBuffer.h"
		#include"Converter.h"

	#elif defined( SMALL_TEXT_H_ )	//It is calling...

		#include"CellPart.h"

	#elif defined( TEXT_PART_H_ )	//It is calling...

		#include"CellPart.h"

	#elif defined( RULE_H )		//It is calling...

		#include"CellPart.h"

	#elif defined( TABLE_CELL_H_ )	//It is calling...

		#include"../buffers/Package_Buffer.h"
		#include"Converter.h"
		#include"CellPart.h"
		#include"SmallText.h"
		#include"TextPart.h"
		#include"Coordenate.h"
		#include"Rule.h"

	#elif defined( TABLE_LINE_H_ )	//It is calling...

		#include"../buffers/Package_Buffer.h"
		#include"TableCell.h"

	#elif defined( TABLE_H_ )		//It is calling...

		#include"TableLine.h"

	#else							//Unknown calling...

		#include"Converter.h"
		#include"TableLine.h"
		#include"Table.h"

	#endif /* Who is calling */

#endif /* PACKAGE_TABLE_H */
