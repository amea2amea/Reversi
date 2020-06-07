/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_Board.h"

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------*/
/*																*/
/*	[�֐�]	Reversi_Board	:	const�����Ȃ��R���X�g���N�^		*/
/*--------------------------------------------------------------*/
Reversi_Board::Reversi_Board()
{
	m_Discs.SetSize( BOARD_SIZE_X + 2, BOARD_SIZE_Y + 2);
	m_ColorStarge.SetSize( COLOR_NUM, COLOR_START_POINT );
	Init();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Init				:	������									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::Init()
{
	Reversi_Point	reversi_point(EMPTY, REVERSED_NONE);
	Reversi_Point	reversi_wall( WALL,  REVERSED_NONE);
	Reversi_Point	reversi_white(WHITE, REVERSED_NONE);
	Reversi_Point	reversi_black(BLACK, REVERSED_NONE);

	/************************/
	/*	�{�[�h�ʒu�̏�����	*/
	/************************/
	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{
			m_Discs(x, y) = reversi_point;											/*	�{�[�h�ʒu�̏���������						*/
		}
	}

	/************************/
	/*	�ǂ̐ݒ�			*/
	/************************/
	for (int x = 0; x <= BOARD_SIZE_X + 1; x++)
	{
		m_Discs(x, 0) = reversi_wall;												/*	�ǂ̐ݒ� ( 1�ԏ� )								*/
		m_Discs(x, BOARD_SIZE_Y + 1) = reversi_wall;								/*	�ǂ̐ݒ� ( 1�ԉ� )								*/
	}

	for (int y = 0; y <= BOARD_SIZE_Y + 1; y++)
	{
		m_Discs(0, y) = reversi_wall;												/*	�ǂ̐ݒ� ( ���[ )								*/
		m_Discs(BOARD_SIZE_X + 1, y) = reversi_wall;								/*	�ǂ̐ݒ� ( �E�[ )								*/

	}

	/************************/
	/*	�����z�u�̐ݒ�		*/
	/************************/
	m_Discs(Discs_START_POINT_X1, Discs_START_POINT_Y1) = reversi_white;			/*	�΂̏����z�u ( �����Ίp�ʒu�@)					*/
	m_Discs(Discs_START_POINT_X2, Discs_START_POINT_Y2) = reversi_white;			/*	�΂̏����z�u ( �����Ίp�ʒu�@)					*/
	m_Discs(Discs_START_POINT_X1, Discs_START_POINT_Y2) = reversi_black;			/*	�΂̏����z�u ( �����Ίp�ʒu�@)					*/
	m_Discs(Discs_START_POINT_X2, Discs_START_POINT_Y1) = reversi_black;			/*	�΂̏����z�u ( �����Ίp�ʒu�@)					*/

	/************************/
	/*	�΂̐��������ݒ�	*/
	/************************/
	m_ColorStarge[BLACK]	= 2;												/*	�΂̐���ݒ� ( ���F )							*/
	m_ColorStarge[WHITE]	= 2;												/*	�΂̐���ݒ� ( ���F )							*/
	m_ColorStarge[EMPTY]	= BOARD_SIZE_X * BOARD_SIZE_Y - 4 ;					/*	�΂̐���ݒ� ( �Ȃ� )							*/

	/****************************/
	/*	�萔�̏�����			*/
	/****************************/
	m_Turns = 0;																/*	�萔											*/

	/****************************/
	/*	��Ԃ̐ݒ�				*/
	/****************************/
	m_CurrentColor = BLACK;														/*	���݂̎�� ( �΂̐F )							*/

	/****************************/
	/*	�{�[�h�̏�Ԃ�������		*/
	/****************************/
	m_UpdateLog.clear();														/*	�e�菇�̍X�V�����{�[�h�̏�Ԃ�ۑ�			*/

	/****************************/
	/*	�΂̒u����ʒu�̎擾	*/
	/****************************/
	InitMove();																	/*	�΂̈ʒu�����擾								*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		isGameOver			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Q�[���I��( 0:���Ȃ�	1:���� )		*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::isGameOver()
{





	/****************************/
	/*	�ő�萔���ǂ����̊m�F	*/
	/****************************/
	unsigned short truns = GetTurns();												/*	�萔											*/
	if (truns == MAX_TURNS - 4 )													/*	�萔���ő�萔�ɂȂ��Ă���						*/
		return true;																/*	�Q�[���I������									*/

	/****************************/
	/*	�΂𗠕Ԃ���ʒu�̑���	*/
	/****************************/
	std::vector< Stone_Info >&			vector_stone_info = GetEnablePos();			/*	�΂�łĂ�{�[�h�ʒu							*/
	if (vector_stone_info.size() != 0)												/*	�΂𗠕Ԃ�����W�ʒu�����݂���					*/
		return false;																/*	�Q�[���I�����Ȃ�								*/
	
	/*
		Note:
		�����̔Ԃɂ����Đ΂𗠕Ԃ���ʒu�̑��݂��Ȃ��Ȃ��
		����̔Ԃɐ΂��ʒu�𗠕Ԃ��鎖���ł���m�F
		�����A���葤�ɂ����Ă��΂𗠕Ԃ���ʒu�̑��݂��Ȃ��ꍇ�A
		���҂Ƃ��łĂȂ��̂ŁA�Q�[�����I������
	*/
	
	/****************************/
	/*	�Q�[���I���̔���		*/
	/****************************/
	short CurrentColor = GetCurrentColor();											/*	���݂̎�Ԃ̐΂̐F								*/

	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		Stone_Info							disc_point;								/*	�΂̈ʒu										*/
		disc_point.x = x;															/*	�΂̍��W�ʒu���X�V								*/
		disc_point.color = -CurrentColor;											/*	����Ԃ̐΂̐F��ݒ�							*/

		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{
			disc_point.y = y;														/*	�΂̍��W�ʒu���X�V								*/

			if (CheckMobility(disc_point) != REVERSED_NONE) 						/*	�΂�ł������ʒu�ɐ΂𗠕Ԃ�����������݂���	*/
				return false;														/*	�Q�[���I�����Ȃ�								*/
		}
	}

	return true;

}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	Move				:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]		unsigned short	:	�{�[�h�ʒu���								*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Move(const Stone_Info& stone_info )
{
	unsigned int		x		= stone_info.x;									/*	�΂�ł������ʒu(X)								*/
	unsigned int		y		= stone_info.y;									/*	�΂�ł������ʒu(Y)								*/
	unsigned short		truns	= GetTurns();									/*	�萔											*/
	unsigned short		dir		= m_EnableDir[truns](x, y).GetDirection();		/*	�΂�ł������ʒu�̐΂𗠕Ԃ������				*/

	/****************************/
	/*	�G���[					*/
	/****************************/
	if (	((x < 0) || (x > BOARD_SIZE_X))										/*	�ł������ʒu���{�[�h�O�ɂȂ�Ȃ�΃G���[(X)		*/
		||	((y < 0) || (y > BOARD_SIZE_Y))										/*	�ł������ʒu���{�[�h�O�ɂȂ�Ȃ�΃G���[(Y)		*/
		||	( dir == REVERSED_NONE))											/*	�ł������ʒu���΂𗠕Ԃ��Ȃ��ꏊ��������G���[	*/
	{
		return false;
	}

	/****************************/
	/*	�΂�u��				*/
	/****************************/
	Reversi_Point reversi_point(GetCurrentColor(), REVERSED_NONE);
	m_Discs(x, y) = reversi_point;

	/****************************/
	/*	�΂𗠕Ԃ�				*/
	/****************************/
	flipDiscss( stone_info );

	/****************************/
	/*	�萔�̍X�V				*/
	/****************************/
	m_Turns++;

	/****************************/
	/*	��Ԃ̌��				*/
	/****************************/
	ChangePlayer();

	/************************************/
	/*	���̎�ԂŐ΂̒u����ʒu�̎擾	*/
	/************************************/
	InitMove();
	
	return true;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	Pass				:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]		unsigned short	:	�{�[�h�ʒu���								*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Pass()
{
	std::vector< Stone_Info >&	vector_stone_info = GetEnablePos();		/*	�΂�łĂ�{�[�h�ʒu							*/

	/****************************/
	/*	�΂𗠕Ԃ���ʒu�̑���	*/
	/****************************/
	if (vector_stone_info.size() != 0)											/*	�΂𗠕Ԃ�����W�ʒu�����݂���					*/
		return false;															/*	�p�X���Ȃ�										*/

	/****************************/
	/*	�Q�[���I��				*/
	/****************************/
	if (isGameOver())															/*	�Q�[���I���Ȃ��								*/
		return false;															/*	�p�X���Ȃ�										*/

	/****************************/
	/*	��Ԃ̌��				*/
	/****************************/
	ChangePlayer();

	/************************************/
	/*	�e�菇�̃{�[�h�̕ύX�_���X�V	*/
	/************************************/
	m_UpdateLog.push_back(std::vector<Stone_Info>());							/*	�e�菇�̍X�V�����{�[�h�ύX�_��ۑ�			*/

	/****************************/
	/*	�΂̒u����ʒu�̎擾	*/
	/****************************/
	InitMove();

	return true;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	Undo				:	�w�肳�ꂽ�萔�܂ŏ�Ԃ�߂�				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]		unsigned short	:	���݂̎萔����߂��萔						*/
/*------------------------------------------------------------------------------*/
bool Reversi_Board::Undo()
{
	unsigned short						truns	= GetTurns();						/*	���݂̎萔										*/

	/****************************/
	/*	�J�n�n�_�Ȃ�I���		*/
	/****************************/
	if (truns == 0)																	/*	�J�n�n�_										*/
		return false;																/*	�߂�Ȃ�										*/

	const std::vector<Stone_Info>&		update = m_UpdateLog.back();				/*	1�O�̃{�[�h�̕ύX�_ ( �Ō�̗v�f )			*/

	/****************************/
	/*	��Ԃ�߂�				*/
	/****************************/
	ChangePlayer();

	/********************************/
	/*	�΂𗠕Ԃ�����W�ʒu�̍폜	*/
	/********************************/
	m_EnablePos[truns].clear();														/*	1�O�̐΂𗠕Ԃ�����W�ʒu���폜				*/

	/****************************/
	/*	�萔�̍X�V				*/
	/****************************/
	m_Turns--;


	if (update.empty())																/*	�p�X���Ă�����									*/
	{
		/****************************/
		/*	�΂𗠕Ԃ�������̍폜	*/
		/****************************/
		for (int x = 1; x <= BOARD_SIZE_X; x++)
		{
			for (int y = 1; y <= BOARD_SIZE_Y; y++)
			{
				m_EnableDir[truns](x, y).SetDirection() = REVERSED_NONE;			/*	�΂𗠕Ԃ������								*/
			}
		}
	}
	else																			/*	�p�X���Ă��Ȃ�									*/
	{
		/****************************/
		/*	�u�����΂�߂�			*/
		/****************************/
		Reversi_Point	reversi_point1(EMPTY, REVERSED_NONE);						/*	�{�[�h�ʒu�̏�����Ԃ�ݒ�						*/
		Stone_Info		stone_info			= update.at( 0 );						/*	1�O�̐΂�ł����ʒu���擾						*/
		m_Discs(stone_info.x, stone_info.y)	= reversi_point1;						/*	�{�[�h�ʒu�̏�Ԃ�������						*/

		/****************************/
		/*	���Ԃ����΂�߂�		*/
		/****************************/
		for (unsigned int i = 1; i < update.size(); i++)
		{
			stone_info = update.at( i );											/*	�΂𗠕Ԃ��������擾							*/
			Reversi_Point	reversi_point2( -stone_info.color, REVERSED_NONE);		/*	�΂𗠕Ԃ�������ݒ�							*/
			m_Discs(stone_info.x, stone_info.y) = reversi_point2;					/*	�{�[�h�ʒu�̏�Ԃ�߂�							*/
		}

		/****************************/
		/*	�΂̐����X�V			*/
		/****************************/
		m_ColorStarge[stone_info.color]		-= static_cast<int>(update.size());			/*	�΂�u�����ʒu�Ɨ��Ԃ����������΂̐F�����炷	*/
		m_ColorStarge[-stone_info.color]	+= static_cast<int>(update.size() - 1);		/*	�΂𗠕Ԃ��ꂽ�������΂̐F�𑝂₷				*/
																						/*�@( �z��̎w��ł͂Ȃ����߁A�}�C�i�X�ł����Ȃ�)	*/
		m_ColorStarge[EMPTY]++;															/*	�΂�߂����̂Ő΂̂Ȃ��ʒu���P�������₷		*/
	}

	/************************************/
	/*	�e�菇�̃{�[�h�̕ύX�_���X�V	*/
	/************************************/
	m_UpdateLog.pop_back();															/*	�΂�߂����̂ŋL�^�����ύX�_���폜(�������폜)	*/

	return true;
}
/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]		GetTurns				:	�萔���擾					*/
/*	------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short			:	�萔						*/
/*	[����]									�Ȃ�						*/
/*----------------------------------------------------------------------*/
unsigned short Reversi_Board::GetTurns() const
{
	return m_Turns;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[�֐�]		CheckEnablePos			:	�w�肵���ʒu���΂�łĂ�ʒu���擾����		*/
/*	----------------------------------------------------------------------------------	*/
/*	[�߂�l]	bool					:	�΂�łĂ�ʒu���ǂ���						*/
/*												true	->	�΂�łĂ�					*/
/*												false	->	�΂�łĂȂ�				*/
/*	[����]		Stone_Point				:	�΂̈ʒu									*/
/*--------------------------------------------------------------------------------------*/
bool Reversi_Board::CheckEnablePos( Stone_Point stone_point )
{
	Stone_Info								stone_info;									/*	�{�[�h�ʒu										*/
	std::vector< Stone_Info >&				vector_stone_info = GetEnablePos();			/*	�΂�łĂ�{�[�h�ʒu							*/

	for (unsigned int i = 0; i < vector_stone_info.size(); i++)
	{
		stone_info = vector_stone_info.at(i);											/*	�΂�łĂ�ʒu���擾							*/

		if (	(stone_point.x == stone_info.x)											/*	�΂�łĂ�ʒu�Ǝw�肵���ʒu������ ( X���W )	*/
			&&	(stone_point.y == stone_info.y))										/*	�΂�łĂ�ʒu�Ǝw�肵���ʒu������ ( Y���W )	*/
		{
			return true;																/*	�΂�łĂ�ʒu									*/
		}
	}

	return false;																		/*	�΂�łĂȂ��ʒu								*/
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetEnablePos				:	���݂̎�Ԃ̐΂�łĂ�ʒu		*/
/*	-------------------------------------------------------------------------	*/
/*	[�߂�l]	std::vector< Stone_Info >&	:	���݂̎�Ԃ̐΂�łĂ�ʒu		*/
/*	[����]										�Ȃ�							*/
/*------------------------------------------------------------------------------*/
std::vector< Stone_Info >& Reversi_Board::GetEnablePos() 
{
	unsigned short		truns = GetTurns();							/* �萔 */
	return m_EnablePos[truns];
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]		GetCurrentColor			:	���݂̎�Ԃ̐΂̐F���擾	*/
/*	------------------------------------------------------------------	*/
/*	[�߂�l]	short					:	�萔						*/
/*	[����]									�Ȃ�						*/
/*----------------------------------------------------------------------*/
short Reversi_Board::GetCurrentColor() const
{
	return m_CurrentColor;
}

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]		GetColor				:	�w�肵���΂̈ʒu�̏�Ԃ��擾	*/
/*	---------------------------------------------------------------------	*/
/*	[�߂�l]	short 					:	�΂̏��						*/
/*	[����]		Stone_Point				:	�΂̈ʒu						*/
/*--------------------------------------------------------------------------*/
short Reversi_Board::GetColor(Stone_Point stone_point) const
{
	return m_Discs(stone_point.x, stone_point.y).GetColor();
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]		ChangePlayer			:	��Ԃ̌��					*/
/*	------------------------------------------------------------------	*/
/*	[�߂�l]								�Ȃ�						*/
/*	[����]									�Ȃ�						*/
/*----------------------------------------------------------------------*/
void Reversi_Board::ChangePlayer()
{
	m_CurrentColor = -m_CurrentColor;
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]		GetDiscColor			:	�w�肵���΂̈ʒu�̏�Ԃ��擾	*/
/*	---------------------------------------------------------------------	*/
/*	[�߂�l]	short					:	�萔							*/
/*	[����]									�Ȃ�							*/
/*--------------------------------------------------------------------------*/
short Reversi_Board::GetDiscColor(Stone_State stone_state) const
{
	return m_ColorStarge[stone_state];
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	flipDiscs			:	�΂�ł�									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]		unsigned short	:	�{�[�h�ʒu���								*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::flipDiscss( const Stone_Info& stone_info)
{
	unsigned int				x = stone_info.x;												/*	�΂�łʒu(X)									*/
	unsigned int				y = stone_info.y;												/*	�΂�łʒu(Y)									*/
	short						CurrentColor = stone_info.color;								/*	���݂̎�Ԃ̐΂̐F								*/
	std::vector<Stone_Info>		update;															/*	�΂̏�Ԃ��L�^����								*/

	/****************************/
	/*	�u�����΂�ۑ�			*/
	/****************************/
	Stone_Info  Discs(x, y, CurrentColor);														/*	�΂�łʒu									*/
	update.push_back(Discs);																	/*	�΂̕ύX�_��ۑ� ( �΂�ł����ʒu��ۑ�	)		*/

	/****************************************************************/
	/*	�΂𗠕Ԃ�													*/				
	/*		-> �΂̔��] (��A�E���A�E�A�E���A���A�����A���A����)	*/
	/****************************************************************/
	for (int i = 0x01; i < REVERSED_UPPER_LEFT; i = i << 1)
	{
		flipDirections( stone_info, update, i );												/*	�΂𗠕Ԃ�										*/
	}

	/************************************/
	/*	�΂̏����X�V					*/
	/*		-> �΂̐�(���A���A��̐�)	*/
	/*		-> �΂̗��Ԃ�������ۑ�	*/
	/************************************/
	m_ColorStarge[CurrentColor] += static_cast<int>(update.size());								/*	�΂𗠕Ԃ����������΂̐F�𑝂₷				*/
	m_ColorStarge[-CurrentColor] -= static_cast<int>((update.size() - 1));						/*	�΂𗠕Ԃ��ꂽ�������΂̐F�����炷				*/
																								/*�@( �z��̎w��ł͂Ȃ����߁A�}�C�i�X�ł����Ȃ�)	*/
	m_ColorStarge[EMPTY]--;																		/*	�΂�ł����̂Ő΂̂Ȃ��ʒu���P�������炷		*/
	m_UpdateLog.push_back(update);																/*	�e�菇�̍X�V�����{�[�h�̏�Ԃ�ۑ�			*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	flipDirections			:	�w�肵���{�[�h�����ɑ΂���				*/
/*										�΂𔽓]������							*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�΂𗠕Ԃ��邩�̏��					*/
/*											0		: �΂𗠕Ԃ��Ȃ�			*/
/*											1		: �΂𗠕Ԃ���				*/
/*	[����]		unsigned short		:	�{�[�h�ʒu���							*/
/*				unsigned short		:	�{�[�h����								*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::flipDirections(const Stone_Info& stone_info, std::vector< Stone_Info >& update, unsigned short board_state )
{
	unsigned int				x				= stone_info.x;									/*	�΂�łʒu(X)									*/
	unsigned int				y				= stone_info.y;									/*	�΂�łʒu(Y)									*/
	short						CurrentColor	= stone_info.color;								/*	���݂̎�Ԃ̐΂̐F								*/
	unsigned short				truns			= GetTurns();									/*	�萔											*/
	unsigned short				dir				= m_EnableDir[truns](x, y).SetDirection();		/*	�΂𗠕Ԃ������								*/
	unsigned short				serch_dir		= 0;											/*	��������										*/

	/*
		Note:
		�e���(�㉺���E)�ɂ����Đ΂𔽓]������
		�Ȃ��A�X�N���[�����W�̂��߁A��̓}�C�i�X�����A���̓v���X�����A���̓}�C�i�X�����A�E�̓v���X����
	*/

	switch (dir & board_state)
	{
	case REVERSED_UPPER:														/*	������̐΂𗠕Ԃ���							*/
		y = y - 1;
		serch_dir = SEARCH_UPPER;
		break;

	case REVERSED_UPPER_RIGHT:													/*	�E������̐΂𗠕Ԃ���							*/
		x = x + 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_RIGHT;
		break;

	case REVERSED_RIGHT:														/*	�E�����̐΂𗠕Ԃ���							*/
		x = x + 1;
		serch_dir = SEARCH_RIGHT;
		break;

	case REVERSED_LOWER_RIGHT:													/*	�E�������̐΂𗠕Ԃ���							*/
		x = x + 1;
		y = y + 1;
		serch_dir = SEARCH_RIGHT | SEARCH_LOWER;
		break;

	case REVERSED_LOWER:														/*	�������̐΂𗠕Ԃ���							*/
		y = y + 1;
		serch_dir = SEARCH_LOWER;
		break;

	case REVERSED_LOWER_LEFT:													/*	���������̐΂𗠕Ԃ���							*/
		x = x - 1;
		y = y + 1;
		serch_dir = SEARCH_LOWER | SEARCH_LEFT;
		break;

	case REVERSED_LEFT:															/*	�������̐΂𗠕Ԃ���							*/
		x = x - 1;
		serch_dir = SEARCH_LEFT;
		break;

	case REVERSED_UPPER_LEFT:													/*	��������̐΂𗠕Ԃ���							*/
		x = x - 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_LEFT;
		break;

	case REVERSED_NONE:															/*	�΂�łĂȂ�									*/
	default:																	/*	����ȊO										*/
		return ;

	}

	while (m_Discs(x, y).GetColor() == -CurrentColor)							/*	�e��Ԃ̐΂̐F�������ɂȂ�܂ŒT��				*/
	{
		m_Discs(x, y).SetColor() = CurrentColor;								/*	�΂𔽓]������									*/
		Stone_Info	Discs2(x, y, CurrentColor);									/*	�΂𔽓]�������ʒu								*/
		update.push_back( Discs2 );												/*	�΂̕ύX�_��ۑ� ( �΂𗠕Ԃ����ʒu��ۑ�	)	*/

		if (serch_dir & SEARCH_UPPER)
			y--;
		if (serch_dir & SEARCH_RIGHT)
			x++;
		if (serch_dir & SEARCH_LOWER)
			y++;
		if (serch_dir & SEARCH_LEFT)
			x--;
	}

	return ;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	InitMovable			:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]							�Ȃ�										*/
/*------------------------------------------------------------------------------*/
void Reversi_Board::InitMove()
{
	Stone_Info			disc_info;												/*	�΂̈ʒu										*/
	short				CurrentColor	= GetCurrentColor();					/*	���݂̎�Ԃ̐΂̐F								*/
	unsigned short		dir				= REVERSED_NONE;						/*	�΂𗠕Ԃ������								*/
	unsigned short		truns			= GetTurns();							/*	�萔											*/

	m_EnableDir[truns].SetSize(BOARD_SIZE_X + 2, BOARD_SIZE_Y + 2);

	for (int x = 1; x <= BOARD_SIZE_X; x++)
	{
		disc_info.color = CurrentColor;
		disc_info.x = x;														/*	�΂̍��W�ʒu���X�V								*/

		for (int y = 1; y <= BOARD_SIZE_Y; y++)
		{	
			disc_info.y = y;													/*	�΂̍��W�ʒu���X�V								*/

			dir = CheckMobility( disc_info );									/*	�΂̈ʒu�ɑ΂��Đ΂𗠕Ԃ���������擾			*/

			if (dir != REVERSED_NONE)											/*	�΂�ł������ʒu�ɐ΂𗠕Ԃ������������Ȃ��	*/
			{
				m_EnablePos[truns].push_back( disc_info );						/*	�΂𗠕Ԃ�����W�ʒu��ۑ�						*/
			}
			m_EnableDir[truns](x, y).SetDirection() = dir;						/*	�΂�ł������ʒu�̐΂𗠕Ԃ������				*/
		}
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	CheckMobility		:	�w�肵���{�[�h�ʒu�ɑ΂���					*/
/*									�΂�łĂ邩�ǂ������肷��					*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�										*/
/*	[����]		unsigned short	:	�{�[�h�ʒu���								*/
/*------------------------------------------------------------------------------*/
unsigned short Reversi_Board::CheckMobility( const Stone_Info& stone_info ) const
{
	unsigned short  dir = REVERSED_NONE;										/*	�΂�Ԃ������									*/
	unsigned int	x = stone_info.x; ;											/*	�΂�ł������ʒu(X)								*/
	unsigned int	y = stone_info.y;											/*	�΂�ł������ʒu(Y)								*/


	if (m_Discs(x, y).GetColor() != EMPTY)										/*	�w�肵���{�[�h��ɐ΂�����ꍇ�A�΂�łĂȂ�	*/
		return dir;

	/* 
		Note:
		����̐΂𔽓]�ł���ʒu�ɂ����łĂȂ�����
		�΂�ł������ʒu����{�[�h��̊e��Ԃ��m�F����
		(��A�E���A�E�A�E���A���A�����A���A����̏�Ԃ��m�F)
	*/

	for (int i = 0x01; i < REVERSED_UPPER_LEFT; i = i << 1)
		dir |= CheckDirections( stone_info, i );								/*	�΂𗠕Ԃ���ꍇ�̓t���O���ݒ肳���			*/
	
	return dir;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]	CheckDirectionsr		:	�w�肵���{�[�h�����ɑ΂���				*/
/*										�΂�łĂ邩�ǂ������肷��				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�΂𗠕Ԃ��邩�̏��					*/
/*											0		: �΂𗠕Ԃ��Ȃ�			*/
/*											1�ȏ�	: �΂𗠕Ԃ���(���Ԃ������)*/
/*	[����]		unsigned short		:	�{�[�h�ʒu���							*/
/*				unsigned short		:	�{�[�h����								*/
/*------------------------------------------------------------------------------*/
unsigned short Reversi_Board::CheckDirections( const Stone_Info& stone_info, unsigned short board_state ) const
{	
	unsigned int	x				= stone_info.x; ;							/*	�΂�ł������ʒu(X)								*/
	unsigned int	y				= stone_info.y;								/*	�΂�ł������ʒu(Y)								*/
	short			CurrentColor	= stone_info.color;							/*	���݂̎�Ԃ̐΂̐F								*/
	unsigned short  dir				= REVERSED_NONE;							/*	�΂�Ԃ������									*/
	unsigned short  serch_dir		= 0;										/*	��������										*/

	/*
		Note:
		�e���(�㉺���E)�ɂ����ĂP��̉ӏ��Ɏ����̐F�Ɣ��΂̐F�̐΂����邩�ǂ����m�F����
		�����̒u�����ʒu�ɑ΂���1��̐΂����΂̐F�łȂ������͐΂𔽓]�ł��Ȃ��B
		�S�Ă̕����Ő΂𔽓]�ł��Ȃ��Ȃ�΂�u�����Ƃ��ł��Ȃ��B
		�Ȃ��A�X�N���[�����W�̂��߁A��̓}�C�i�X�����A���̓v���X�����A���̓}�C�i�X�����A�E�̓v���X����
	*/

	switch (board_state)
	{
	case REVERSED_UPPER:														/*	������̐΂𗠕Ԃ���							*/
		y = y - 1;
		serch_dir = SEARCH_UPPER;
		break;

	case REVERSED_UPPER_RIGHT:													/*	�E������̐΂𗠕Ԃ���							*/
		x = x + 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_RIGHT;
		break;

	case REVERSED_RIGHT:														/*	�E�����̐΂𗠕Ԃ���							*/
		x = x + 1;
		serch_dir = SEARCH_RIGHT;
		break;

	case REVERSED_LOWER_RIGHT:													/*	�E�������̐΂𗠕Ԃ���							*/
		x = x + 1;
		y = y + 1;
		serch_dir = SEARCH_RIGHT | SEARCH_LOWER;
		break;

	case REVERSED_LOWER:														/*	�������̐΂𗠕Ԃ���							*/
		y = y + 1;
		serch_dir = SEARCH_LOWER;
		break;

	case REVERSED_LOWER_LEFT:													/*	���������̐΂𗠕Ԃ���							*/
		x = x - 1;
		y = y + 1;
		serch_dir = SEARCH_LOWER | SEARCH_LEFT;
		break;

	case REVERSED_LEFT:															/*	�������̐΂𗠕Ԃ���							*/
		x = x - 1;
		serch_dir = SEARCH_LEFT;
		break;

	case REVERSED_UPPER_LEFT:													/*	��������̐΂𗠕Ԃ���							*/
		x = x - 1;
		y = y - 1;
		serch_dir = SEARCH_UPPER | SEARCH_LEFT;
		break;

	case REVERSED_NONE:															/*	�΂�łĂȂ�									*/
	default:																	/*	����ȊO										*/
		return dir;

	}

	if ( m_Discs(x, y).GetColor() == -CurrentColor )							/*	1��̕����̐΂����΂̐F�Ȃ�					*/
	{
		while ( m_Discs(x, y).GetColor() == -CurrentColor )						/*	������̐΂̐F���ς��܂ŒT��					*/
		{																		/*	�ǂ�{�[�h�ɐ΂��Ȃ��ꍇ������					*/
			if(serch_dir & SEARCH_UPPER)
				y--;
			if (serch_dir & SEARCH_RIGHT)
				x++;
			if (serch_dir & SEARCH_LOWER)
				y++;
			if (serch_dir & SEARCH_LEFT)
				x--;
		}

		if ( m_Discs(x, y).GetColor() == CurrentColor )							/*	�΂̐F���ω������ʒu�������΂̐F�ł���Ȃ��	*/
			dir = board_state;													/*	�΂𗠕Ԃ��������ݒ�							*/
	}

	return dir;
}