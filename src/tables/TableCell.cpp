#include"TableCell.h"

#include<new>
using std::bad_alloc;

#include<iostream>
using std::cout;

TableCell::TableCell( const char * const str) noexcept try{

	FIRST = nullptr;
	next = nullptr;

	NbPartes = ( NbNextEmpty = 0 );

	//Parses, Syntactic Checking and creation

	CellPart * LAST = nullptr;
	AeternalBuffer text, auxBuf;
	natural j, i = 0;

	bool done;

	while( str[i] != '\0' ){

		done = false;
		j = i;

		do{

			if( str[j] == '$' || ( str[j] >= 'A' && str[j] <= 'Z' ) ){

				auxBuf.justRelease();
				const bool constC = str[j] == '$';

				if( !constC ){		//The first element is a letter.

					for( natural i = 0; i != 3; ++i, ++j)
						if( str[j] >= 'A' && str[j] <= 'Z' )
							auxBuf << str[j];
						else
							break;

				}else{

					bool done = false;
					++j;

					for( natural i = 0; i != 3; ++i, ++j)
						if( str[j] >= 'A' && str[j] <= 'Z' ){

							auxBuf << str[j];
							done = true;

						}else
							break;

					if( !done )
						break;	//Returns to the main loop...
				}

				const char* aux = auxBuf.compileAndRelease();
				const natural column = Converter::parse_String_Column(aux);
				delete[] aux;

				if( str[j] != '$' && !( str[j] >= '0' && str[j] <= '9' ) )
					break;		//Returns to the main loop...

				const bool constL = str[j] == '$';

				if( constL )
					++j;

				if( str[j] < '0' && str[j] > '9' )
					break;		//Returns to the main loop...

				char* aux2;
				const natural line = strtoul(&str[j],&aux2,10);
				i += aux2 - &str[i];

				const natural size = text.size();
				aux = text.compileAndRelease();
				done = true;

				if( size <= 6 ){	//The aux chars enter inside the new coordenate, otherwise it becomes another text part apart.

					char ttt[6] = {'\0','\0','\0','\0','\0','\0'};

					for( slimNatural i = 0; aux[i] != '\0'; ++i)
						ttt[i] = aux[i];

					if( FIRST == nullptr ){	//First part...

						LAST = new Coordenate(column,constC,line,constL,char6(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5]));
						FIRST = LAST;

					}else{

						LAST->setNext( new Coordenate(column,constC,line,constL,char6(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5])) );
						LAST = LAST->getNext();
					}

					delete[] aux;

				}else if( size <= 8 ){

					char ttt[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};

					for( slimNatural i = 0; aux[i] != '\0'; ++i)
						ttt[i] = aux[i];

					if( FIRST == nullptr ){	//First part...

						LAST = new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]);
						FIRST = LAST;

					}else{

						LAST->setNext( new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]) );
						LAST = LAST->getNext();
					}

					LAST->setNext( new Coordenate(column,constC,line,constL) );
					LAST = LAST->getNext();
					delete[] aux;

				}else{

					if( FIRST == nullptr ){	//First part...

						LAST = new TextPart(aux);
						FIRST = LAST;

					}else{

						LAST->setNext( new TextPart(aux) );
						LAST = LAST->getNext();
					}

					LAST->setNext( new Coordenate(column,constC,line,constL) );
					LAST = LAST->getNext();
				}
			}

		}while( false );

		if( done )
			continue;

		if( str[i] == '-' && str[i+1] == '&' && str[i+2] == '#' ){	//If it's a rule, skip it.

			i += 3 + TableCell::process_rule(text,auxBuf,str+i+3,FIRST,LAST);
			continue;
		}

		text << str[i];
		++i;
	}

	if( !text.empty() ){

		const natural size = text.size();
		const char* aux = text.compileAndRelease();

		if( size <= 8 ){

			char ttt[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};

			for( slimNatural i = 0; aux[i] != '\0'; ++i)
				ttt[i] = aux[i];

			if( FIRST == nullptr ){	//First part...

				LAST = new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]);
				FIRST = LAST;

			}else{

				LAST->setNext( new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]) );
				LAST = LAST->getNext();
			}

			delete[] aux;

		}else{

			if( FIRST == nullptr ){	//First part...

				LAST = new TextPart(aux);
				FIRST = LAST;

			}else{

				LAST->setNext( new TextPart(aux) );
				LAST = LAST->getNext();
			}
		}
	}

	delete[] str;

}catch(bad_alloc){

	fail_report("TableCell::TableCell(const char*)",ERROR_CODE::BAD_ALLOC);
}


natural TableCell::process_rule( AeternalBuffer& text, AeternalBuffer& auxBuf, const char* const str, const CellPart *& FIRST, CellPart *& LAST) noexcept try{

	static constexpr const char* error = "syntatic error in rule entry '-&#'. It must be: -&#[A|G]#[L|C]#natural#natural#natural#natural#natural#[anything]#&-";

	natural j, i = 0;
	char* aux;

	//Parses, Syntactic Checking and creation

	if( str[i] != 'A' && str[i] != 'G' )
		fail_report(error,ERROR_CODE::RUNTIME);

	const progression_t pgt = str[i] == 'A' ? AP : GP;
	i += 2;

	if( str[i-1] != '#' && str[i] != 'L' && str[i] != 'C' )
		fail_report(error,ERROR_CODE::RUNTIME);

	const apply_on apl = str[i] == 'L' ? LINE : COLUMN;
	i += 2;

	if( str[i-1] != '#' && ( str[i] < '0' || str[i] > '9' ) )
		fail_report(error,ERROR_CODE::RUNTIME);

	const natural step = strtoul(str+i,&aux,10);
	i += aux - (str+i) + 1;

	if( str[i-1] != '#' && ( str[i] < '0' || str[i] > '9' ) )
		fail_report(error,ERROR_CODE::RUNTIME);

	const natural frec = strtoul(str+i,&aux,10);
	i += aux - (str+i) + 1;

	if( str[i-1] != '#' && ( str[i] < '0' || str[i] > '9' ) )
		fail_report(error,ERROR_CODE::RUNTIME);

	const natural since = strtoul(str+i,&aux,10);
	i += aux - (str+i) + 1;

	if( str[i-1] != '#' && ( str[i] < '0' || str[i] > '9' ) )
		fail_report(error,ERROR_CODE::RUNTIME);

	const natural until = strtoul(str+i,&aux,10);
	i += aux - (str+i) + 1;

	if( str[i-1] != '#' && ( str[i] < '0' || str[i] > '9' ) )
		fail_report(error,ERROR_CODE::RUNTIME);

	const natural vigor = strtoul(str+i,&aux,10);
	i += aux - (str+i) + 1;

	if( str[i-1] != '#' )		//Necessary to avoid some human errors...
		fail_report(error,ERROR_CODE::RUNTIME);

	if( pgt == GP && step == 0 )
		fail_report("There's a geometric progression with '0' as step on some rule, wich generates invalid domain.",ERROR_CODE::_DOMAIN);

	Rule* INIT;

	if( FIRST == nullptr ){

		INIT = new Rule(step,frec,since,until,vigor == 0 ? 0 : vigor+1,pgt,apl);
		FIRST = ( LAST = INIT );

	}else{

		LAST->setNext( INIT = new Rule(step,frec,since,until,vigor == 0 ? 0 : vigor+1,pgt,apl) );
		LAST = LAST->getNext();
	}

	CellPart* ILAST = nullptr;	//This represents the last ruled part.

	//Subcreation

	static constexpr const char* unfinished = "syntatic error in rule entry '-&#'. No rule end '#&-' detected at the same cell it started.";
	bool done;

	while( true ){

		if( str[i] == '\0' || str[i+1] == '\0' || str[i+2] == '\0' )	//This possible syntatic error must be checked before every loop...
			fail_report(unfinished,ERROR_CODE::RUNTIME);

		if( str[i] == '#' && str[i+1] == '&' && str[i+2] == '-' )
			break;

		done = false;
		j = i;

		do{

			if( str[j] == '$' || ( str[j] >= 'A' && str[j] <= 'Z' ) ){

				auxBuf.justRelease();
				const bool constC = str[j] == '$';

				if( !constC ){		//The first element is a letter.

					for( natural i = 0; i != 3; ++i, ++j)
						if( str[j] >= 'A' && str[j] <= 'Z' )
							auxBuf << str[j];
						else
							break;

				}else{

					bool done = false;
					++j;

					for( natural i = 0; i != 3; ++i, ++j)
						if( str[j] >= 'A' && str[j] <= 'Z' ){

							auxBuf << str[j];
							done = true;

						}else
							break;

					if( !done )
						break;	//Returns to the main loop...
				}

				const char* aux = auxBuf.compileAndRelease();
				const natural column = Converter::parse_String_Column(aux);
				delete[] aux;

				if( str[j] != '$' && !( str[j] >= '0' && str[j] <= '9' ) )
					break;		//Returns to the main loop...

				const bool constL = str[j] == '$';

				if( constL )
					++j;

				if( str[j] < '0' && str[j] > '9' )
					break;		//Returns to the main loop...

				char* aux2;
				const natural line = strtoul(str+j,&aux2,10);
				i += aux2 - (str+i);

				const natural size = text.size();
				aux = text.compileAndRelease();
				done = true;

				if( size <= 6 ){	//The aux chars enter inside the new coordenate, otherwise it becomes another text part apart.

					char ttt[6] = {'\0','\0','\0','\0','\0','\0'};

					for( slimNatural i = 0; aux[i] != '\0'; ++i)
						ttt[i] = aux[i];

					if( INIT->getRuling() == nullptr ){	//First part...

						ILAST = new Coordenate(column,constC,line,constL,char6(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5]));
						INIT->setRuling(ILAST);

					}else{

						ILAST->setNext( new Coordenate(column,constC,line,constL,char6(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5])) );
						ILAST = ILAST->getNext();
					}

					delete[] aux;

				}else if( size <= 8 ){

					char ttt[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};

					for( slimNatural i = 0; aux[i] != '\0'; ++i)
						ttt[i] = aux[i];

					if( INIT->getRuling() == nullptr ){	//First part...

						ILAST = new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]);
						INIT->setRuling(ILAST);

					}else{

						ILAST->setNext( new SmallText(ttt[0],ttt[1],ttt[2],ttt[3],ttt[4],ttt[5],ttt[6],ttt[7]) );
						ILAST = ILAST->getNext();
					}

					ILAST->setNext( new Coordenate(column,constC,line,constL) );
					ILAST = ILAST->getNext();
					delete[] aux;

				}else{

					if( INIT->getRuling() == nullptr ){	//First part...

						ILAST = new TextPart(aux);
						INIT->setRuling(ILAST);

					}else{

						ILAST->setNext( new TextPart(aux) );
						ILAST = ILAST->getNext();
					}

					ILAST->setNext( new Coordenate(column,constC,line,constL) );
					ILAST = ILAST->getNext();
				}
			}

		}while( false );

		if( done )
			continue;

		if( str[i] == '-' && str[i+1] == '&' && str[i+2] == '#' ){	//If it's a rule, skip it.

			i += 3 + TableCell::process_rule(text,auxBuf,str+i+3,INIT->getRuling(),ILAST);
			continue;
		}

		text << str[i];
		++i;
	}

	INIT->setLast(ILAST);
	return i+3;

}catch(bad_alloc){

	fail_report("natural TableCell::process_rule(AeternalBuffer&,AeternalBuffer&,const char*,const CellPart *&,CellPart *&)",ERROR_CODE::BAD_ALLOC);
}


TableCell* TableCell::getCellApplying( const progression_t pt, const apply_on where, const int step, const natural NbIter) const noexcept{

	TableCell* temp;

	try{

		temp = new TableCell(this->NbNextEmpty,this->NbPartes);

	}catch(bad_alloc){

		fail_report("TableCell* TableCell::getCellApplying(progression_t,apply_on,natural,natural) const",ERROR_CODE::BAD_ALLOC);
	}

	if( this->FIRST != nullptr ){

		const CellPart * aux = this->FIRST;
		CellPart * LAST;

		if( where == apply_on::COLUMN )
			temp->FIRST = ( LAST = aux->applyInColumns(NbIter,step,pt == progression_t::AP ? plus : times) );
		else
			temp->FIRST = ( LAST = aux->applyInLines(NbIter,step,pt == progression_t::AP ? plus : times) );

		while( aux = aux->getNext() ){

			if( where == apply_on::COLUMN )
				LAST->setNext( aux->applyInColumns(NbIter,step,pt == progression_t::AP ? plus : times) );
			else
				LAST->setNext( aux->applyInLines(NbIter,step,pt == progression_t::AP ? plus : times) );

			LAST = LAST->getNext();
		}
	}

return temp;}


void TableCell::print( const bool keepMarkUp) const noexcept{

	if( FIRST != nullptr ){

		const CellPart * browser = FIRST;

		do{

			browser->print(keepMarkUp);	//Polymorphic

		}while( browser = browser->getNext() );

		if( next != nullptr )
			for( natural i = 0; i != NbNextEmpty; ++i)
				cout << '\t';
	}
}


TableCell::~TableCell() noexcept{

	const CellPart * clean, * browser = FIRST;

	while( browser != nullptr ){

		clean = browser;
		browser = browser->getNext();

		delete clean;
	}
}
