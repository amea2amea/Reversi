#ifndef Reversi_Point_h
#define Reversi_Point_h

/*--------------*/
/*	クラス		*/
/*--------------*/
class Reversi_Point										/*	ボード位置クラス					*/
{
/*--------------*/
/*	メンバ変数	*/
/*--------------*/
private:
	short							m_Color;			/* 石の状態								*/
	unsigned short					m_dir;				/* 石を裏返せる方向						*/

/*--------------*/
/*	メンバ関数	*/
/*--------------*/
public:
	Reversi_Point();									/* 引数なしコンストラクタ				*/
	Reversi_Point( short, unsigned short );				/* 引数ありコンストラクタ				*/
	const short&	GetColor() const;
	short&			SetColor();
	const unsigned short& GetDirection() const;
	unsigned short& SetDirection();

};
#endif