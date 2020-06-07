#ifndef Reversi_Board_h
#define Reversi_Board_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Reversi.h"
#include "Reversi_Point.h"
#include "Array2D.h"
#include "Array1D.h"

/*--------------*/
/*	クラス		*/
/*--------------*/

/************************/
/*	ボードのクラス		*/
/************************/

class Reversi_Board 
{
/*--------------------------*/
/*	メンバ変数	( 定義用 )	*/
/*--------------------------*/
public:
	static const short						BOARD_SIZE_X			= 8;									/*	ボードの横サイズ								*/
	static const short						BOARD_SIZE_Y			= 8;									/*	ボードの縦サイズ								*/
	static const short						BOARD_SIZE				= BOARD_SIZE_X * BOARD_SIZE_Y;			/*	ボードサイズ									*/
	static const short						COLOR_NUM				=	3;									/*	色の種類										*/
	static const short						COLOR_START_POINT		=	-1;									/*	色の開始データ									*/
	static const short						Discs_START_POINT_X1	=	4;									/*	石の初期配置1									*/
	static const short						Discs_START_POINT_Y1	=	4;									/*	石の初期配置1									*/
	static const short						Discs_START_POINT_X2	=	5;									/*	石の初期配置2									*/
	static const short						Discs_START_POINT_Y2	=	5;									/*	石の初期配置2									*/
	static const short						MAX_TURNS				=	BOARD_SIZE;							/*	手数											*/

/*--------------*/
/*	メンバ変数	*/
/*--------------*/
private:
	Array2D< Reversi_Point >					m_Discs;													/*	現在のボードの状態								*/
	Array1D< int >								m_ColorStarge;												/*	ボードの色情報									*/
																											/*		->	-1: 白	0：なし 1: 黒					*/
	short										m_CurrentColor;												/*	現在の手番の石の色								*/										
																											/*		->	-1: 白　1: 黒							*/
	unsigned short								m_Turns;													/*	現在の手数										*/
	std::vector< std::vector< Stone_Info > >	m_UpdateLog;												/*	各手順の更新されるボードの状態を保存			*/
	std::vector< Stone_Info >					m_EnablePos[MAX_TURNS + 1];									/*	各手順において石を打てる位置保存				*/
	Array2D<Reversi_Point>						m_EnableDir[MAX_TURNS + 1];									/*	各手順において全位置で石を裏返せる方向を保存	*/

/*--------------*/
/*	メンバ関数	*/
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
	Reversi_Board();																						/*	引数なしコンストラクタ							*/
	short								GetColor(Stone_Point) const;										/*	指定した石の位置の状態を取得					*/
	short								GetDiscColor(Stone_State ) const;									/*	指定した石の位置の状態を取得					*/
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