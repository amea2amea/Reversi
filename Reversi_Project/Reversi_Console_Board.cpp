/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* 名前空間			*/
/*------------------*/
using namespace std;

/*------------------*/
/* メンバ関数		*/
/*------------------*/

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		ReversiConsolePrint		:	コンソール上の描画					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]							:	なし								*/
/*	[引数]								:	なし								*/
/*------------------------------------------------------------------------------*/
void Reversi_Console_Board::ReversiConsolePrint( int status)
{
	cout << "    a b c d e f g h " << endl;											/*	アルファベットの表示 ( 横方向 )				*/

	for (int y = 1; y <= BOARD_SIZE_Y; y++)
	{
		cout << "  " <<  y << " ";													/*	数字の表示           ( 縦方向 )				*/

		for (int x = 1; x <= BOARD_SIZE_X; x++)
		{
			switch (GetColor(Stone_Point(x, y)))
			{
			case	BLACK:															/*	黒											*/
				cout <<  "○" ;														/*	黒丸を描画									*/
				break;

			case	WHITE:															/*	白											*/
				cout <<  "●" ;														/*	白丸を描画									*/
				break;

			case	WALL:															/*	壁											*/
				break;

			case	EMPTY:															/*	なし										*/														
				if (status == EnablePos )											/*	打てる位置を表示							*/
				{
					if (CheckEnablePos(Stone_Point(x, y)))
					{
						cout << "＊";
					}
					else
					{
						cout << "  ";
					}
				}
				else
				{
					cout << "  ";
				}
				break;

			default:
				cout <<  "  ";
				break;
			}

		}
		cout  << endl;																/*	改行										*/
	}

	return;
}
