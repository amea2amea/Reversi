/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_NegaScout_AI.h"
#include <algorithm> 

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_NegaScout_AI	:	const引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_NegaScout_AI::Reversi_NegaScout_AI()
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
void Reversi_NegaScout_AI::Move(Reversi_Board& reversi_board)
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
			reversi_board.Pass();
		}
		else if (vector_stone_info.size() == 1)													/*	石を裏返せる座標位置が1つしか存在しない			*/
		{
			/*------------------*/
			/* 移動				*/
			/*------------------*/
			reversi_board.Move(vector_stone_info[0]);
		}
	}
	else																						/*	石を裏返せる位置が複数存在する				*/
	{
		/*------------------*/
		/* ソート			*/
		/*------------------*/
		int					limit = 0;
		unsigned short		truns = reversi_board.GetTurns();									/*	手数											*/
		Sort(reversi_board, vector_stone_info, m_perfect_depth);

		if (reversi_board.MAX_TURNS - truns <= m_wld_depth)
		{
			limit = std::numeric_limits<int>::max();
		}
		else
		{
			limit = m_normal_depth;
		}

		/*------------------*/
		/*					*/
		/*------------------*/
		int eval = 0;
		int alpha = std::numeric_limits<int>::max();
		int beta = std::numeric_limits<int>::max();
		Stone_Info stone_info;
		for (unsigned short i = 0; i < vector_stone_info.size(); i++)
		{
			reversi_board.Move(vector_stone_info[i]);
			eval = -Alpahabeta(reversi_board, limit, alpha, beta);
			reversi_board.Undo();

			if (eval > alpha)
			{
				alpha = eval;
				stone_info = vector_stone_info[i];
			}

		}

		/*------------------*/
		/* 移動				*/
		/*------------------*/
		reversi_board.Move(stone_info);
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
int Reversi_NegaScout_AI::Evaluate(const Reversi_Board& reversi_board)
{
	return 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Sort				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
void Reversi_NegaScout_AI::Sort(Reversi_Board& reversi_board, std::vector< Stone_Info >& vector_stone_info, int limit)
{
	std::vector< Stone_Eval >		vector_stone_eval;

	/*------------------*/
	/*					*/
	/*------------------*/
	for (unsigned short i = 0; i < vector_stone_info.size(); i++)
	{
		int eval = 0;
		reversi_board.Move(vector_stone_info[i]);
		eval = -Alpahabeta(reversi_board, limit - 1, -INT_MAX, INT_MAX);
		reversi_board.Undo();

		Stone_Eval	stone_Eval(vector_stone_info[i].x, vector_stone_info[i].y, eval);
		vector_stone_eval.push_back(stone_Eval);
	}

	/*------------------*/
	/* マージーソート	*/
	/*------------------*/
	//	std::stable_sort(vector_stone_eval.begin(), vector_stone_eval.end(), NULL);

	/*----------------------*/
	/*	データの書き換え	*/
	/*----------------------*/
	vector_stone_info.clear();
	for (unsigned short i = 0; i < vector_stone_eval.size(); i++)
	{
		Stone_Info	stone_info(vector_stone_eval[i].x, vector_stone_eval[i].y, reversi_board.GetCurrentColor());
		vector_stone_info.push_back(stone_info);
	}

	return;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Alpahabeta			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_NegaScout_AI::Alpahabeta(Reversi_Board& reversi_board, int limit, int alpha, int beta)
{
	return 0;
}