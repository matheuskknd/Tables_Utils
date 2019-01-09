#ifndef AETERNALIS_STRING_H_
#define AETERNALIS_STRING_H_

#include"Package_Buffer.h"

class AeternalBuffer final{

private: /* Attributes */

	static constexpr ltNatural BSIZE = 4096;

	struct buffer final{

		struct buffer * next;
		char string [BSIZE];
	};

	struct buffer * FIRST, * LAST;
	ltNatural NbBuffers, NbChars;

private:  /* Methods */

	inline AeternalBuffer& receiveChar( const char c) noexcept{ LAST->string[NbChars] = c; NbChars++; if( NbChars == BSIZE ) extendBuffer(); return *this;}
	void extendBuffer(void) noexcept;

public:  /* Methods */

	AeternalBuffer(void) noexcept;
	~AeternalBuffer() noexcept;

//#############################################
//############ getters and setters ############
//#############################################

	inline ltNatural getNbBuffers(void) const noexcept{ return NbBuffers+1;}

	inline natural size(void) const noexcept{ return NbChars + BSIZE*NbBuffers;}
	inline bool empty(void) const noexcept{ return size() == 0;}

//#############################################
//########### String use operations ###########
//#############################################

	natural writeAndRelease( FILE *&, const bool keepOpen = true) noexcept;	//Writes on the end of that file and destroy the buffer.
	natural justWrite( FILE *&, const bool keepOpen = true) const noexcept;	//Just writes on that file...

	char * compileAndRelease( bigNatural * lenght = nullptr) noexcept;	//Compile and destroy the buffer.
	char * justCompile( bigNatural * lenght = nullptr) noexcept;	 	//just compile the buffer entire buffer into a long string like structure.

	natural showAndRelease(void) noexcept;		//Show and destroy the buffer.
	natural justShow(void) const noexcept;		//Just Show...

	void justRelease(void) noexcept;

	void backspace( natural how_many) noexcept;
	friend void backspace( AeternalBuffer&) noexcept;

//############################################
//########## Buffering Operators << ##########
//############################################

	inline AeternalBuffer& operator<<( const char c) noexcept{ return receiveChar(c);}

	AeternalBuffer& operator<<( const char * const) noexcept;
	AeternalBuffer& operator<<( slimNatural) noexcept;

	AeternalBuffer& operator<<( short int) noexcept;
	AeternalBuffer& operator<<( int) noexcept;
	AeternalBuffer& operator<<( long int) noexcept;

	AeternalBuffer& operator<<( ltNatural) noexcept;
	AeternalBuffer& operator<<( natural) noexcept;
	AeternalBuffer& operator<<( bigNatural) noexcept;

	AeternalBuffer& operator<<( const AeternalBuffer& otherBuffer) noexcept;	//Copy the second buffer into the first... (It's diferent from what being a bufferable means)

//#############################################
//############## Other Operators ##############
//#############################################

	inline AeternalBuffer& operator<<( const ConstBufferable& entity) noexcept{ entity << *this; return *this;}
	inline AeternalBuffer& operator<<( Bufferable& entity) noexcept{ entity << *this; return *this;}

	inline AeternalBuffer& operator<<( void (*f)(AeternalBuffer&) noexcept) noexcept{ f(*this); return *this;}	//Integrate functions like "backspace" bellow.

	inline bool operator==( const AeternalBuffer& other) const{ return !(*this != other);}
	bool operator!=( const AeternalBuffer& other) const;
};

//The following non-member functions prototype declaration is needed, this will "be owned by this class only" due to its signature.
void backspace( AeternalBuffer& str) noexcept;

#endif /* AETERNALIS_STRING_H_ */
