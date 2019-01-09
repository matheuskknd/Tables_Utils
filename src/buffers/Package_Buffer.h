#ifndef PACKAGE_BUFFER_H
#define PACKAGE_BUFFER_H

	#include"../PCA.h"

	#if defined( AETERNALIS_STRING_H_ )		//It is calling...

		#include<cstdio>
		#include"Bufferable.h"

	#elif defined( CIRCULAR_BUFFER_H ) || defined( BUFFERABLE_H_ )		//It is calling...

	#else									//Unknown calling...

		#include<cstdio>
		#include"Bufferable.h"
		#include"AeternalBuffer.h"
		#include"CircularBuffer.h"

	#endif /* Who is calling */

#endif /* PACKAGE_BUILDING_H */
