#include"Rule.h"

#include<iostream>
using std::cout;

#include<new>
using std::bad_alloc;

natural Rule::pow( const natural base, const natural exp) noexcept{

	natural aux = 1;

	for( natural i = 0; i != exp; ++i)
		aux *= base;

return aux;}


CellPart* Rule::applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept{

	if( vigor == 1 )	//If there's no more vigor
		return this->F_ruled->applyInColumns(iter,step,oprtn);

	Rule* temp;

	try{

		temp = new Rule(this->step,this->frequency,this->since,this->until,this->vigor == 0 ? 0 : this->vigor-1,this->pgt,this->aplo);

	}catch(bad_alloc){

		fail_report("CellPart* Rule::applyInColumns(natural,int,operation) const",ERROR_CODE::BAD_ALLOC);
	}

	const CellPart * aux1 = this->F_ruled;	//aux2 browses the new Rule, aux1 browses this Rule
	CellPart * aux2;

	if( aux1 != nullptr ){

		if( iter >= since && ( until == 0 || iter <= until ) ){	//Inside the vigor zone...

			if( this->aplo == apply_on::LINE )
				temp->F_ruled = ( aux2 = aux1->applyInLines(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );
			else
				temp->F_ruled = ( aux2 = aux1->applyInColumns(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );

		}else
			temp->F_ruled = ( aux2 = aux1->applyInColumns(iter,step,none) );	//It just gets a copy of the previous version

		while( ( aux1 = aux1->getNext() ) != this->getNext() ){

			if( iter >= since && ( until == 0 || iter <= until ) ){	//Inside the vigor zone...

				if( this->aplo == apply_on::LINE )
					aux2->setNext( aux1->applyInLines(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );
				else
					aux2->setNext( aux1->applyInColumns(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );

			}else
				aux2->setNext( aux1->applyInColumns(iter,step,none) );	//It just gets a copy of the previous version

			aux2 = aux2->getNext();
		}
	}

	temp->setLast(aux2);

return temp;}


CellPart* Rule::applyInLines( const natural iter, const int step, const operation oprtn) const noexcept{

	if( vigor == 1 )	//If there's no more vigor
		return this->F_ruled->applyInLines(iter,step,oprtn);

	Rule* temp;

	try{

		temp = new Rule(this->step,this->frequency,this->since,this->until,this->vigor == 0 ? 0 : this->vigor-1,this->pgt,this->aplo);

	}catch(bad_alloc){

		fail_report("CellPart* Rule::applyInColumns(natural,int,operation) const",ERROR_CODE::BAD_ALLOC);
	}

	const CellPart * aux1 = this->F_ruled;	//aux2 browses the new Rule, aux1 browses this Rule
	CellPart * aux2;

	if( aux1 != nullptr ){

		if( iter >= since && ( until == 0 || iter <= until ) ){	//Inside the vigor zone...

			if( this->aplo == apply_on::LINE )
				temp->F_ruled = ( aux2 = aux1->applyInLines(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );
			else
				temp->F_ruled = ( aux2 = aux1->applyInColumns(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );

		}else
			temp->F_ruled = ( aux2 = aux1->applyInLines(iter,step,none) );	//It just gets a copy of the previous version

		while( ( aux1 = aux1->getNext() ) != this->getNext() ){

				if( iter >= since && ( until == 0 || iter <= until ) ){	//Inside the vigor zone...

					if( this->aplo == apply_on::LINE )
						aux2->setNext( aux1->applyInLines(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );
					else
						aux2->setNext( aux1->applyInColumns(iter,this->pgt == GP ? pow(this->step,iter/frequency) : this->step*static_cast<natural>(iter/frequency),this->pgt == GP ? times : plus) );

				}else
					aux2->setNext( aux1->applyInLines(iter,step,none) );	//It just gets a copy of the previous version

			aux2 = aux2->getNext();
		}
	}

	temp->setLast(aux2);

return temp;}


void Rule::print( const bool keepMarkUp) const noexcept{

	if( keepMarkUp )
		cout << "-&#" << ( pgt == AP ? 'A' : 'G' ) << '#' << ( aplo == LINE ? 'L' : 'C' ) << '#' << step << '#' << frequency << '#' << since << '#' << until << '#' << vigor << '#';

	if( F_ruled != nullptr ){

		const CellPart* browser = F_ruled;

		do{

			browser->print(keepMarkUp);

		}while( ( browser = browser->getNext() ) != this->getNext() );
	}

	if( keepMarkUp )
		cout << "#&-";
}


Rule::~Rule() noexcept{

	if( F_ruled != nullptr ){

		const CellPart * clean, * browser = F_ruled;

		do{

			clean = browser;
			browser = browser->getNext();

			delete clean;

		}while( browser != this->getNext() );
	}
}
