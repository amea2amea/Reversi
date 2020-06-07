/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_MiniMax_AI.h"
#include "Reversi_Player.h"


/*----------------------------------*/
/*	 �l�ԗp��Player�N���X			*/
/*----------------------------------*/

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	Reversi_AI_Player			:	�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_AI_Player::Reversi_AI_Player() : m_reversi_AI( NULL )
{
	m_reversi_AI = new Reversi_MiniMax_AI();
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	~Reversi_AI_Player			:	�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_AI_Player::~Reversi_AI_Player() 
{
	delete m_reversi_AI;
	m_reversi_AI = 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		PlayerTurn			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_AI_Player::PlayerTurn(Reversi_Board& reversi_board)
{
	/************************/
	/*	����				*/
	/************************/
	if (reversi_board.GetCurrentColor() == BLACK)
	{
		std::cout << "  ��� : ��" << std::endl;
	}
	else if (reversi_board.GetCurrentColor() == WHITE)
	{
		std::cout << "  ��� : ��" << std::endl;
	}
	std::cout << "  �R���s���[�^�v�l���E�E�E�E�E�E" << std::endl;
	m_reversi_AI->Move(reversi_board);
	std::cout << std::endl;

	return 0;
}

/*======================================================================================================*/

/*----------------------------------*/
/*	 �l�ԗp��Player�N���X			*/
/*----------------------------------*/

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	Reversi_Human_Player		:	�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_Human_Player::Reversi_Human_Player()
{
	;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		PlayerTurn			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_Human_Player::PlayerTurn(Reversi_Board& reversi_board)
{
	std::string					stone_input;
	Stone_Info					stone_info;

	/************************/
	/*	����				*/
	/************************/
	if (reversi_board.GetCurrentColor() == BLACK)
	{
		std::cout << "  ��� : ��" << std::endl;
	}
	else if (reversi_board.GetCurrentColor() == WHITE)
	{
		std::cout << "  ��� : ��" << std::endl;
	}
	std::cout << "  =================================================== " << std::endl;
	std::cout << "  �΂�ł� => �A���t�@�x�b�g���� (��Fe6) " << std::endl;
	std::cout << "  �p�X => p " << std::endl;
	std::cout << "  UNDO => u " << std::endl;
	std::cout << "  �΂�u����ʒu => h " << std::endl;
	std::cout << "  =================================================== " << std::endl;
	std::cout << "  �����͂��Ă������� : ";
	std::cin >> stone_input;
	std::cout << std::endl;

	/************************/
	/*	�X�V				*/
	/************************/
	if (stone_input == "p")
	{
		/*------------------*/
		/* �p�X				*/
		/*------------------*/
		if (reversi_board.Pass() == true)
		{
			std::cerr << "  -> �p�X���܂�" << std::endl;
			std::cout << std::endl;
			return PASS;
		}
		else
		{
			std::cerr << "  -> �p�X�ł��܂���" << std::endl;
			std::cout << std::endl;
		}
	}
	if (stone_input == "h")
	{
		/*----------------------*/
		/* �łĂ�ʒu��\��		*/
		/*----------------------*/
		return EnablePos;
	}
	else if (stone_input == "u")
	{
		/*------------------*/
		/* undo				*/
		/*------------------*/
		if (reversi_board.Undo() == true)
		{
			std::cerr << "  -> �߂��܂�" << std::endl;
			std::cout << std::endl;
			return UNDO;
		}
		else
		{
			std::cerr << "  -> �߂��܂���" << std::endl;
			std::cout << std::endl;
		}
	}
	else if(((stone_input[0] >= 'a') && (stone_input[0] <= 'h'))
		&& ((stone_input[1] >= '1') && (stone_input[1] <= '8')))

	{
		try
		{
			/*------------------*/
			/* �΂̈ʒu���擾	*/
			/*------------------*/
			Stone_Point				store_point(stone_input);
			stone_info.x		=	store_point.x;
			stone_info.y		=	store_point.y;
			stone_info.color	=	reversi_board.GetCurrentColor();

		}
		catch (std::invalid_argument)
		{
			/*------------------*/
			/* �G���[			*/
			/*------------------*/
			std::cerr << "  ->���o�[�V�̎��ł��Ă�������" << std::endl;
			std::cout << std::endl;
			return INPUT_ERROR;
		}

		/*------------------*/
		/* �ړ�				*/
		/*------------------*/
		if (reversi_board.Move(stone_info))
		{
			std::cerr << "  ->�ł��܂���" << std::endl;
			std::cout << std::endl;
			return MOVE;
		}
		else
		{
			std::cerr << "  ->�����ɂ͒u���܂���" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{ 
		/*------------------*/
		/* �G���[			*/
		/*------------------*/
		std::cerr << "  ->���o�[�V�̎��ł��Ă�������" << std::endl;
		std::cout << std::endl;
		return INPUT_ERROR;
	
	}

	return INPUT_ERROR;
}