#ifndef Reversi_Board_h
#define Reversi_Board_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Point.h"
#include "Array2D.h"
#include "Array1D.h"

/*--------------*/
/*	�N���X		*/
/*--------------*/

/************************/
/*	�{�[�h�̃N���X		*/
/************************/

class Reversi_Board 
{
/*--------------------------*/
/*	�����o�ϐ�	( ��`�p )	*/
/*--------------------------*/
public:
	static const short						BOARD_SIZE_X			= 8;									/*	�{�[�h�̉��T�C�Y								*/
	static const short						BOARD_SIZE_Y			= 8;									/*	�{�[�h�̏c�T�C�Y								*/
	static const short						BOARD_SIZE				= BOARD_SIZE_X * BOARD_SIZE_Y;			/*	�{�[�h�T�C�Y									*/
	static const short						COLOR_NUM				=	3;									/*	�F�̎��										*/
	static const short						COLOR_START_POINT		=	-1;									/*	�F�̊J�n�f�[�^									*/
	static const short						Discs_START_POINT_X1	=	4;									/*	�΂̏����z�u1									*/
	static const short						Discs_START_POINT_Y1	=	4;									/*	�΂̏����z�u1									*/
	static const short						Discs_START_POINT_X2	=	5;									/*	�΂̏����z�u2									*/
	static const short						Discs_START_POINT_Y2	=	5;									/*	�΂̏����z�u2									*/
	static const short						MAX_TURNS				=	BOARD_SIZE;							/*	�萔											*/

/*--------------*/
/*	�����o�ϐ�	*/
/*--------------*/
private:
	Array2D< Reversi_Point >					m_Discs;													/*	���݂̃{�[�h�̏��								*/
	Array1D< int >								m_ColorStarge;												/*	�{�[�h�̐F���									*/
																											/*		->	-1: ��	0�F�Ȃ� 1: ��					*/
	short										m_CurrentColor;												/*	���݂̎�Ԃ̐΂̐F								*/										
																											/*		->	-1: ���@1: ��							*/
	unsigned short								m_Turns;													/*	���݂̎萔										*/
	std::vector< std::vector< Stone_Info > >	m_UpdateLog;												/*	�e�菇�̍X�V�����{�[�h�̏�Ԃ�ۑ�			*/
	std::vector< Stone_Info >					m_EnablePos[MAX_TURNS + 1];									/*	�e�菇�ɂ����Đ΂�łĂ�ʒu�ۑ�				*/
	Array2D<Reversi_Point>						m_EnableDir[MAX_TURNS + 1];									/*	�e�菇�ɂ����đS�ʒu�Ő΂𗠕Ԃ��������ۑ�	*/

/*--------------*/
/*	�����o�֐�	*/
/*--------------*/
private:
	unsigned short			CheckMobility( const Stone_Info& ) const;
	unsigned short			CheckDirections( const Stone_Info& , unsigned short ) const;
	void					flipDiscss( const Stone_Info& );
	void					flipDirections(const Stone_Info& , std::vector< Stone_Info >&, unsigned short );
	void					InitMove();
	void					Init();
	void					ChangePlayer();

public:
	Reversi_Board();																						/*	�����Ȃ��R���X�g���N�^							*/
	short								GetColor(Stone_Point) const;										/*	�w�肵���΂̈ʒu�̏�Ԃ��擾					*/
	short								GetDiscColor(Stone_State ) const;									/*	�w�肵���΂̈ʒu�̏�Ԃ��擾					*/
	unsigned short						GetTurns() const;
	short								GetCurrentColor() const;
	bool								Move(const Stone_Info&);
	std::vector< Stone_Info >&			GetEnablePos();
	bool								CheckEnablePos(Stone_Point );
	bool								Pass();
	bool								isGameOver();
	bool								Undo();
	virtual void						ReversiConsolePrint() {};
};
#endif