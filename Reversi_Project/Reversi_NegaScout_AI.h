#ifndef Reversi_NegaScout_AI_h
#define Reversi_NegaScout_AI_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_AI.h"

/*----------------------------------*/
/*	NegaScout�@��p����AI�N���X	*/
/*----------------------------------*/
class Reversi_NegaScout_AI : public Reversi_AI					/*	NegaScout�@��p����AI�N���X						*/
{

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
private:
	int		Evaluate(const Reversi_Board&);
	void	Sort(Reversi_Board&, std::vector< Stone_Info >&, int);
	int		Alpahabeta(Reversi_Board&, int, int, int);

public:
	Reversi_NegaScout_AI();
	void	Move(Reversi_Board&);

};

#endif
