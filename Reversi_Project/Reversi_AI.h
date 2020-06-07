#ifndef Reversi_AI_h
#define Reversi_AI_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_Board.h"
#include "Reversi_Evaluator.h"

/*------------------------------*/
/*	AIクラス ( 抽象クラス )		*/
/*------------------------------*/
class Reversi_AI															/*	AIクラス											*/
{
	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
protected:
	unsigned short			m_pre_search_depth;
	unsigned short			m_normal_depth;
	unsigned short			m_wld_depth;
	unsigned short			m_perfect_depth;
	Reversi_Evaluator*		m_reversi_evaluator;

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	Reversi_AI() : m_pre_search_depth(3), m_normal_depth(5),
		m_wld_depth(15), m_perfect_depth(13), m_reversi_evaluator(NULL)		/*	引数付きコンストラクタ								*/
	{}
	virtual ~Reversi_AI() {};												/*	引数なしデストラクタ									*/
	virtual void Move( Reversi_Board& ) = 0;

};

#endif