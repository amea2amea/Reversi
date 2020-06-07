/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Player.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* 名前空間			*/
/*------------------*/
using namespace std;

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		main					:	リバーシのメイン処理				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]							:	なし								*/
/*	[引数]								:	なし								*/
/*------------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	Reversi_Player*						player[2];
	Reversi_Console_Board				reversi_console_board;
	int									status = 0;
	int									i = 0;
	short								current_player	= 0;
	bool								bInitiative = false;

	/*------------------*/
	/* コマンドライン	*/
	/*------------------*/
	if (argc > 1)
	{
		if(strcmp(argv[1], "-r") == 0) 
			bInitiative = true;
	}

	/*------------------*/
	/* 先手・後手		*/
	/*------------------*/
	if (bInitiative)
	{
		player[0] = new Reversi_AI_Player();
		player[1] = new Reversi_Human_Player();
	}
	else
	{
		player[0] = new Reversi_Human_Player();
		player[1] = new Reversi_AI_Player();
	}

	/*------------------*/
	/* ゲーム開始		*/
	/*------------------*/
	cout << "----------------------------ゲーム開始----------------------------" << endl;
	cout << endl;

	while (1)
	{
		/************************/
		/*	コンソール描画		*/
		/************************/
		cout << " ( " << reversi_console_board.GetTurns() + 1 << " ) " << endl;
		reversi_console_board.ReversiConsolePrint(status);											/*	コンソール上の描画							*/
		cout << endl;

		cout << "  --------- " << endl;
		cout << "  黒石   : " << reversi_console_board.GetDiscColor(BLACK) << endl;					/*	黒石の数									*/
		cout << "  白石   : " << reversi_console_board.GetDiscColor(WHITE) << endl;					/*	白石の数									*/
		cout << "  空マス : " << reversi_console_board.GetDiscColor(EMPTY) << endl;					/*	空マスの数									*/
		cout << "  --------- " << endl;
		cout << endl;

		/************************/
		/*	更新				*/
		/************************/
		if (reversi_console_board.isGameOver())
		{
			/*------------------*/
			/* ゲーム終了		*/
			/*------------------*/
			cout << "   -----------------  " << endl;
			cout << "  | Congratulations | " << endl;
			cout << "   -----------------  " << endl;
			if (reversi_console_board.GetDiscColor(BLACK) >  reversi_console_board.GetDiscColor(WHITE))
			{
				std::cout << "  黒が勝利しました " << std::endl;
			}
			else if (reversi_console_board.GetDiscColor(BLACK) <  reversi_console_board.GetDiscColor(WHITE))
			{
				std::cout << "  白が勝利しました " << std::endl;
			}
			cout << "  黒石   : " << reversi_console_board.GetDiscColor(BLACK) << endl;					/*	黒石の数									*/
			cout << "  白石   : " << reversi_console_board.GetDiscColor(WHITE) << endl;					/*	白石の数									*/
			cout << "  空マス : " << reversi_console_board.GetDiscColor(EMPTY) << endl;					/*	空マスの数									*/
			cout << endl;
			
			cout << "----------------------------ゲーム終了----------------------------" << endl;
			cout << "終了しますか？" << endl;
			cout << "このプログラム終了場合は、何か文字を入力してからEnterキーを押してください";
			cin >> i;
			break;

		}
		else
		{
			/*------------------*/
			/*	ゲーム中		*/
			/*------------------*/

			/*------------------*/
			/*	プレイヤー		*/
			/*------------------*/
			status = player[current_player]->PlayerTurn(reversi_console_board);
			
			if (status == INPUT_ERROR)
			{			
				/*------------------*/
				/* エラー			*/
				/*------------------*/
				continue;
			}
			else if (status == EnablePos)
			{
				/*----------------------*/
				/* 打てる位置を表示		*/
				/*----------------------*/
				continue;
			}
			else
			{
				current_player = ++current_player % 2;
			}
	
		}
		cout << endl;
	}

	delete player[0];
	delete player[1];

	return 0;
}