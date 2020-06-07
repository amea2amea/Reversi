/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Player.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* ���O���			*/
/*------------------*/
using namespace std;

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		main					:	���o�[�V�̃��C������				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]							:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
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
	/* �R�}���h���C��	*/
	/*------------------*/
	if (argc > 1)
	{
		if(strcmp(argv[1], "-r") == 0) 
			bInitiative = true;
	}

	/*------------------*/
	/* ���E���		*/
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
	/* �Q�[���J�n		*/
	/*------------------*/
	cout << "----------------------------�Q�[���J�n----------------------------" << endl;
	cout << endl;

	while (1)
	{
		/************************/
		/*	�R���\�[���`��		*/
		/************************/
		cout << " ( " << reversi_console_board.GetTurns() + 1 << " ) " << endl;
		reversi_console_board.ReversiConsolePrint(status);											/*	�R���\�[����̕`��							*/
		cout << endl;

		cout << "  --------- " << endl;
		cout << "  ����   : " << reversi_console_board.GetDiscColor(BLACK) << endl;					/*	���΂̐�									*/
		cout << "  ����   : " << reversi_console_board.GetDiscColor(WHITE) << endl;					/*	���΂̐�									*/
		cout << "  ��}�X : " << reversi_console_board.GetDiscColor(EMPTY) << endl;					/*	��}�X�̐�									*/
		cout << "  --------- " << endl;
		cout << endl;

		/************************/
		/*	�X�V				*/
		/************************/
		if (reversi_console_board.isGameOver())
		{
			/*------------------*/
			/* �Q�[���I��		*/
			/*------------------*/
			cout << "   -----------------  " << endl;
			cout << "  | Congratulations | " << endl;
			cout << "   -----------------  " << endl;
			if (reversi_console_board.GetDiscColor(BLACK) >  reversi_console_board.GetDiscColor(WHITE))
			{
				std::cout << "  �����������܂��� " << std::endl;
			}
			else if (reversi_console_board.GetDiscColor(BLACK) <  reversi_console_board.GetDiscColor(WHITE))
			{
				std::cout << "  �����������܂��� " << std::endl;
			}
			cout << "  ����   : " << reversi_console_board.GetDiscColor(BLACK) << endl;					/*	���΂̐�									*/
			cout << "  ����   : " << reversi_console_board.GetDiscColor(WHITE) << endl;					/*	���΂̐�									*/
			cout << "  ��}�X : " << reversi_console_board.GetDiscColor(EMPTY) << endl;					/*	��}�X�̐�									*/
			cout << endl;
			
			cout << "----------------------------�Q�[���I��----------------------------" << endl;
			cout << "�I�����܂����H" << endl;
			cout << "���̃v���O�����I���ꍇ�́A������������͂��Ă���Enter�L�[�������Ă�������";
			cin >> i;
			break;

		}
		else
		{
			/*------------------*/
			/*	�Q�[����		*/
			/*------------------*/

			/*------------------*/
			/*	�v���C���[		*/
			/*------------------*/
			status = player[current_player]->PlayerTurn(reversi_console_board);
			
			if (status == INPUT_ERROR)
			{			
				/*------------------*/
				/* �G���[			*/
				/*------------------*/
				continue;
			}
			else if (status == EnablePos)
			{
				/*----------------------*/
				/* �łĂ�ʒu��\��		*/
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