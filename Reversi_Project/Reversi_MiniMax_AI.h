#ifndef Reversi_MiniMax_AI_h
#define Reversi_MiniMax_AI_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_AI.h"

/*----------------------------------*/
/*	MiniMax法を用いたAIクラス		*/
/*----------------------------------*/
class Reversi_MiniMax_AI : public Reversi_AI					/*	MiniMax法を用いたAIクラス						*/
{

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	Stone_Info				m_next_stone_info;

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
private:
	int		Evaluate(const Reversi_Board&);
	int		MiniMax(Reversi_Board&, int );
	int		MiniLevel(Reversi_Board&, int );
	int		MaxLevel(Reversi_Board&, int );
	void	DebugCode(Reversi_Board&, int, int );

public:
	Reversi_MiniMax_AI();
	virtual ~Reversi_MiniMax_AI();
	void	Move(Reversi_Board&);

};

#endif
