#ifndef Reversi_ScoreTable_Evaluator_h
#define Reversi_ScoreTable_Evaluator_h


/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Evaluator.h"

/*--------------------------------------*/
/*	得点テーブルにおける評価関数クラス	*/
/*--------------------------------------*/
class Reversi_ScoreTable_Evaluator : public Reversi_Evaluator		/*	得点テーブルにおける評価関数クラス						*/
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_ScoreTable_Evaluator();									/*	引数なしコンストラクタ									*/
	int Evaluate(const Reversi_Board&);

};

#endif
