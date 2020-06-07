#ifndef Reversi_Console_Board_h
#define Reversi_Console_Board_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Board.h"

/*--------------*/
/*	クラス		*/
/*--------------*/

/********************************/
/*	コンソールボードのクラス	*/
/********************************/
class Reversi_Console_Board : public Reversi_Board
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	virtual void ReversiConsolePrint( int );
};
#endif
