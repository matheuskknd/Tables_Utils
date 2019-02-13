#include"tables/Package_Table.h"
#include"PCA.h"

#include<iostream>
using std::cout;
using std::cerr;

#include<cstring>
using std::strtoul;
using std::strcmp;
using std::atoi;

[[noreturn]] void fail_report( const char * const description, const ERROR_CODE error) noexcept{

	static constexpr const char * hashes = "################################";
	cerr << "\n\n" << hashes << "\nA";

	if( error == ERROR_CODE::BAD_ALLOC )
		cerr << " Bad Alloc";

	else if( error == ERROR_CODE::RUNTIME )
		cerr << " Runtime";

	else if( error == ERROR_CODE::_DOMAIN )
		cerr << " Domain";

	else if( error == ERROR_CODE::LOGIC )
		cerr << " Logic";

	else
		cerr << "n Unexpected";

	cerr << " Exception ocurred during the exection";

	if( error == ERROR_CODE::BAD_ALLOC )
		cerr << " in: " << description;
	else
		cerr << ", description: " << description;

	cerr << "\nProgram is shuting down...\n" << hashes << "\n\n";

exit(error);}


int main( const int argc, const char * const * const argv){

	if( argc < 8 || argc%4 != 0 )
		fail_report("wrong number of parameters!",ERROR_CODE::RUNTIME);

	if( strcmp(argv[2],"Excel") == 0 )
		Converter::setCompatibilityToExcel();
	else
		Converter::setCompatilityToCalc();

	Table * temp, * old;

	try{

		old = new Table(argv[1]);	//The first table, built from the initial file.

	}catch(...){

		fail_report("int main(int,char**)",ERROR_CODE::BAD_ALLOC);
	}

	natural NbIter;
	int step;

	for( natural i = 4; i != argc; i += 4){

		NbIter = strtoul(argv[i+3],nullptr,10);
		step = atoi(argv[i+2]);

		if( strcmp(argv[i],"-G") == 0 && step == 0 )
			fail_report("There's a geometric progression with '0' as step in the parameters, wich generates invalid domain.",ERROR_CODE::_DOMAIN);

		if( strcmp(argv[i+1],"-L") == 0 && NbIter > Converter::getLineLimit() )
			fail_report("There's a progression in lines with more lines than the table program suports.",ERROR_CODE::_DOMAIN);

		temp = old->create_table(strcmp(argv[i],"-A") == 0 ? progression_t::AP : progression_t::GP,strcmp(argv[i+1],"-L") == 0 ? apply_on::LINE : apply_on::COLUMN,step,NbIter);

		delete old;
		old = temp;
	}

	temp->print(strcmp(argv[3],"keep") == 0);
	delete temp;

return 0;}
