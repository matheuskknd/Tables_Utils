#include"AeternalBuffer.h"

#include<new>
using std::bad_alloc;

#include<cstdio>
using std::putchar;
using std::fwrite;

AeternalBuffer::AeternalBuffer(void) noexcept{

	try{ FIRST = new struct buffer; }catch(bad_alloc){ fail_report("AeternalBuffer::AeternalBuffer(void)",ERROR_CODE::BAD_ALLOC);}

	FIRST->next = nullptr;
	LAST = FIRST;

	NbBuffers = 0;
	NbChars = 0;
}


void AeternalBuffer::extendBuffer(void) noexcept{

	NbChars = 0;
	++NbBuffers;

	try{ LAST->next = new struct buffer; }catch(bad_alloc){ justRelease(); fail_report("void AeternalBuffer::extendBuffer(void)",ERROR_CODE::BAD_ALLOC);}

	( LAST = LAST->next )->next = nullptr;

return ;}


natural AeternalBuffer::writeAndRelease( FILE *& file, const bool keepOpen) noexcept{

	if( file == nullptr )
		return 0;

	const natural NbWritten = size();

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * clean;

		do{

			FIRST = ( clean = FIRST )->next;

			fwrite(clean->string,sizeof(char),BSIZE,file);

			delete(clean);

		}while( ( NbBuffers -= 1 ) != 0 );
	}

	NbChars -= fwrite(FIRST->string,sizeof(char),NbChars,file);
	fflush(file);

	if( !keepOpen ){

		fclose(file);
		file = nullptr;
	}

return NbWritten;}


natural AeternalBuffer::justWrite( FILE *& file, const bool keepOpen) const noexcept{

	if( file == nullptr )
		return 0;

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * browser = FIRST;

		do{

			fwrite(browser->string,sizeof(char),BSIZE,file);

		}while( ( browser = browser->next )->next != nullptr );
	}

	fwrite(LAST->string,sizeof(char),NbChars,file);
	fflush(file);

	if( !keepOpen ){

		fclose(file);
		file = nullptr;
	}

return this->size();}


char* AeternalBuffer::compileAndRelease( bigNatural * lenght) noexcept{

	const bigNatural totalLenght = this->size();

	if( lenght != nullptr )
		*lenght = totalLenght;

	char * compilation;

	try{ compilation = new char [totalLenght+1]; }catch(bad_alloc){ justRelease(); fail_report("char* AeternalBuffer::compileAndRelease( natural*)",ERROR_CODE::BAD_ALLOC);}

	compilation[totalLenght] = 0;	//Equivalent of NULL on Strigs...
	bigNatural position = 0;

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * clean;

		do{

			clean = FIRST;
			FIRST = FIRST->next;

			for( ltNatural i = 0; i != BSIZE; ++i, ++position)
				compilation[position] = clean->string[i];

			delete(clean);
			--NbBuffers;

		}while( NbBuffers != 0 );
	}

	for( ltNatural i = 0; i != NbChars; ++i, ++position)
		compilation[position] = LAST->string[i];

	NbChars =  0;

return compilation;}


char * AeternalBuffer::justCompile( bigNatural * lenght) noexcept{

	const bigNatural totalLenght = this->size();

	if( lenght != nullptr )
		*lenght = totalLenght;

	char * compilation;

	try{ compilation = new char [totalLenght+1]; }catch(bad_alloc){ justRelease(); fail_report("char * AeternalBuffer::justCompile( bigNatural*)",ERROR_CODE::BAD_ALLOC);}

	compilation[totalLenght] = 0;	//Equivalent of NULL on Strigs...
	bigNatural position = 0;

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * browser = FIRST;

		do{

			for( ltNatural i = 0; i != BSIZE; ++i,++position)
				compilation[position] = browser->string[i];

		}while( ( browser = browser->next )->next != nullptr );
	}

	for( ltNatural i = 0; i != NbChars; ++i, ++position)
		compilation[position] = LAST->string[i];

return compilation;}


natural AeternalBuffer::showAndRelease(void) noexcept{

	const natural NbCharsBefore = this->size();

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * clean;

		do{

			FIRST = ( clean = FIRST )->next;

			for( ltNatural i = 0; i != BSIZE; ++i)
				putchar(clean->string[i]);

			delete(clean);

		}while( ( NbBuffers -= 1 ) != 0 );
	}

	for( ltNatural i = 0; i != NbChars; ++i)
		putchar(FIRST->string[i]);

	NbChars = 0;

return NbCharsBefore;}


natural AeternalBuffer::justShow(void) const noexcept{

	if( NbBuffers != 0 ){	//Remember this number is actually (NbBuffers-1)... If there are 5 buffers, it will be 4!

		struct buffer * browser = FIRST;

		do{

			for( ltNatural i = 0; i != BSIZE; ++i)
				putchar(browser->string[i]);

		}while( ( browser = browser->next )->next != nullptr );
	}

	for( ltNatural i = 0; i != NbChars; ++i)
		putchar(LAST->string[i]);

return this->size();}


void AeternalBuffer::justRelease(void) noexcept{

	if( NbBuffers != 0 ){

		struct buffer * clean;

		for( natural i=0; i != NbBuffers; ++i){

			FIRST = ( clean = FIRST )->next;
			delete(clean);
		}

		NbBuffers = 0;
	}

	NbChars = 0;

return ;}


void AeternalBuffer::backspace( const natural how_many) noexcept{

	if( how_many <= NbChars )
		NbChars -= how_many;

	else{

		if( how_many <= size() ){

			const natural charLeft = size() - how_many;
			NbChars = charLeft % BSIZE;

			const natural bufferLeft = charLeft/BSIZE;

			if( NbBuffers > bufferLeft ){

				struct buffer * clean = FIRST;
				NbBuffers = bufferLeft;

				for( natural i = 0; i != bufferLeft; ++i)
					clean = clean->next;

				struct buffer * aux = clean;

				clean = clean->next;
				aux->next = nullptr;

				while( clean != nullptr ){

					clean = ( aux = clean )->next;
					delete(aux);
				}
			}

		}else
			justRelease();
	}
}


AeternalBuffer::~AeternalBuffer() noexcept{

	LAST = FIRST;

	while( LAST != nullptr ){

		LAST = ( FIRST = LAST )->next;
		delete(FIRST);
	}
}


//	Operators:


AeternalBuffer& AeternalBuffer::operator<<( const char * const word) noexcept{

	if( word != nullptr ){

		natural i = 0;

		while( word[i] != '\0' ){

			this->receiveChar(word[i]);
			++i;
		}
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( slimNatural n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	bool started = false;

	for( slimNatural i = 100, digit; i != 0; i /= 10){	//Unsigned char goes 0 to 255

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( short int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	if( n < 0 ){

		this->receiveChar('-');
		n *= -1;
	}

	slimNatural digit;
	bool started = false;

	for( short int i = 10000; i != 0; i /= 10){	//Short int goes -32.767 to 32.767 (solved with 10^4)

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( long int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	if( n < 0 ){

		this->receiveChar('-');
		n *= -1;
	}

	if( n <= 65535 )
		return *this << (unsigned short int) n;

	if( n <= 4294967295 )
		return *this << (unsigned int) n;

	slimNatural digit;
	bool started = false;

	for( long int i = 1000000000000000000UL; i != 0; i /= 10){	//Long int goes -9223372036854775807 to 9223372036854775807 (solved with 10^18)

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	if( n < 0 ){

		this->receiveChar('-');
		n *= -1;
	}

	slimNatural digit;
	bool started = false;

	for( int i = 1000000000; i != 0; i /= 10){ //Regular int goes -2147483647 to 2147483647 (solved with 10^9)

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( unsigned short int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	slimNatural digit;
	bool started = false;

	for( unsigned short int i = 10000; i != 0; i /= 10){	//Short int goes 0 to 65.535 (solved with 10^4)
	
		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( unsigned long int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	if( n <= 65535 )
		return *this << (unsigned short int) n;

	if( n <= 4294967295 )
		return *this << (unsigned int) n;

	slimNatural digit;
	bool started = false;

	for( unsigned long int i = 10000000000000000000UL; i != 0; i /= 10){	//Long int goes 0 to 18.446.744.073.709.551.615 (solved with 10^19)

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( unsigned int n) noexcept{

	if( n == 0 )
		return this->receiveChar('0');

	slimNatural digit;
	bool started = false;

	for( unsigned int i = 1000000000; i != 0; i /= 10){ //Regular int goes 0 to 4.294.967.295 (solved with 10^9)

		digit = n/i;
		n -= i*digit;

		if( !started && digit != 0 )
			started = true;

		if( started )
			this->receiveChar( '0' + digit );
	}

return *this;}


AeternalBuffer& AeternalBuffer::operator<<( const AeternalBuffer& otherBuffer) noexcept{

	if( otherBuffer.NbBuffers != 0 ){

		struct buffer * browser = otherBuffer.FIRST;

		do{

			for( ltNatural i = 0; i != BSIZE; ++i)
				this->receiveChar(browser->string[i]);

			browser = browser->next;

		}while( browser->next != nullptr );
	}

	for( ltNatural i = 0; i != otherBuffer.NbChars; ++i)
		this->receiveChar(otherBuffer.LAST->string[i]);

return *this;}


bool AeternalBuffer::operator!=( const AeternalBuffer& other) const{

	if( this == &other )	//100% sure its the same...
		return false;

	if( this->size() != other.size() )
		return true;

	if( NbBuffers != 0 ){

		struct buffer * browser1 = this->FIRST;
		struct buffer * browser2 = other.FIRST;

		do{

			for( ltNatural i = 0; i != BSIZE; ++i)
				if( browser1->string[i] != browser2->string[i] )
					return true;

			browser1 = browser1->next;
			browser2 = browser2->next;

		}while( browser1->next != nullptr );	//Doesn't matters wich of them...
	}

	for( ltNatural i = 0; i != NbChars; ++i)
		if( this->LAST->string[i] != other.LAST->string[i] )
			return true;

return false;}


//	No member:


void backspace( AeternalBuffer& str) noexcept{

	if( str.NbChars != 0 )
		--(str.NbChars);
	else
		str.backspace(1);

return ;}
