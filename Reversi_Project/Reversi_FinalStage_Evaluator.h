#ifndef Reversi_FinalStage_Evaluator_h
#define Reversi_FinalStage_Evaluator_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Evaluator.h"

/*--------------------------------------*/
/*	終盤の場面における評価関数クラス	*/
/*--------------------------------------*/
class Reversi_FinalStage_Evaluator : public Reversi_Evaluator		/*	終盤の場面における評価関数クラス						*/
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_FinalStage_Evaluator();									/*	引数なしコンストラクタ									*/
	int Evaluate(const Reversi_Board&);

};

#endif