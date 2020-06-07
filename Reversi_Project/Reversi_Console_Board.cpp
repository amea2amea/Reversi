/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* ���O���			*/
/*------------------*/
using namespace std;

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		ReversiConsolePrint		:	�R���\�[����̕`��					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]							:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*------------------------------------------------------------------------------*/
void Reversi_Console_Board::ReversiConsolePrint( int status)
{
	cout << "    a b c d e f g h " << endl;											/*	�A���t�@�x�b�g�̕\�� ( ������ )				*/

	for (int y = 1; y <= BOARD_SIZE_Y; y++)
	{
		cout << "  " <<  y << " ";													/*	�����̕\��           ( �c���� )				*/

		for (int x = 1; x <= BOARD_SIZE_X; x++)
		{
			switch (GetColor(Stone_Point(x, y)))
			{
			case	BLACK:															/*	��											*/
				cout <<  "��" ;														/*	���ۂ�`��									*/
				break;

			case	WHITE:															/*	��											*/
				cout <<  "��" ;														/*	���ۂ�`��									*/
				break;

			case	WALL:															/*	��											*/
				break;

			case	EMPTY:															/*	�Ȃ�										*/														
				if (status == EnablePos )											/*	�łĂ�ʒu��\��							*/
				{
					if (CheckEnablePos(Stone_Point(x, y)))
					{
						cout << "��";
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
		cout  << endl;																/*	���s										*/
	}

	return;
}
