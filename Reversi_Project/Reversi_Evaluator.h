#ifndef Reversi_Evaluator_h
#define Reversi_Evaluator_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Board.h"

/*----------------------------------*/
/*	�]���֐��N���X ( ���ۃN���X )	*/
/*----------------------------------*/
class Reversi_Evaluator												/*	�]���֐��N���X											*/
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_Evaluator() {} 											/*	�����Ȃ��R���X�g���N�^									*/
	virtual int Evaluate(const Reversi_Board&) = 0;

};

#endif
