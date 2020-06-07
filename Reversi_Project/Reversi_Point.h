#ifndef Reversi_Point_h
#define Reversi_Point_h

/*--------------*/
/*	�N���X		*/
/*--------------*/
class Reversi_Point										/*	�{�[�h�ʒu�N���X					*/
{
/*--------------*/
/*	�����o�ϐ�	*/
/*--------------*/
private:
	short							m_Color;			/* �΂̏��								*/
	unsigned short					m_dir;				/* �΂𗠕Ԃ������						*/

/*--------------*/
/*	�����o�֐�	*/
/*--------------*/
public:
	Reversi_Point();									/* �����Ȃ��R���X�g���N�^				*/
	Reversi_Point( short, unsigned short );				/* ��������R���X�g���N�^				*/
	const short&	GetColor() const;
	short&			SetColor();
	const unsigned short& GetDirection() const;
	unsigned short& SetDirection();

};
#endif