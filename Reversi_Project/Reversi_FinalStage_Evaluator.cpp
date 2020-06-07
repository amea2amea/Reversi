/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_FinalStage_Evaluator.h"

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_FinalStage_Evaluator	:	引数なしコンストラクタ		*/
/*--------------------------------------------------------------------------*/
Reversi_FinalStage_Evaluator::Reversi_FinalStage_Evaluator()
{
	;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Evaluate			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_FinalStage_Evaluator::Evaluate(const Reversi_Board& reversi_board)
{
	int score = 0;
	
	score	=	reversi_board.GetCurrentColor() *
					(reversi_board.GetDiscColor(BLACK) - reversi_board.GetDiscColor(WHITE));

	return score;
}