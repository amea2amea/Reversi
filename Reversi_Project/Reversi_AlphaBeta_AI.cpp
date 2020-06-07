/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_AlphaBeta_AI.h"

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_AlphaBeta_AI	:	const引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_AlphaBeta_AI::Reversi_AlphaBeta_AI()
{
	;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Move				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
void Reversi_AlphaBeta_AI::Move(Reversi_Board& reversi_board)
{
	std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();			/*	石を裏返せるボード位置							*/
	
	/****************************/
	/*	石を裏返せる位置の存在	*/
	/****************************/
	if (vector_stone_info.size() <= 1)															/*	石を裏返せる位置が複数存在しない				*/
	{
		if (vector_stone_info.size() == 0)														/*	石を裏返せる座標位置が存在しない				*/
		{
			/*------------------*/
			/* パス				*/
			/*------------------*/
			if (reversi_board.Pass() == true)
			{
				std::cerr << "  -> パスします" << std::endl;
			}
		}
		else if (vector_stone_info.size() == 1)													/*	石を裏返せる座標位置が1つしか存在しない			*/
		{
			/*------------------*/
			/* 移動				*/
			/*------------------*/
			if (reversi_board.Move(vector_stone_info[0]))
			{
				std::cerr << "  ->打ちました" << std::endl;
			}
		}
	}
	else																						/*	石を裏返せる位置が複数存在する				*/
	{
		/*------------------*/
		/*					*/
		/*------------------*/
		int				eval	= 0;
		int				alpha	= std::numeric_limits<int>::max();
		int				beta	= std::numeric_limits<int>::max();
		int				limit	= 0;
		unsigned short	truns	= reversi_board.GetTurns();										/*	手数										*/	
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
		/* 移動				*/
		/*------------------*/
		if (reversi_board.Move(stone_info))
		{
			std::cerr << "  ->打ちました" << std::endl;
		}
	}

	return;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Evaluate			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_AlphaBeta_AI::Evaluate(const Reversi_Board& reversi_board)
{
	return 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Alpahabeta			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_AlphaBeta_AI::Alpahabeta(Reversi_Board& reversi_board, int limit, int alpha, int beta)
{
	return 0;
}