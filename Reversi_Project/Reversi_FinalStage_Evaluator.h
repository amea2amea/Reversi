#ifndef Reversi_FinalStage_Evaluator_h
#define Reversi_FinalStage_Evaluator_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Evaluator.h"

/*--------------------------------------*/
/*	�I�Ղ̏�ʂɂ�����]���֐��N���X	*/
/*--------------------------------------*/
class Reversi_FinalStage_Evaluator : public Reversi_Evaluator		/*	�I�Ղ̏�ʂɂ�����]���֐��N���X						*/
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_FinalStage_Evaluator();									/*	�����Ȃ��R���X�g���N�^									*/
	int Evaluate(const Reversi_Board&);

};

#endif