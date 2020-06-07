#ifndef Reversi_Player_h
#define Reversi_Player_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Board.h"
#include "Reversi_AI.h"

/*----------------------------------*/
/*	Playerクラス ( 抽象クラス )		*/
/*----------------------------------*/
class Reversi_Player												/*	Playerクラス											*/
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_Player() {} 											/*	引数なしコンストラクタ									*/
	virtual ~Reversi_Player() {} 									/*	引数なしデストラクタ									*/
	virtual int PlayerTurn(Reversi_Board&) = 0;						/*	Playerの番												*/

};

/*----------------------------------*/
/*	 AI用のPlayerクラス				*/
/*----------------------------------*/
class Reversi_AI_Player : public Reversi_Player						/*	AI用のPlayerクラス										*/
{
	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	Reversi_AI*			m_reversi_AI;								/*	AIクラス												*/

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_AI_Player();											/*	引数なしコンストラクタ									*/
	virtual ~Reversi_AI_Player();									/*	引数なしデストラクタ									*/
	int PlayerTurn(Reversi_Board&);									/*	Playerの番												*/

};

/*----------------------------------*/
/*	 人間用のPlayerクラス			*/
/*----------------------------------*/
class Reversi_Human_Player	:	public Reversi_Player				/*	 人間用のPlayerクラス									*/
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_Human_Player(); 										/*	引数なしコンストラクタ									*/
	virtual ~Reversi_Human_Player() {} 								/*	引数なしデストラクタ									*/
	int PlayerTurn(Reversi_Board&);									/*	Playerの番												*/

};

#endif
