/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_MiniMax_AI.h"
#include "Reversi_FinalStage_Evaluator.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_MiniMax_AI	:	const引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_MiniMax_AI::Reversi_MiniMax_AI()
{
	m_reversi_evaluator = new Reversi_FinalStage_Evaluator();
	m_normal_depth = 5;
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	~Reversi_AI_Player			:	引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_MiniMax_AI::~Reversi_MiniMax_AI()
{
	delete m_reversi_evaluator;
	m_reversi_evaluator = 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Move				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
void Reversi_MiniMax_AI::Move(Reversi_Board& reversi_board)
{
	std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();			/*	石を裏返せるボード位置							*/
	int								limit = m_normal_depth;										/*	読み手の深さ									*/

	/****************************/
	/*	石を裏返せる位置の存在	*/
	/****************************/
	if (vector_stone_info.size() <= 1)															/*	石を裏返せる位置が複数存在しない				*/
	{
		/****************************/
		/*	先読みしない			*/
		/****************************/
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
	else																						/*	石を裏返せる位置が複数存在する					*/
	{
		/****************************/
		/*	先読みを行う			*/
		/****************************/
		MiniMax(reversi_board, limit);
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
int Reversi_MiniMax_AI::Evaluate(const Reversi_Board& reversi_board)
{
	short Evaluate = 0;
	Evaluate	= m_reversi_evaluator->Evaluate(reversi_board);
	return Evaluate;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MiniMax				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MiniMax(Reversi_Board& reversi_board, int limit)
{
	/*

		MiniMax法は、自分の手を最大評価値(自分にとって一番良い手)と
		相手の手を最小評価値(自分にとって一番危険な手)として
		探索することで動的の評価値を導き出す手法です。

		現在の選択できる全ての手を読み込むことで一番良い評価値を導き出す。
		( 1つずつの手において先読み数分読み込むことで最大値(最小値)を導く )

		●	MaxLevel	->	自分の手を読む
		●	MiniLevel	->	相手の手を読む	

	*/

	/****************************************/
	/*	先読みの手の設定					*/
	/*		事前に1番最初の手を設定しておく	*/
	/****************************************/
	const std::vector< Stone_Info >&	vector_stone_info = reversi_board.GetEnablePos();	/*	石を裏返せるボード位置							*/
	m_next_stone_info = vector_stone_info[0];

	/****************************/
	/*	先読み開始				*/
	/****************************/
	MaxLevel(reversi_board, limit);

	/****************************/
	/*	移動					*/
	/****************************/
	if (reversi_board.Move(m_next_stone_info))
	{
		std::cerr << "  ->打ちました" << std::endl;
	}

	return 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MiniLevel			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MiniLevel(Reversi_Board& reversi_board, int limit)
{
	/****************************/
	/*	先読み手数が完了済み	*/
	/****************************/
	if (	(limit == 0)																		/*	先読み手数分読み終えたら						*/
		||	(reversi_board.isGameOver()))														/*	ゲームが終了したら								*/
	{
//		std::cout << "  " << m_normal_depth - limit << "手先読み完了・・・・・" << std::endl;
		return Evaluate(reversi_board);															/*	評価値を返す									*/
	}

	/****************************/
	/*	先読み中 ( 探索中 )		*/
	/****************************/
	const std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();	/*	石を裏返せるボード位置							*/
	Stone_Info	stone_info;
	int			score = 0;																		/*	現在のスコア									*/
	int			score_mini = 0;															/*	最小スコア										*/

	for (unsigned int disc_count = 0; disc_count < vector_stone_info.size(); disc_count++)
	{
		stone_info = vector_stone_info.at(disc_count);											/*	石を打てる位置を取得							*/
		reversi_board.Move(stone_info);															/*	石を打つ										*/
		DebugCode(reversi_board, disc_count, limit - 1);
	
		score = MaxLevel(reversi_board, limit - 1);												/*	自分の手を読む									*/
		reversi_board.Undo();																	/*	手を戻す										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		if ( score < score_mini )
		{
			score_mini = score;																	/*	最小スコアの更新								*/
		}
	}

	return score_mini;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MaxLevel			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MaxLevel(Reversi_Board& reversi_board, int limit)
{
	/****************************/
	/*	先読み手数が完了済み	*/
	/****************************/
	if (	(limit == 0)																		/*	先読み手数分読み終えたら						*/
		||	(reversi_board.isGameOver()))														/*	ゲームが終了したら								*/
	{
//		std::cout << "  " << m_normal_depth - limit << "手先読み完了・・・・・" << std::endl;
		return Evaluate(reversi_board);															/*	評価値を返す									*/
	}

	/****************************/
	/*	先読み中 ( 探索中 )		*/
	/****************************/
	const std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();	/*	石を裏返せるボード位置							*/
	Stone_Info	stone_info;
	int			score		= 0;																/*	現在のスコア									*/
	int			score_max	= 0;																/*	最大スコア										*/

	for (unsigned int disc_count = 0; disc_count < vector_stone_info.size(); disc_count++)
	{
		stone_info = vector_stone_info.at(disc_count);											/*	石を打てる位置を取得							*/
		reversi_board.Move(stone_info);															/*	石を打つ										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		score = MiniLevel(reversi_board, limit - 1);											/*	相手の手を読む									*/
		reversi_board.Undo();																	/*	手を戻す										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		if ( score > score_max)
		{
			score_max = score;																	/*	最大スコアの更新								*/
			
			if (limit == m_normal_depth)														/*	現在の読み手ならば								*/
			{
				m_next_stone_info = stone_info;													/*	次の読み手を決定する							*/
			}
		}
	}

	return score_max;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DebugCode			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
void Reversi_MiniMax_AI::DebugCode(Reversi_Board& reversi_board, int disc_count, int limit)
{
#if 0
	std::cout << "  No." << disc_count + 1 << " - ";
	std::cout << m_normal_depth - limit << "手目の先読み中・・・・・・" << std::endl;
	std::cout << std::endl;
	reversi_board.ReversiConsolePrint();
	std::cout << std::endl;
#endif
	return;
}