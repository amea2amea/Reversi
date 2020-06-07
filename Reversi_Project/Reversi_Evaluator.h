#ifndef Reversi_Evaluator_h
#define Reversi_Evaluator_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Board.h"

/*----------------------------------*/
/*	評価関数クラス ( 抽象クラス )	*/
/*----------------------------------*/
class Reversi_Evaluator												/*	評価関数クラス											*/
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_Evaluator() {} 											/*	引数なしコンストラクタ									*/
	virtual int Evaluate(const Reversi_Board&) = 0;

};

#endif
