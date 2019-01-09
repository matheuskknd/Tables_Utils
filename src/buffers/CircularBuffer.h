#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include"Package_Buffer.h"

template< natural N>
class CircularBuffer{

public: /* Attributes */

	natural put, get;
	char str[N];
	bool full;

public: /* Methods */

	inline CircularBuffer(void) noexcept : put{N-1}, get{N-1}, full{false} { for( natural i = 0; i != N; ++i) str[i] = '\0'; static_assert(N>1,"\n\n\tThe CircularBuffer must be size 2 or more!\n\n");}
	inline ~CircularBuffer() = default;

	inline char getFirst(void) noexcept{ return !full ? str[ get = 0 ] : str[ get = ( put+1 == N ? 0 : put+1 ) ];}
	inline char getNext(void) noexcept{ return get == put ? '\0' : str[ get = ( get+1 == N ? 0 : get+1 ) ];}

	inline CircularBuffer& operator<<( const char c) noexcept{ str[ put = ( put+1 == N ? 0 : put+1 ) ] = c; full = full || put == N-1; return *this;}
};

#endif /* CIRCULAR_BUFFER_H */
