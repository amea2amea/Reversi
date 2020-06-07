#ifndef Reversi_AI_h
#define Reversi_AI_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Board.h"
#include "Reversi_Evaluator.h"

/*------------------------------*/
/*	AI�N���X ( ���ۃN���X )		*/
/*------------------------------*/
class Reversi_AI															/*	AI�N���X											*/
{
	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
protected:
	unsigned short			m_pre_search_depth;
	unsigned short			m_normal_depth;
	unsigned short			m_wld_depth;
	unsigned short			m_perfect_depth;
	Reversi_Evaluator*		m_reversi_evaluator;

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_AI() : m_pre_search_depth(3), m_normal_depth(5),
		m_wld_depth(15), m_perfect_depth(13), m_reversi_evaluator(NULL)		/*	�����t���R���X�g���N�^								*/
	{}
	virtual ~Reversi_AI() {};												/*	�����Ȃ��f�X�g���N�^									*/
	virtual void Move( Reversi_Board& ) = 0;

};

#endif