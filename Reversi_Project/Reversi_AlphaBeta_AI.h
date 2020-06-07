#ifndef Reversi_AlphaBeta_AI_h
#define Reversi_AlphaBeta_AI_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_AI.h"

/*----------------------------------*/
/*	Alpha_Beta�@��p����AI�N���X	*/
/*----------------------------------*/
class Reversi_AlphaBeta_AI	:	public Reversi_AI					/*	Alpha_Beta�@��p����AI�N���X						*/
{

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
private:
	int		Evaluate( const Reversi_Board& );
	int		Alpahabeta(Reversi_Board&, int, int, int );

public:
	Reversi_AlphaBeta_AI();
	void	Move(Reversi_Board&);

};

#endif
