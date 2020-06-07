#ifndef Reversi_h
#define Reversi_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include <vector>
#include <sstream>
#include <iostream>

/*--------------*/
/*	列挙体		*/
/*--------------*/
		
enum Reversi_State																				/*	リバーシの状態								*/
{
	PASS,																						/*	パス										*/
	INPUT_ERROR,																				/*	エラー										*/
	UNDO,																						/*	UNDO										*/
	EXIT,																						/*	終了										*/
	MOVE,																						/*	ボードに打つ								*/
	EnablePos																					/*	打てる位置を表示							*/
};

enum Stone_State																				/*	ボード位置の状態							*/
{
	BLACK = 1,																					/*	黒											*/
	EMPTY = 0,																					/*	なし										*/
	WHITE = -1,																					/*	白											*/
	WALL = 2																					/*	壁											*/
};

enum Reversed_Direction																			/*	ボード位置から裏返せる方向					*/
{
	REVERSED_NONE			= 0x00,																/*	石を打てない								*/
	REVERSED_UPPER			= 0x01,																/*	上方向の石を裏返せる						*/
	REVERSED_UPPER_RIGHT	= 0x02,																/*	右上方向の石を裏返せる						*/
	REVERSED_RIGHT			= 0x04,																/*	右方向の石を裏返せる						*/
	REVERSED_LOWER_RIGHT	= 0x08,																/*	右下方向の石を裏返せる						*/
	REVERSED_LOWER			= 0x10,																/*	下方向の石を裏返せる						*/
	REVERSED_LOWER_LEFT		= 0x20,																/*	左下方向の石を裏返せる						*/
	REVERSED_LEFT			= 0x40,																/*	左方向の石を裏返せる						*/
	REVERSED_UPPER_LEFT		= 0x80																/*	左上方向の石を裏返せる						*/
};


enum Search_Direction																			/*	ボードの検索方向							*/
{
	SEARCH_UPPER	= 0x01,																		/*	上方向										*/
	SEARCH_RIGHT	= 0x02,																		/*	右方向										*/
	SEARCH_LOWER	= 0x04,																		/*	下方向										*/
	SEARCH_LEFT		= 0x08,																		/*	左方向										*/
};

/*--------------*/
/*	構造体		*/
/*--------------*/
																								/*	ボート位置の構造体							*/
struct Stone_Point
{
	/*----------------------*/
	/*	座標位置			*/
	/*----------------------*/
	unsigned int x;																				/*	座標位置 ( 横 )								*/
	unsigned int y;																				/*	座標位置 ( 縦 )								*/

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Stone_Point()																				/*	引数なしコンストラクタ						*/
	{
		Stone_Point(0, 0);
	}
																							
	Stone_Point(int x, int y)																	/*	引数ありコンストラクタ						*/
	{
		this->x = x;
		this->y = y;
	}

	Stone_Point(std::string coordstr)
	{
		if ((coordstr.length() > 2)
			|| 
			(!(((coordstr[0] >= 'a') && (coordstr[0] <= 'h'))
			&& ((coordstr[1] >= '1') && (coordstr[1] <= '8')))))
		{
			return;
		}
		
		x = coordstr[0] - 'a' + 1;																/*	アルファベット入力をアスキー変換 ( 横方向 )	*/
		y = coordstr[1] - '1' + 1;																/*	数字入力をアスキーを変換		 ( 縦方向 )	*/
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		演算子オーバーロード	*/
	/*------------------------------*/

	const Stone_Point& operator()(int x, int y) const											/*	位置を指定したときの操作　( 代入用 )		*/
	{
		return Stone_Point(x, y);
	}

	Stone_Point& operator()(int x, int y)														/*	位置を指定したときの操作　( 操作用 )		*/
	{
		return Stone_Point(x, y);
	}

	operator std::string() const																/*	文字が設定されたときの操作					*/
	{
		std::ostringstream oss;
		oss << static_cast<char>('a' + x - 1)													/*	アルファベットのアスキーに変換 ( 横方向 )	*/
			<< static_cast<char>('1' + y - 1);													/*	数字のアスキーに変換		   ( 縦方向 )	*/

		return oss.str();
	}

};

																								/*	ボート位置の構造体							*/
struct Stone_Info	:	public Stone_Point
{
	short color;

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Stone_Info()	:	Stone_Point(0, 0)														/*	引数なしコンストラクタ						*/
	{
		color = EMPTY;
	}
																					
	Stone_Info( int x, int y, int color ) : Stone_Point(x, y)									/*	引数ありコンストラクタ						*/
	{
		this->color = color;
	}


	/*------------------------------*/
	/*	opeart						*/
	/*		演算子オーバーロード	*/
	/*------------------------------*/

	const Stone_Info& operator()(int x, int y, int color) const									/*	位置を指定したときの操作　( 代入用 )		*/
	{
		return Stone_Info(x, y, color);
	}

	Stone_Point& operator()(int x, int y, int color)											/*	位置を指定したときの操作　( 操作用 )		*/
	{
		return Stone_Info(x, y, color);
	}

};

struct Stone_Eval : public Stone_Point
{
	int eval;

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Stone_Eval() : Stone_Point(0, 0)															/*	引数なしコンストラクタ						*/
	{
		eval = 0;
	}

	Stone_Eval(int x, int y, int eval) : Stone_Point(x, y)										/*	引数ありコンストラクタ						*/
	{
		this->eval = eval;
	}
};
#endif
