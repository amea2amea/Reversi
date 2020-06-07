/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Reversi_MiniMax_AI.h"
#include "Reversi_FinalStage_Evaluator.h"
#include "Reversi_Console_Board.h"

/*------------------*/
/* �����o�֐�		*/
/*------------------*/

/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	Reversi_MiniMax_AI	:	const�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_MiniMax_AI::Reversi_MiniMax_AI()
{
	m_reversi_evaluator = new Reversi_FinalStage_Evaluator();
	m_normal_depth = 5;
}
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[�֐�]	~Reversi_AI_Player			:	�����Ȃ��R���X�g���N�^			*/
/*--------------------------------------------------------------------------*/
Reversi_MiniMax_AI::~Reversi_MiniMax_AI()
{
	delete m_reversi_evaluator;
	m_reversi_evaluator = 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Move				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
void Reversi_MiniMax_AI::Move(Reversi_Board& reversi_board)
{
	std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();			/*	�΂𗠕Ԃ���{�[�h�ʒu							*/
	int								limit = m_normal_depth;										/*	�ǂݎ�̐[��									*/

	/****************************/
	/*	�΂𗠕Ԃ���ʒu�̑���	*/
	/****************************/
	if (vector_stone_info.size() <= 1)															/*	�΂𗠕Ԃ���ʒu���������݂��Ȃ�				*/
	{
		/****************************/
		/*	��ǂ݂��Ȃ�			*/
		/****************************/
		if (vector_stone_info.size() == 0)														/*	�΂𗠕Ԃ�����W�ʒu�����݂��Ȃ�				*/
		{
			/*------------------*/
			/* �p�X				*/
			/*------------------*/
			if (reversi_board.Pass() == true)
			{
				std::cerr << "  -> �p�X���܂�" << std::endl;
			}
		}
		else if (vector_stone_info.size() == 1)													/*	�΂𗠕Ԃ�����W�ʒu��1�������݂��Ȃ�			*/
		{
			/*------------------*/
			/* �ړ�				*/
			/*------------------*/
			if (reversi_board.Move(vector_stone_info[0]))
			{
				std::cerr << "  ->�ł��܂���" << std::endl;
			}
		}
	}
	else																						/*	�΂𗠕Ԃ���ʒu���������݂���					*/
	{
		/****************************/
		/*	��ǂ݂��s��			*/
		/****************************/
		MiniMax(reversi_board, limit);
	}

	return;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Evaluate			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::Evaluate(const Reversi_Board& reversi_board)
{
	short Evaluate = 0;
	Evaluate	= m_reversi_evaluator->Evaluate(reversi_board);
	return Evaluate;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MiniMax				:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MiniMax(Reversi_Board& reversi_board, int limit)
{
	/*

		MiniMax�@�́A�����̎���ő�]���l(�����ɂƂ��Ĉ�ԗǂ���)��
		����̎���ŏ��]���l(�����ɂƂ��Ĉ�Ԋ댯�Ȏ�)�Ƃ���
		�T�����邱�Ƃœ��I�̕]���l�𓱂��o����@�ł��B

		���݂̑I���ł���S�Ă̎��ǂݍ��ނ��Ƃň�ԗǂ��]���l�𓱂��o���B
		( 1���̎�ɂ����Đ�ǂݐ����ǂݍ��ނ��Ƃōő�l(�ŏ��l)�𓱂� )

		��	MaxLevel	->	�����̎��ǂ�
		��	MiniLevel	->	����̎��ǂ�	

	*/

	/****************************************/
	/*	��ǂ݂̎�̐ݒ�					*/
	/*		���O��1�ԍŏ��̎��ݒ肵�Ă���	*/
	/****************************************/
	const std::vector< Stone_Info >&	vector_stone_info = reversi_board.GetEnablePos();	/*	�΂𗠕Ԃ���{�[�h�ʒu							*/
	m_next_stone_info = vector_stone_info[0];

	/****************************/
	/*	��ǂ݊J�n				*/
	/****************************/
	MaxLevel(reversi_board, limit);

	/****************************/
	/*	�ړ�					*/
	/****************************/
	if (reversi_board.Move(m_next_stone_info))
	{
		std::cerr << "  ->�ł��܂���" << std::endl;
	}

	return 0;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MiniLevel			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MiniLevel(Reversi_Board& reversi_board, int limit)
{
	/****************************/
	/*	��ǂݎ萔�������ς�	*/
	/****************************/
	if (	(limit == 0)																		/*	��ǂݎ萔���ǂݏI������						*/
		||	(reversi_board.isGameOver()))														/*	�Q�[�����I��������								*/
	{
//		std::cout << "  " << m_normal_depth - limit << "���ǂ݊����E�E�E�E�E" << std::endl;
		return Evaluate(reversi_board);															/*	�]���l��Ԃ�									*/
	}

	/****************************/
	/*	��ǂݒ� ( �T���� )		*/
	/****************************/
	const std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();	/*	�΂𗠕Ԃ���{�[�h�ʒu							*/
	Stone_Info	stone_info;
	int			score = 0;																		/*	���݂̃X�R�A									*/
	int			score_mini = 0;															/*	�ŏ��X�R�A										*/

	for (unsigned int disc_count = 0; disc_count < vector_stone_info.size(); disc_count++)
	{
		stone_info = vector_stone_info.at(disc_count);											/*	�΂�łĂ�ʒu���擾							*/
		reversi_board.Move(stone_info);															/*	�΂�ł�										*/
		DebugCode(reversi_board, disc_count, limit - 1);
	
		score = MaxLevel(reversi_board, limit - 1);												/*	�����̎��ǂ�									*/
		reversi_board.Undo();																	/*	���߂�										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		if ( score < score_mini )
		{
			score_mini = score;																	/*	�ŏ��X�R�A�̍X�V								*/
		}
	}

	return score_mini;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MaxLevel			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
int Reversi_MiniMax_AI::MaxLevel(Reversi_Board& reversi_board, int limit)
{
	/****************************/
	/*	��ǂݎ萔�������ς�	*/
	/****************************/
	if (	(limit == 0)																		/*	��ǂݎ萔���ǂݏI������						*/
		||	(reversi_board.isGameOver()))														/*	�Q�[�����I��������								*/
	{
//		std::cout << "  " << m_normal_depth - limit << "���ǂ݊����E�E�E�E�E" << std::endl;
		return Evaluate(reversi_board);															/*	�]���l��Ԃ�									*/
	}

	/****************************/
	/*	��ǂݒ� ( �T���� )		*/
	/****************************/
	const std::vector< Stone_Info >&		vector_stone_info = reversi_board.GetEnablePos();	/*	�΂𗠕Ԃ���{�[�h�ʒu							*/
	Stone_Info	stone_info;
	int			score		= 0;																/*	���݂̃X�R�A									*/
	int			score_max	= 0;																/*	�ő�X�R�A										*/

	for (unsigned int disc_count = 0; disc_count < vector_stone_info.size(); disc_count++)
	{
		stone_info = vector_stone_info.at(disc_count);											/*	�΂�łĂ�ʒu���擾							*/
		reversi_board.Move(stone_info);															/*	�΂�ł�										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		score = MiniLevel(reversi_board, limit - 1);											/*	����̎��ǂ�									*/
		reversi_board.Undo();																	/*	���߂�										*/
		DebugCode(reversi_board, disc_count, limit - 1);

		if ( score > score_max)
		{
			score_max = score;																	/*	�ő�X�R�A�̍X�V								*/
			
			if (limit == m_normal_depth)														/*	���݂̓ǂݎ�Ȃ��								*/
			{
				m_next_stone_info = stone_info;													/*	���̓ǂݎ�����肷��							*/
			}
		}
	}

	return score_max;
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		DebugCode			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]						:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*------------------------------------------------------------------------------*/
void Reversi_MiniMax_AI::DebugCode(Reversi_Board& reversi_board, int disc_count, int limit)
{
#if 0
	std::cout << "  No." << disc_count + 1 << " - ";
	std::cout << m_normal_depth - limit << "��ڂ̐�ǂݒ��E�E�E�E�E�E" << std::endl;
	std::cout << std::endl;
	reversi_board.ReversiConsolePrint();
	std::cout << std::endl;
#endif
	return;
}