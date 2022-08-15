#pragma once
#include "GameObject.h"

class SceneMain;

class Player : public GameObject
{
public:
	enum class Seq
	{
		kSeqMain,		// 普段のゲーム中
		kSeqGameOver,	// ゲームオーバー演出
		kSeqGameClear,	// ゲームクリア演出
		
		kSeqNum
	};
	// パワーアップの種類
	typedef enum PowerupType
	{
		kPowerupTypeShotPower,		// ショットの攻撃力、サイズ
		kPowerupTypeShotDir,		// 攻撃方向
		kPowerupTypeBackShot,		// 後方攻撃
		kPowerupTypeMoveSpeed,		// 移動速度
		kPowerupTypeShotInterval,	// 発射間隔

		kPowerupTypeNum
	}PowerupType;

	typedef struct ShotData
	{
		// 発射開始位置	プレイヤー位置からの差分
		float startOffsetX;
		float startOffsetY;
		// 速度
		float speed;
		// 角度
		float angle;
		// 攻撃力
		int power;
	}ShotData;
private:
	// 演出用にプレイヤー位置の過去ログを残す
	static constexpr int kPosLogNum = 8;
public:
	Player() : GameObject()
	{
		m_pMain = nullptr;

		m_seq = Seq::kSeqMain;

		m_hp = 0;
		m_maxHp = 0;
		m_shotSpeed = 0;
		m_damagePrevent = 0;

		for (int i = 0; i < kPowerupTypeNum; i++)
		{
			m_powerUp[i] = 0;
		}

		m_lastShot = 0;
		m_damageFrame = -1;

		m_level = 0;
		m_exp = 0;

		m_shotNum = 0;

		for (int i = 0; i < kPosLogNum; i++)
		{
			m_posLog[i] = m_pos;
		}
	}
	virtual ~Player() {}

	void init();
	void update();
	void draw();

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// ゲームクリア時にシーケンス変更
	void setSeq(Seq seq) { m_seq = seq; }

	// ダメージを受けるか
	bool isGetDamage();
	// ダメージを受ける処理
	void damage( int getDamage );

	int getHp() { return m_hp; }
	int getShotSpeed() { return m_shotSpeed; }

	// パワーアップ関連
	void addExp(int add);	// 経験値加算
	int getLevel();			// 現在のレベル取得
	int getNextLevelExp();	// 次のレベルになるのに必要な経験値
private:
	// define----------------------------
	static constexpr int kShotMax = 32;	// 1回の発射で出るショットの最大数

	// function----------------------------
	// ショットデータ設定
	void setShot( int level );
	
	// パワーアップを反映した情報を取得する
	int getShotDamage();
	float getShotScale();
	int getPlayerSpeed();
	int getShotInterval();

private:
	// variable----------------------------
	SceneMain* m_pMain;
	Seq m_seq;

	// キャラクター性能
	int m_hp;
	int m_maxHp;
	int m_shotSpeed;	// ショットの速度
	int m_damagePrevent;// 防御力

	// パワーアップ情報
	int m_powerUp[kPowerupTypeNum];


	// プレイ情報
	// ショットを撃ってからの経過フレーム数
	int m_lastShot;
	// ダメージ受けた後の無敵時間
	int m_damageFrame;

	// レベルアップ
	int m_level;
	int m_exp;

	// ショット情報
	int m_shotNum;
	ShotData m_shotData[kShotMax];

	// 演出
	Vec2 m_posLog[kPosLogNum];
};
