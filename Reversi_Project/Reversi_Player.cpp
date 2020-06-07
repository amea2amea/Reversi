/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_MiniMax_AI.h"
#include "Reversi_Player.h"


/*----------------------------------*/
/*	 人間用のPlayerクラス			*/
/*----------------------------------*/

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_AI_Player			:	引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_AI_Player::Reversi_AI_Player() : m_reversi_AI( NULL )
{
	m_reversi_AI = new Reversi_MiniMax_AI();
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	~Reversi_AI_Player			:	引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_AI_Player::~Reversi_AI_Player() 
{
	delete m_reversi_AI;
	m_reversi_AI = 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		PlayerTurn			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_AI_Player::PlayerTurn(Reversi_Board& reversi_board)
{
	/************************/
	/*	入力				*/
	/************************/
	if (reversi_board.GetCurrentColor() == BLACK)
	{
		std::cout << "  手番 : 黒" << std::endl;
	}
	else if (reversi_board.GetCurrentColor() == WHITE)
	{
		std::cout << "  手番 : 白" << std::endl;
	}
	std::cout << "  コンピュータ思考中・・・・・・" << std::endl;
	m_reversi_AI->Move(reversi_board);
	std::cout << std::endl;

	return 0;
}

/*======================================================================================================*/

/*----------------------------------*/
/*	 人間用のPlayerクラス			*/
/*----------------------------------*/

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Reversi_Human_Player		:	引数なしコンストラクタ			*/
/*--------------------------------------------------------------------------*/
Reversi_Human_Player::Reversi_Human_Player()
{
	;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		PlayerTurn			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]						:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
int Reversi_Human_Player::PlayerTurn(Reversi_Board& reversi_board)
{
	std::string					stone_input;
	Stone_Info					stone_info;

	/************************/
	/*	入力				*/
	/************************/
	if (reversi_board.GetCurrentColor() == BLACK)
	{
		std::cout << "  手番 : 黒" << std::endl;
	}
	else if (reversi_board.GetCurrentColor() == WHITE)
	{
		std::cout << "  手番 : 白" << std::endl;
	}
	std::cout << "  =================================================== " << std::endl;
	std::cout << "  石を打つ => アルファベット数字 (例：e6) " << std::endl;
	std::cout << "  パス => p " << std::endl;
	std::cout << "  UNDO => u " << std::endl;
	std::cout << "  石を置ける位置 => h " << std::endl;
	std::cout << "  =================================================== " << std::endl;
	std::cout << "  手を入力してください : ";
	std::cin >> stone_input;
	std::cout << std::endl;

	/************************/
	/*	更新				*/
	/************************/
	if (stone_input == "p")
	{
		/*------------------*/
		/* パス				*/
		/*------------------*/
		if (reversi_board.Pass() == true)
		{
			std::cerr << "  -> パスします" << std::endl;
			std::cout << std::endl;
			return PASS;
		}
		else
		{
			std::cerr << "  -> パスできません" << std::endl;
			std::cout << std::endl;
		}
	}
	if (stone_input == "h")
	{
		/*----------------------*/
		/* 打てる位置を表示		*/
		/*----------------------*/
		return EnablePos;
	}
	else if (stone_input == "u")
	{
		/*------------------*/
		/* undo				*/
		/*------------------*/
		if (reversi_board.Undo() == true)
		{
			std::cerr << "  -> 戻します" << std::endl;
			std::cout << std::endl;
			return UNDO;
		}
		else
		{
			std::cerr << "  -> 戻せません" << std::endl;
			std::cout << std::endl;
		}
	}
	else if(((stone_input[0] >= 'a') && (stone_input[0] <= 'h'))
		&& ((stone_input[1] >= '1') && (stone_input[1] <= '8')))

	{
		try
		{
			/*------------------*/
			/* 石の位置を取得	*/
			/*------------------*/
			Stone_Point				store_point(stone_input);
			stone_info.x		=	store_point.x;
			stone_info.y		=	store_point.y;
			stone_info.color	=	reversi_board.GetCurrentColor();

		}
		catch (std::invalid_argument)
		{
			/*------------------*/
			/* エラー			*/
			/*------------------*/
			std::cerr << "  ->リバーシの手を打ってください" << std::endl;
			std::cout << std::endl;
			return INPUT_ERROR;
		}

		/*------------------*/
		/* 移動				*/
		/*------------------*/
		if (reversi_board.Move(stone_info))
		{
			std::cerr << "  ->打ちました" << std::endl;
			std::cout << std::endl;
			return MOVE;
		}
		else
		{
			std::cerr << "  ->そこには置けません" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{ 
		/*------------------*/
		/* エラー			*/
		/*------------------*/
		std::cerr << "  ->リバーシの手を打ってください" << std::endl;
		std::cout << std::endl;
		return INPUT_ERROR;
	
	}

	return INPUT_ERROR;
}