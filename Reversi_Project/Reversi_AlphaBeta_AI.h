#ifndef Reversi_AlphaBeta_AI_h
#define Reversi_AlphaBeta_AI_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi_AI.h"

/*----------------------------------*/
/*	Alpha_Beta法を用いたAIクラス	*/
/*----------------------------------*/
class Reversi_AlphaBeta_AI	:	public Reversi_AI					/*	Alpha_Beta法を用いたAIクラス						*/
{

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
private:
	int		Evaluate( const Reversi_Board& );
	int		Alpahabeta(Reversi_Board&, int, int, int );

public:
	Reversi_AlphaBeta_AI();
	void	Move(Reversi_Board&);

};

#endif
