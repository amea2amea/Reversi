#ifndef Reversi_ScoreTable_Evaluator_h
#define Reversi_ScoreTable_Evaluator_h


/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Evaluator.h"

/*--------------------------------------*/
/*	���_�e�[�u���ɂ�����]���֐��N���X	*/
/*--------------------------------------*/
class Reversi_ScoreTable_Evaluator : public Reversi_Evaluator		/*	���_�e�[�u���ɂ�����]���֐��N���X						*/
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_ScoreTable_Evaluator();									/*	�����Ȃ��R���X�g���N�^									*/
	int Evaluate(const Reversi_Board&);

};

#endif
