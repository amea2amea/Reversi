/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_FinalStage_Evaluator.h"

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	Reversi_FinalStage_Evaluator	:	�����Ȃ��R���X�g���N�^		*/
/*--------------------------------------------------------------------------*/
Reversi_FinalStage_Evaluator::Reversi_FinalStage_Evaluator()
{
	;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Evaluate			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_FinalStage_Evaluator::Evaluate(const Reversi_Board& reversi_board)
{
	int score = 0;
	
	score	=	reversi_board.GetCurrentColor() *
					(reversi_board.GetDiscColor(BLACK) - reversi_board.GetDiscColor(WHITE));

	return score;
}