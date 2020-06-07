/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Board.h"

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*--------------------------------------------------------------*/
/*																*/
/*	[関数]	Reversi_Board	:	const引数なしコンストラクタ		*/
/*--------------------------------------------------------------*/
Reversi_Board::Reversi_Board()
{
	m_Discs.SetSize( BOARD_SIZE_X + 2, BOARD_SIZE_Y + 2);
	m_ColorStarge.SetSize( COLOR_NUM, COLOR_START_POINT );
	Init();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Init				:	初期化									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::Init()
{
	Reversi_Point	reversi_point(EMPTY, REVERSED_NONE);
	Reversi_Point	reversi_wall( WALL,  REVERSED_NONE);
	Reversi_Point	reversi_white(WHITE, REVERSED_NONE);
	Reversi_Point	reversi_black(BLACK, REVERSED_NONE);

	/************************/
	/*	ボード位置の初期化	*/
	/************************/
	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{
			m_Discs(x, y) = reversi_point;											/*	ボード位置の情報を初期化						*/
		}
	}

	/************************/
	/*	壁の設定			*/
	/************************/
	for (int x = 0; x <= BOARD_SIZE_X + 1; x++)
	{
		m_Discs(x, 0) = reversi_wall;												/*	壁の設定 ( 1番上 )								*/
		m_Discs(x, BOARD_SIZE_Y + 1) = reversi_wall;								/*	壁の設定 ( 1番下 )								*/
	}

	for (int y = 0; y <= BOARD_SIZE_Y + 1; y++)
	{
		m_Discs(0, y) = reversi_wall;												/*	壁の設定 ( 左端 )								*/
		m_Discs(BOARD_SIZE_X + 1, y) = reversi_wall;								/*	壁の設定 ( 右端 )								*/

	}

	/************************/
	/*	初期配置の設定		*/
	/************************/
	m_Discs(Discs_START_POINT_X1, Discs_START_POINT_Y1) = reversi_white;			/*	石の初期配置 ( 中央対角位置　)					*/
	m_Discs(Discs_START_POINT_X2, Discs_START_POINT_Y2) = reversi_white;			/*	石の初期配置 ( 中央対角位置　)					*/
	m_Discs(Discs_START_POINT_X1, Discs_START_POINT_Y2) = reversi_black;			/*	石の初期配置 ( 中央対角位置　)					*/
	m_Discs(Discs_START_POINT_X2, Discs_START_POINT_Y1) = reversi_black;			/*	石の初期配置 ( 中央対角位置　)					*/

	/************************/
	/*	石の数を初期設定	*/
	/************************/
	m_ColorStarge[BLACK]	= 2;												/*	石の数を設定 ( 黒色 )							*/
	m_ColorStarge[WHITE]	= 2;												/*	石の数を設定 ( 白色 )							*/
	m_ColorStarge[EMPTY]	= BOARD_SIZE_X * BOARD_SIZE_Y - 4 ;					/*	石の数を設定 ( なし )							*/

	/****************************/
	/*	手数の初期化			*/
	/****************************/
	m_Turns = 0;																/*	手数											*/

	/****************************/
	/*	手番の設定				*/
	/****************************/
	m_CurrentColor = BLACK;														/*	現在の手番 ( 石の色 )							*/

	/****************************/
	/*	ボードの状態を初期化		*/
	/****************************/
	m_UpdateLog.clear();														/*	各手順の更新されるボードの状態を保存			*/

	/****************************/
	/*	石の置ける位置の取得	*/
	/****************************/
	InitMove();																	/*	石の位置情報を取得								*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		isGameOver			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	ゲーム終了( 0:しない	1:する )		*/
/*	[引数]							:	なし									*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::isGameOver()
{





	/****************************/
	/*	最大手数かどうかの確認	*/
	/****************************/
	unsigned short truns = GetTurns();												/*	手数											*/
	if (truns == MAX_TURNS - 4 )													/*	手数が最大手数になっている						*/
		return true;																/*	ゲーム終了する									*/

	/****************************/
	/*	石を裏返せる位置の存在	*/
	/****************************/
	std::vector< Stone_Info >&			vector_stone_info = GetEnablePos();			/*	石を打てるボード位置							*/
	if (vector_stone_info.size() != 0)												/*	石を裏返せる座標位置が存在する					*/
		return false;																/*	ゲーム終了しない								*/
	
	/*
		Note:
		自分の番において石を裏返せる位置の存在しないならば
		相手の番に石を位置を裏返せる事ができる確認
		もし、相手側においても石を裏返せる位置の存在しない場合、
		両者とも打てないので、ゲームを終了する
	*/
	
	/****************************/
	/*	ゲーム終了の判定		*/
	/****************************/
	short CurrentColor = GetCurrentColor();											/*	現在の手番の石の色								*/

	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		Stone_Info							disc_point;								/*	石の位置										*/
		disc_point.x = x;															/*	石の座標位置を更新								*/
		disc_point.color = -CurrentColor;											/*	相手番の石の色を設定							*/

		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{
			disc_point.y = y;														/*	石の座標位置を更新								*/

			if (CheckMobility(disc_point) != REVERSED_NONE) 						/*	石を打ちたい位置に石を裏返せる方向が存在する	*/
				return false;														/*	ゲーム終了しない								*/
		}
	}

	return true;

}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	Move				:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]		unsigned short	:	ボード位置情報								*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Move(const Stone_Info& stone_info )
{
	unsigned int		x		= stone_info.x;									/*	石を打ちたい位置(X)								*/
	unsigned int		y		= stone_info.y;									/*	石を打ちたい位置(Y)								*/
	unsigned short		truns	= GetTurns();									/*	手数											*/
	unsigned short		dir		= m_EnableDir[truns](x, y).GetDirection();		/*	石を打ちたい位置の石を裏返せる方向				*/

	/****************************/
	/*	エラー					*/
	/****************************/
	if (	((x < 0) || (x > BOARD_SIZE_X))										/*	打ちたい位置がボード外になるならばエラー(X)		*/
		||	((y < 0) || (y > BOARD_SIZE_Y))										/*	打ちたい位置がボード外になるならばエラー(Y)		*/
		||	( dir == REVERSED_NONE))											/*	打ちたい位置が石を裏返せない場所だったらエラー	*/
	{
		return false;
	}

	/****************************/
	/*	石を置く				*/
	/****************************/
	Reversi_Point reversi_point(GetCurrentColor(), REVERSED_NONE);
	m_Discs(x, y) = reversi_point;

	/****************************/
	/*	石を裏返す				*/
	/****************************/
	flipDiscss( stone_info );

	/****************************/
	/*	手数の更新				*/
	/****************************/
	m_Turns++;

	/****************************/
	/*	手番の交代				*/
	/****************************/
	ChangePlayer();

	/************************************/
	/*	次の手番で石の置ける位置の取得	*/
	/************************************/
	InitMove();
	
	return true;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	Pass				:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]		unsigned short	:	ボード位置情報								*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Pass()
{
	std::vector< Stone_Info >&	vector_stone_info = GetEnablePos();		/*	石を打てるボード位置							*/

	/****************************/
	/*	石を裏返せる位置の存在	*/
	/****************************/
	if (vector_stone_info.size() != 0)											/*	石を裏返せる座標位置が存在する					*/
		return false;															/*	パスしない										*/

	/****************************/
	/*	ゲーム終了				*/
	/****************************/
	if (isGameOver())															/*	ゲーム終了ならば								*/
		return false;															/*	パスしない										*/

	/****************************/
	/*	手番の交代				*/
	/****************************/
	ChangePlayer();

	/************************************/
	/*	各手順のボードの変更点を更新	*/
	/************************************/
	m_UpdateLog.push_back(std::vector<Stone_Info>());							/*	各手順の更新されるボード変更点を保存			*/

	/****************************/
	/*	石の置ける位置の取得	*/
	/****************************/
	InitMove();

	return true;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	Undo				:	指定された手数まで状態を戻す				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]		unsigned short	:	現在の手数から戻す手数						*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Undo()
{
	unsigned short						truns	= GetTurns();						/*	現在の手数										*/

	/****************************/
	/*	開始地点なら終わり		*/
	/****************************/
	if (truns == 0)																	/*	開始地点										*/
		return false;																/*	戻れない										*/

	const std::vector<Stone_Info>&		update = m_UpdateLog.back();				/*	1つ前のボードの変更点 ( 最後の要素 )			*/

	/****************************/
	/*	手番を戻す				*/
	/****************************/
	ChangePlayer();

	/********************************/
	/*	石を裏返せる座標位置の削除	*/
	/********************************/
	m_EnablePos[truns].clear();														/*	1つ前の石を裏返せる座標位置を削除				*/

	/****************************/
	/*	手数の更新				*/
	/****************************/
	m_Turns--;


	if (update.empty())																/*	パスしていたら									*/
	{
		/****************************/
		/*	石を裏返せる方向の削除	*/
		/****************************/
		for (int x = 1; x <= BOARD_SIZE_X; x++)
		{
			for (int y = 1; y <= BOARD_SIZE_Y; y++)
			{
				m_EnableDir[truns](x, y).SetDirection() = REVERSED_NONE;			/*	石を裏返せる方向								*/
			}
		}
	}
	else																			/*	パスしていない									*/
	{
		/****************************/
		/*	置いた石を戻す			*/
		/****************************/
		Reversi_Point	reversi_point1(EMPTY, REVERSED_NONE);						/*	ボード位置の初期状態を設定						*/
		Stone_Info		stone_info			= update.at( 0 );						/*	1つ前の石を打った位置を取得						*/
		m_Discs(stone_info.x, stone_info.y)	= reversi_point1;						/*	ボード位置の状態を初期化						*/

		/****************************/
		/*	裏返した石を戻す		*/
		/****************************/
		for (unsigned int i = 1; i < update.size(); i++)
		{
			stone_info = update.at( i );											/*	石を裏返した情報を取得							*/
			Reversi_Point	reversi_point2( -stone_info.color, REVERSED_NONE);		/*	石を裏返した情報を設定							*/
			m_Discs(stone_info.x, stone_info.y) = reversi_point2;					/*	ボード位置の状態を戻す							*/
		}

		/****************************/
		/*	石の数を更新			*/
		/****************************/
		m_ColorStarge[stone_info.color]		-= static_cast<int>(update.size());			/*	石を置いた位置と裏返した数だけ石の色を減らす	*/
		m_ColorStarge[-stone_info.color]	+= static_cast<int>(update.size() - 1);		/*	石を裏返された数だけ石の色を増やす				*/
																						/*　( 配列の指定ではないため、マイナスでも問題ない)	*/
		m_ColorStarge[EMPTY]++;															/*	石を戻したので石のない位置を１つだけ増やす		*/
	}

	/************************************/
	/*	各手順のボードの変更点を更新	*/
	/************************************/
	m_UpdateLog.pop_back();															/*	石を戻したので記録した変更点を削除(末尾を削除)	*/

	return true;
}
/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]		GetTurns				:	手数を取得					*/
/*	------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short			:	手数						*/
/*	[引数]									なし						*/
/*----------------------------------------------------------------------*/
unsigned short Reversi_Board::GetTurns() const
{
	return m_Turns;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		CheckEnablePos			:	指定した位置が石を打てる位置か取得する		*/
/*	----------------------------------------------------------------------------------	*/
/*	[戻り値]	bool					:	石を打てる位置かどうか						*/
/*												true	->	石を打てる					*/
/*												false	->	石を打てない				*/
/*	[引数]		Stone_Point				:	石の位置									*/
/*--------------------------------------------------------------------------------------*/
bool Reversi_Board::CheckEnablePos( Stone_Point stone_point )
{
	Stone_Info								stone_info;									/*	ボード位置										*/
	std::vector< Stone_Info >&				vector_stone_info = GetEnablePos();			/*	石を打てるボード位置							*/

	for (unsigned int i = 0; i < vector_stone_info.size(); i++)
	{
		stone_info = vector_stone_info.at(i);											/*	石を打てる位置を取得							*/

		if (	(stone_point.x == stone_info.x)											/*	石を打てる位置と指定した位置が同じ ( X座標 )	*/
			&&	(stone_point.y == stone_info.y))										/*	石を打てる位置と指定した位置が同じ ( Y座標 )	*/
		{
			return true;																/*	石を打てる位置									*/
		}
	}

	return false;																		/*	石を打てない位置								*/
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetEnablePos				:	現在の手番の石を打てる位置		*/
/*	-------------------------------------------------------------------------	*/
/*	[戻り値]	std::vector< Stone_Info >&	:	現在の手番の石を打てる位置		*/
/*	[引数]										なし							*/
/*------------------------------------------------------------------------------*/
std::vector< Stone_Info >& Reversi_Board::GetEnablePos() 
{
	unsigned short		truns = GetTurns();							/* 手数 */
	return m_EnablePos[truns];
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]		GetCurrentColor			:	現在の手番の石の色を取得	*/
/*	------------------------------------------------------------------	*/
/*	[戻り値]	short					:	手数						*/
/*	[引数]									なし						*/
/*----------------------------------------------------------------------*/
short Reversi_Board::GetCurrentColor() const
{
	return m_CurrentColor;
}

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]		GetColor				:	指定した石の位置の状態を取得	*/
/*	---------------------------------------------------------------------	*/
/*	[戻り値]	short 					:	石の状態						*/
/*	[引数]		Stone_Point				:	石の位置						*/
/*--------------------------------------------------------------------------*/
short Reversi_Board::GetColor(Stone_Point stone_point) const
{
	return m_Discs(stone_point.x, stone_point.y).GetColor();
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]		ChangePlayer			:	手番の交代					*/
/*	------------------------------------------------------------------	*/
/*	[戻り値]								なし						*/
/*	[引数]									なし						*/
/*----------------------------------------------------------------------*/
void Reversi_Board::ChangePlayer()
{
	m_CurrentColor = -m_CurrentColor;
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]		GetDiscColor			:	指定した石の位置の状態を取得	*/
/*	---------------------------------------------------------------------	*/
/*	[戻り値]	short					:	手数							*/
/*	[引数]									なし							*/
/*--------------------------------------------------------------------------*/
short Reversi_Board::GetDiscColor(Stone_State stone_state) const
{
	return m_ColorStarge[stone_state];
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	flipDiscs			:	石を打つ									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]		unsigned short	:	ボード位置情報								*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::flipDiscss( const Stone_Info& stone_info)
{
	unsigned int				x = stone_info.x;												/*	石を打つ位置(X)									*/
	unsigned int				y = stone_info.y;												/*	石を打つ位置(Y)									*/
	short						CurrentColor = stone_info.color;								/*	現在の手番の石の色								*/
	std::vector<Stone_Info>		update;															/*	石の状態を記録する								*/

	/****************************/
	/*	置いた石を保存			*/
	/****************************/
	Stone_Info  Discs(x, y, CurrentColor);														/*	石を打つ位置									*/
	update.push_back(Discs);																	/*	石の変更点を保存 ( 石を打った位置を保存	)		*/

	/****************************************************************/
	/*	石を裏返す													*/				
	/*		-> 石の反転 (上、右下、右、右下、下、左下、左、左上)	*/
	/****************************************************************/
	for (int i = 0x01; i < REVERSED_UPPER_LEFT; i = i << 1)
	{
		flipDirections( stone_info, update, i );												/*	石を裏返す										*/
	}

	/************************************/
	/*	石の情報を更新					*/
	/*		-> 石の数(白、黒、空の数)	*/
	/*		-> 石の裏返した情報を保存	*/
	/************************************/
	m_ColorStarge[CurrentColor] += static_cast<int>(update.size());								/*	石を裏返した数だけ石の色を増やす				*/
	m_ColorStarge[-CurrentColor] -= static_cast<int>((update.size() - 1));						/*	石を裏返された数だけ石の色を減らす				*/
																								/*　( 配列の指定ではないため、マイナスでも問題ない)	*/
	m_ColorStarge[EMPTY]--;																		/*	石を打ったので石のない位置を１つだけ減らす		*/
	m_UpdateLog.push_back(update);																/*	各手順の更新されるボードの状態を保存			*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	flipDirections			:	指定したボード方向に対して				*/
/*										石を反転させる							*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	石を裏返せるかの情報					*/
/*											0		: 石を裏返せない			*/
/*											1		: 石を裏返せる				*/
/*	[引数]		unsigned short		:	ボード位置情報							*/
/*				unsigned short		:	ボード方向								*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::flipDirections(const Stone_Info& stone_info, std::vector< Stone_Info >& update, unsigned short board_state )
{
	unsigned int				x				= stone_info.x;									/*	石を打つ位置(X)									*/
	unsigned int				y				= stone_info.y;									/*	石を打つ位置(Y)									*/
	short						CurrentColor	= stone_info.color;								/*	現在の手番の石の色								*/
	unsigned short				truns			= GetTurns();									/*	手数											*/
	unsigned short				dir				= m_EnableDir[truns](x, y).SetDirection();		/*	石を裏返せる方向								*/
	unsigned short				serch_dir		= 0;											/*	検索方向										*/

	/*
		Note:
		各状態(上下左右)において石を反転させる
		なお、スクリーン座標のため、上はマイナス方向、下はプラス方向、左はマイナス方向、右はプラス方向
	*/

	switch (dir & board_state)
	{
	case REVERSED_UPPER:														/*	上方向の石を裏返せる							*/
		y = y - 1;
		serch_dir = SEARCH_UPPER;
		break;

	case REVERSED_UPPER_RIGHT:													/*	右上方向の石を裏返せる							*/
		x = x + 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_RIGHT;
		break;

	case REVERSED_RIGHT:														/*	右方向の石を裏返せる							*/
		x = x + 1;
		serch_dir = SEARCH_RIGHT;
		break;

	case REVERSED_LOWER_RIGHT:													/*	右下方向の石を裏返せる							*/
		x = x + 1;
		y = y + 1;
		serch_dir = SEARCH_RIGHT | SEARCH_LOWER;
		break;

	case REVERSED_LOWER:														/*	下方向の石を裏返せる							*/
		y = y + 1;
		serch_dir = SEARCH_LOWER;
		break;

	case REVERSED_LOWER_LEFT:													/*	左下方向の石を裏返せる							*/
		x = x - 1;
		y = y + 1;
		serch_dir = SEARCH_LOWER | SEARCH_LEFT;
		break;

	case REVERSED_LEFT:															/*	左方向の石を裏返せる							*/
		x = x - 1;
		serch_dir = SEARCH_LEFT;
		break;

	case REVERSED_UPPER_LEFT:													/*	左上方向の石を裏返せる							*/
		x = x - 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_LEFT;
		break;

	case REVERSED_NONE:															/*	石を打てない									*/
	default:																	/*	それ以外										*/
		return ;

	}

	while (m_Discs(x, y).GetColor() == -CurrentColor)							/*	各状態の石の色が同じになるまで探す				*/
	{
		m_Discs(x, y).SetColor() = CurrentColor;								/*	石を反転させる									*/
		Stone_Info	Discs2(x, y, CurrentColor);									/*	石を反転させた位置								*/
		update.push_back( Discs2 );												/*	石の変更点を保存 ( 石を裏返した位置を保存	)	*/

		if (serch_dir & SEARCH_UPPER)
			y--;
		if (serch_dir & SEARCH_RIGHT)
			x++;
		if (serch_dir & SEARCH_LOWER)
			y++;
		if (serch_dir & SEARCH_LEFT)
			x--;
	}

	return ;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	InitMovable			:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]							なし										*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::InitMove()
{
	Stone_Info			disc_info;												/*	石の位置										*/
	short				CurrentColor	= GetCurrentColor();					/*	現在の手番の石の色								*/
	unsigned short		dir				= REVERSED_NONE;						/*	石を裏返せる方向								*/
	unsigned short		truns			= GetTurns();							/*	手数											*/

	m_EnableDir[truns].SetSize(BOARD_SIZE_X + 2, BOARD_SIZE_Y + 2);

	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		disc_info.color = CurrentColor;
		disc_info.x = x;														/*	石の座標位置を更新								*/

		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{	
			disc_info.y = y;													/*	石の座標位置を更新								*/

			dir = CheckMobility( disc_info );									/*	石の位置に対して石を裏返せる方向を取得			*/

			if (dir != REVERSED_NONE)											/*	石を打ちたい位置に石を裏返せる方向があるならば	*/
			{
				m_EnablePos[truns].push_back( disc_info );						/*	石を裏返せる座標位置を保存						*/
			}
			m_EnableDir[truns](x, y).SetDirection() = dir;						/*	石を打ちたい位置の石を裏返せる方向				*/
		}
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	CheckMobility		:	指定したボード位置に対して					*/
/*									石を打てるかどうか判定する					*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void			:	なし										*/
/*	[引数]		unsigned short	:	ボード位置情報								*/
/*------------------------------------------------------------------------------*/
unsigned short Reversi_Board::CheckMobility( const Stone_Info& stone_info ) const
{
	unsigned short  dir = REVERSED_NONE;										/*	石を返せる方向									*/
	unsigned int	x = stone_info.x; ;											/*	石を打ちたい位置(X)								*/
	unsigned int	y = stone_info.y;											/*	石を打ちたい位置(Y)								*/


	if (m_Discs(x, y).GetColor() != EMPTY)										/*	指定したボード上に石がある場合、石を打てない	*/
		return dir;

	/* 
		Note:
		相手の石を反転できる位置にしか打てないため
		石を打ちたい位置からボード上の各状態を確認する
		(上、右下、右、右下、下、左下、左、左上の状態を確認)
	*/

	for (int i = 0x01; i < REVERSED_UPPER_LEFT; i = i << 1)
		dir |= CheckDirections( stone_info, i );								/*	石を裏返せる場合はフラグが設定される			*/
	
	return dir;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]	CheckDirectionsr		:	指定したボード方向に対して				*/
/*										石を打てるかどうか判定する				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	石を裏返せるかの情報					*/
/*											0		: 石を裏返せない			*/
/*											1以上	: 石を裏返せる(裏返せる方向)*/
/*	[引数]		unsigned short		:	ボード位置情報							*/
/*				unsigned short		:	ボード方向								*/
/*------------------------------------------------------------------------------*/
unsigned short Reversi_Board::CheckDirections( const Stone_Info& stone_info, unsigned short board_state ) const
{	
	unsigned int	x				= stone_info.x; ;							/*	石を打ちたい位置(X)								*/
	unsigned int	y				= stone_info.y;								/*	石を打ちたい位置(Y)								*/
	short			CurrentColor	= stone_info.color;							/*	現在の手番の石の色								*/
	unsigned short  dir				= REVERSED_NONE;							/*	石を返せる方向									*/
	unsigned short  serch_dir		= 0;										/*	検索方向										*/

	/*
		Note:
		各状態(上下左右)において１つ先の箇所に自分の色と反対の色の石があるかどうか確認する
		自分の置いた位置に対して1つ先の石が反対の色でない方向は石を反転できない。
		全ての方向で石を反転できないなら石を置くことができない。
		なお、スクリーン座標のため、上はマイナス方向、下はプラス方向、左はマイナス方向、右はプラス方向
	*/

	switch (board_state)
	{
	case REVERSED_UPPER:														/*	上方向の石を裏返せる							*/
		y = y - 1;
		serch_dir = SEARCH_UPPER;
		break;

	case REVERSED_UPPER_RIGHT:													/*	右上方向の石を裏返せる							*/
		x = x + 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_RIGHT;
		break;

	case REVERSED_RIGHT:														/*	右方向の石を裏返せる							*/
		x = x + 1;
		serch_dir = SEARCH_RIGHT;
		break;

	case REVERSED_LOWER_RIGHT:													/*	右下方向の石を裏返せる							*/
		x = x + 1;
		y = y + 1;
		serch_dir = SEARCH_RIGHT | SEARCH_LOWER;
		break;

	case REVERSED_LOWER:														/*	下方向の石を裏返せる							*/
		y = y + 1;
		serch_dir = SEARCH_LOWER;
		break;

	case REVERSED_LOWER_LEFT:													/*	左下方向の石を裏返せる							*/
		x = x - 1;
		y = y + 1;
		serch_dir = SEARCH_LOWER | SEARCH_LEFT;
		break;

	case REVERSED_LEFT:															/*	左方向の石を裏返せる							*/
		x = x - 1;
		serch_dir = SEARCH_LEFT;
		break;

	case REVERSED_UPPER_LEFT:													/*	左上方向の石を裏返せる							*/
		x = x - 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_LEFT;
		break;

	case REVERSED_NONE:															/*	石を打てない									*/
	default:																	/*	それ以外										*/
		return dir;

	}

	if ( m_Discs(x, y).GetColor() == -CurrentColor )							/*	1つ先の方向の石が反対の色なら					*/
	{
		while ( m_Discs(x, y).GetColor() == -CurrentColor )						/*	上方向の石の色が変わるまで探す					*/
		{																		/*	壁やボードに石がない場合もあり					*/
			if(serch_dir & SEARCH_UPPER)
				y--;
			if (serch_dir & SEARCH_RIGHT)
				x++;
			if (serch_dir & SEARCH_LOWER)
				y++;
			if (serch_dir & SEARCH_LEFT)
				x--;
		}

		if ( m_Discs(x, y).GetColor() == CurrentColor )							/*	石の色が変化した位置が同じ石の色であるならば	*/
			dir = board_state;													/*	石を裏返せる方向を設定							*/
	}

	return dir;
}