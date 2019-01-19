#ifndef COORDENATE_H_
#define COORDENATE_H_

#include"Package_Table.h"

struct char6{

	const char value[6];

	inline constexpr char6( const char c1, const char c2, const char c3, const char c4, const char c5, const char c6) noexcept : value{c1,c2,c3,c4,c5,c6} {}
	inline ~char6() = default;

	inline constexpr char operator[]( const natural i) const noexcept{ return i == 6 ? '\0' : value[i];}
};

class Coordenate : public CellPart{

/*
*	32 bytes coordenate.
*/

private: /* Attributes */

	const natural column;
	const natural line;

	const bool column_is_const;
	const bool line_is_const;

	const char6 pre_str;

public: /* Methods */

	inline constexpr Coordenate( const natural c, const bool constC, const natural l, const bool constL, const char6 preStr) noexcept : CellPart(), column{c}, line{l}, column_is_const{constC}, line_is_const{constL}, pre_str{preStr} {}
	inline constexpr Coordenate( const natural c, const bool constC, const natural l, const bool constL) noexcept : Coordenate(c,constC,l,constL,char6('\0','\0','\0','\0','\0','\0')) {}
	virtual inline ~Coordenate() override = default;

	virtual inline CellPart* applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept override;
	virtual inline CellPart* applyInLines( const natural iter, const int step, const operation oprtn) const noexcept override;

	virtual void print( const bool keepMarkUp) const noexcept override;
};

//################################
//########### Inlineds ###########
//################################

CellPart* Coordenate::applyInColumns( const natural iter, const int step, const operation oprtn) const noexcept try{

	return new Coordenate(column_is_const ? column : oprtn(column,step),column_is_const,line,line_is_const,pre_str);

}catch(...){

	fail_report("Coordenate::applyInColumns(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);
}


CellPart* Coordenate::applyInLines( const natural iter, const int step, const operation oprtn) const noexcept try{

	return new Coordenate(column,column_is_const,line_is_const ? line : oprtn(line,step),line_is_const,pre_str);

}catch(...){

	fail_report("Coordenate::applyInLines(natural,natural,operation)",ERROR_CODE::BAD_ALLOC);
}

#endif /* COORDENATE_H_ */
