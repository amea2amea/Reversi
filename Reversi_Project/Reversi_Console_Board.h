#ifndef Reversi_Console_Board_h
#define Reversi_Console_Board_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Board.h"

/*--------------*/
/*	�N���X		*/
/*--------------*/

/********************************/
/*	�R���\�[���{�[�h�̃N���X	*/
/********************************/
class Reversi_Console_Board : public Reversi_Board
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	virtual void ReversiConsolePrint( int );
};
#endif
