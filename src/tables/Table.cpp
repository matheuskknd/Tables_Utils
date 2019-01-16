#include"Table.h"

#include"../buffers/AeternalBuffer.h"

#include<new>
using std::bad_alloc;

#ifdef PARALLELIZING

	#include<thread>
	using std::thread;

#endif

Table::Table( const char * const fName) noexcept try{

	FILE * file = fopen(fName,"rb");

	if( file == nullptr )
		fail_report("file containing the table couldn't be open for binary read.",ERROR_CODE::RUNTIME);

	//Getting NbLines:

	NbLines = 0;

	while( fscanf(file,"%*[^\n]") == 0 && fscanf(file,"%*c") == 0 )
		++NbLines;

	//Allocating Lines:

#ifdef PARALLELIZING

	thread* worker = nullptr;	//Each worker will build one line, in parallel.

#endif

	if( NbLines == 0 )
		this->line = nullptr;

	else{

		this->line = new TableLine [NbLines];

#ifdef PARALLELIZING

		worker = new thread [NbLines];
#endif

		//Creting Lines:

		char* auxBuf = new char [4096];
		natural aux, maxC, l = 0;
		AeternalBuffer buf;

		rewind(file);

		while( aux = fread(auxBuf,sizeof(char),4096,file) ){

			for( natural i = 0; i != aux; ++i){

				if( auxBuf[i] == '\n' ){

#ifdef PARALLELIZING

					const char* const&& aux = buf.compileAndRelease();
					TableLine * const&& LNE = this->line+l;

					worker[l] = (thread&&) thread( [aux,LNE](void) noexcept -> void{ LNE->setLine(aux); } );
#else

					line[l].setLine(buf.compileAndRelease());
#endif
					++l;

				}else
					buf << auxBuf[i];
			}
		}

#ifdef PARALLELIZING

		for( natural i = 0; i != NbLines; ++i)	//Waits for all the threads to finish their job
			if( worker[i].joinable() )
				worker[i].join();

		delete[] worker;	//The thread's job is finished
#endif

		runtime_assert(buf.empty(),"there's still characters on the buffer in: Table::Table(const char*)",ERROR_CODE::LOGIC);
		delete[] auxBuf;

		maxC = line[0].getNbCells();

		for( l = 1; l < NbLines; ++l)
			if( line[l].getNbCells() > maxC )
				maxC = line[l].getNbCells();

		for( l = 0; l != NbLines; ++l)
			line[l].setCorrectNbCells(maxC);	//Erro de segmentacao encontrado...
	}

	fclose(file);

}catch(bad_alloc){

	fail_report("Table::Table(const char*)",ERROR_CODE::BAD_ALLOC);
}


Table* Table::create_table( const progression_t pt, const apply_on where, const int step, const natural NbIter) const noexcept try{

	Table* temp = new Table;

	temp->NbLines = where == apply_on::LINE ? this->NbLines*NbIter : this->NbLines;

	if( NbLines != 0 ){

		temp->line = new TableLine [temp->NbLines];

		if( where == apply_on::LINE ){

			natural i, j = 0;

			while( j != temp->NbLines ){		//On the new Table

				i = 0;

				while( i != this->NbLines ){	//On the old Table

					temp->line[j].update_line(pt,where,step,j/this->NbLines,this->line[i]);
					++i; ++j;
				}
			}


		}else{

			for( natural i = 0; i != this->NbLines; ++i)
				for( natural j = 0; j != NbIter; ++j)
					temp->line[i].update_line(pt,where,step,j,this->line[i]);
		}

	}else
		temp->line = nullptr;

	return temp;

}catch(bad_alloc){

	fail_report("Table* Table::create_table(progression_t,apply_on,natural,natural) const",ERROR_CODE::BAD_ALLOC);
}

void Table::print( const bool keepMarkUp) const noexcept{

	for( natural i = 0; i != NbLines; ++i)
		line[i].print(keepMarkUp);
}
