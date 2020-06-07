/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_AlphaBeta_AI.h"

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	Reversi_AlphaBeta_AI	:	const�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_AlphaBeta_AI::Reversi_AlphaBeta_AI()
{
	;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Move				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
void Reversi_AlphaBeta_AI::Move(Reversi_Board& reversi_board)
{
	std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();			/*	�΂𗠕Ԃ���{�[�h�ʒu							*/
	
	/****************************/
	/*	�΂𗠕Ԃ���ʒu�̑���	*/
	/****************************/
	if (vector_stone_info.size() <= 1)															/*	�΂𗠕Ԃ���ʒu���������݂��Ȃ�				*/
	{
		if (vector_stone_info.size() == 0)														/*	�΂𗠕Ԃ�����W�ʒu�����݂��Ȃ�				*/
		{
			/*------------------*/
			/* �p�X				*/
			/*------------------*/
			if (reversi_board.Pass() == true)
			{
				std::cerr << "  -> �p�X���܂�" << std::endl;
			}
		}
		else if (vector_stone_info.size() == 1)													/*	�΂𗠕Ԃ�����W�ʒu��1�������݂��Ȃ�			*/
		{
			/*------------------*/
			/* �ړ�				*/
			/*------------------*/
			if (reversi_board.Move(vector_stone_info[0]))
			{
				std::cerr << "  ->�ł��܂���" << std::endl;
			}
		}
	}
	else																						/*	�΂𗠕Ԃ���ʒu���������݂���				*/
	{
		/*------------------*/
		/*					*/
		/*------------------*/
		int				eval	= 0;
		int				alpha	= std::numeric_limits<int>::max();
		int				beta	= std::numeric_limits<int>::max();
		int				limit	= 0;
		unsigned short	truns	= reversi_board.GetTurns();										/*	�萔										*/	
		Stone_Info stone_info;
		for (unsigned short i = 0; i < vector_stone_info.size(); i++)
		{
			reversi_board.Move(vector_stone_info[i]);
			eval = -Alpahabeta(reversi_board, limit, alpha, beta);
			reversi_board.Undo();

			if (eval > alpha)
			{
				alpha		= eval;
				stone_info	= vector_stone_info[i];
			}
		
		}

		/*------------------*/
		/* �ړ�				*/
		/*------------------*/
		if (reversi_board.Move(stone_info))
		{
			std::cerr << "  ->�ł��܂���" << std::endl;
		}
	}

	return;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Evaluate			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_AlphaBeta_AI::Evaluate(const Reversi_Board& reversi_board)
{
	return 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Alpahabeta			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_AlphaBeta_AI::Alpahabeta(Reversi_Board& reversi_board, int limit, int alpha, int beta)
{
	return 0;
}