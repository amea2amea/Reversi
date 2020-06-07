#ifndef Reversi_Player_h
#define Reversi_Player_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Board.h"
#include "Reversi_AI.h"

/*----------------------------------*/
/*	Player�N���X ( ���ۃN���X )		*/
/*----------------------------------*/
class Reversi_Player												/*	Player�N���X											*/
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_Player() {} 											/*	�����Ȃ��R���X�g���N�^									*/
	virtual ~Reversi_Player() {} 									/*	�����Ȃ��f�X�g���N�^									*/
	virtual int PlayerTurn(Reversi_Board&) = 0;						/*	Player�̔�												*/

};

/*----------------------------------*/
/*	 AI�p��Player�N���X				*/
/*----------------------------------*/
class Reversi_AI_Player : public Reversi_Player						/*	AI�p��Player�N���X										*/
{
	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	Reversi_AI*			m_reversi_AI;								/*	AI�N���X												*/

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_AI_Player();											/*	�����Ȃ��R���X�g���N�^									*/
	virtual ~Reversi_AI_Player();									/*	�����Ȃ��f�X�g���N�^									*/
	int PlayerTurn(Reversi_Board&);									/*	Player�̔�												*/

};

/*----------------------------------*/
/*	 �l�ԗp��Player�N���X			*/
/*----------------------------------*/
class Reversi_Human_Player	:	public Reversi_Player				/*	 �l�ԗp��Player�N���X									*/
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	Reversi_Human_Player(); 										/*	�����Ȃ��R���X�g���N�^									*/
	virtual ~Reversi_Human_Player() {} 								/*	�����Ȃ��f�X�g���N�^									*/
	int PlayerTurn(Reversi_Board&);									/*	Player�̔�												*/

};

#endif
