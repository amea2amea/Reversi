#ifndef Reversi_h
#define Reversi_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include <vector>
#include <sstream>
#include <iostream>

/*--------------*/
/*	�񋓑�		*/
/*--------------*/
		
enum Reversi_State																				/*	���o�[�V�̏��								*/
{
	PASS,																						/*	�p�X										*/
	INPUT_ERROR,																				/*	�G���[										*/
	UNDO,																						/*	UNDO										*/
	EXIT,																						/*	�I��										*/
	MOVE,																						/*	�{�[�h�ɑł�								*/
	EnablePos																					/*	�łĂ�ʒu��\��							*/
};

enum Stone_State																				/*	�{�[�h�ʒu�̏��							*/
{
	BLACK = 1,																					/*	��											*/
	EMPTY = 0,																					/*	�Ȃ�										*/
	WHITE = -1,																					/*	��											*/
	WALL = 2																					/*	��											*/
};

enum Reversed_Direction																			/*	�{�[�h�ʒu���痠�Ԃ������					*/
{
	REVERSED_NONE			= 0x00,																/*	�΂�łĂȂ�								*/
	REVERSED_UPPER			= 0x01,																/*	������̐΂𗠕Ԃ���						*/
	REVERSED_UPPER_RIGHT	= 0x02,																/*	�E������̐΂𗠕Ԃ���						*/
	REVERSED_RIGHT			= 0x04,																/*	�E�����̐΂𗠕Ԃ���						*/
	REVERSED_LOWER_RIGHT	= 0x08,																/*	�E�������̐΂𗠕Ԃ���						*/
	REVERSED_LOWER			= 0x10,																/*	�������̐΂𗠕Ԃ���						*/
	REVERSED_LOWER_LEFT		= 0x20,																/*	���������̐΂𗠕Ԃ���						*/
	REVERSED_LEFT			= 0x40,																/*	�������̐΂𗠕Ԃ���						*/
	REVERSED_UPPER_LEFT		= 0x80																/*	��������̐΂𗠕Ԃ���						*/
};


enum Search_Direction																			/*	�{�[�h�̌�������							*/
{
	SEARCH_UPPER	= 0x01,																		/*	�����										*/
	SEARCH_RIGHT	= 0x02,																		/*	�E����										*/
	SEARCH_LOWER	= 0x04,																		/*	������										*/
	SEARCH_LEFT		= 0x08,																		/*	������										*/
};

/*--------------*/
/*	�\����		*/
/*--------------*/
																								/*	�{�[�g�ʒu�̍\����							*/
struct Stone_Point
{
	/*----------------------*/
	/*	���W�ʒu			*/
	/*----------------------*/
	unsigned int x;																				/*	���W�ʒu ( �� )								*/
	unsigned int y;																				/*	���W�ʒu ( �c )								*/

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Stone_Point()																				/*	�����Ȃ��R���X�g���N�^						*/
	{
		Stone_Point(0, 0);
	}
																							
	Stone_Point(int x, int y)																	/*	��������R���X�g���N�^						*/
	{
		this->x = x;
		this->y = y;
	}

	Stone_Point(std::string coordstr)
	{
		if ((coordstr.length() > 2)
			|| 
			(!(((coordstr[0] >= 'a') && (coordstr[0] <= 'h'))
			&& ((coordstr[1] >= '1') && (coordstr[1] <= '8')))))
		{
			return;
		}
		
		x = coordstr[0] - 'a' + 1;																/*	�A���t�@�x�b�g���͂��A�X�L�[�ϊ� ( ������ )	*/
		y = coordstr[1] - '1' + 1;																/*	�������͂��A�X�L�[��ϊ�		 ( �c���� )	*/
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		���Z�q�I�[�o�[���[�h	*/
	/*------------------------------*/

	const Stone_Point& operator()(int x, int y) const											/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Stone_Point(x, y);
	}

	Stone_Point& operator()(int x, int y)														/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Stone_Point(x, y);
	}

	operator std::string() const																/*	�������ݒ肳�ꂽ�Ƃ��̑���					*/
	{
		std::ostringstream oss;
		oss << static_cast<char>('a' + x - 1)													/*	�A���t�@�x�b�g�̃A�X�L�[�ɕϊ� ( ������ )	*/
			<< static_cast<char>('1' + y - 1);													/*	�����̃A�X�L�[�ɕϊ�		   ( �c���� )	*/

		return oss.str();
	}

};

																								/*	�{�[�g�ʒu�̍\����							*/
struct Stone_Info	:	public Stone_Point
{
	short color;

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Stone_Info()	:	Stone_Point(0, 0)														/*	�����Ȃ��R���X�g���N�^						*/
	{
		color = EMPTY;
	}
																					
	Stone_Info( int x, int y, int color ) : Stone_Point(x, y)									/*	��������R���X�g���N�^						*/
	{
		this->color = color;
	}


	/*------------------------------*/
	/*	opeart						*/
	/*		���Z�q�I�[�o�[���[�h	*/
	/*------------------------------*/

	const Stone_Info& operator()(int x, int y, int color) const									/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Stone_Info(x, y, color);
	}

	Stone_Point& operator()(int x, int y, int color)											/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Stone_Info(x, y, color);
	}

};

struct Stone_Eval : public Stone_Point
{
	int eval;

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Stone_Eval() : Stone_Point(0, 0)															/*	�����Ȃ��R���X�g���N�^						*/
	{
		eval = 0;
	}

	Stone_Eval(int x, int y, int eval) : Stone_Point(x, y)										/*	��������R���X�g���N�^						*/
	{
		this->eval = eval;
	}
};
#endif
