#include "Game.h"
#include "SceneMain.h"

// レベルアップしたときに何が上がったかを表示するフレーム数
static constexpr int kLevelupTextDispFrame = 60 * 3;

static const char* const kGraphicFilePath[SceneMain::kGraphicData_Kind] =
{
	"data/main/player.bmp",		// kGraphicData_Player,
	"data/main/shot.bmp",		// kGraphicData_Shot,
	"data/main/enemy.bmp",		// kGraphicData_Enemy,
	"data/main/enemyShot.bmp",	// kGraphicData_EnemyShot,
	"data/main/item.bmp",		// kGraphicData_Item,

	// 文字系
	"data/font/levelup.png",	// kGraphicData_LevelUp,
	"data/font/end.png",		// kGraphicData_Clear,
	"data/font/gameover.png",	// kGraphicData_Gameover,
};

void SceneMain::init()
{
	m_seq = Seq::kSeqMain;
	m_frameCount = 0;
	m_endWait = -1;

	for (int i = 0; i < kGraphicData_Kind; i++)
	{
		m_graphicHandle[i] = LoadGraph(kGraphicFilePath[i]);
	}

	m_player.createGraphic(Game::cScreenWidth / 2, Game::cScreenHeight / 2, m_graphicHandle[kGraphicData_Player]);
	m_player.init();
	m_player.setMain( this );

	m_stage.init(this, 0);

	initBg();
}

void SceneMain::deleteGraph()
{
	// 弾データの削除
	for (auto itr = m_shotList.begin(); itr != m_shotList.end();)		// ここではitr++しない
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_shotList.erase(itr);
		}
	}
	// 敵データの削除
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end();)		// ここではitr++しない
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_enemyList.erase(itr);
		}
	}
	// アイテムデータの削除
	for (auto itr = m_itemList.begin(); itr != m_itemList.end();)		// ここではitr++しない
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_itemList.erase(itr);
		}
	}

	for (int i = 0; i < kGraphicData_Kind; i++)
	{
		DeleteGraph(m_graphicHandle[i]);
	}
}

SceneBase* SceneMain::update()
{
	// Listから不要になったものを削除する
	for (auto itr = m_shotList.begin(); itr != m_shotList.end();)		// ここではitr++しない
	{
		if (!(*itr)->isExist())
		{
			delete (*itr);
			itr = m_shotList.erase(itr);
			continue;
		}
		itr++;
	}
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end();)		// ここではitr++しない
	{
		if (!(*itr)->isExist())
		{
			delete (*itr);
			itr = m_enemyList.erase(itr);
			continue;
		}
		itr++;
	}
	for (auto itr = m_itemList.begin(); itr != m_itemList.end();)
	{
		if (!(*itr)->isExist())
		{
			delete (*itr);
			itr = m_itemList.erase(itr);
			continue;
		}
		itr++;
	}

	// 共通演出
	m_levelupDispFrame--;
	m_levelUpPos.y -= 8.0f;

	switch (m_seq)
	{
	case Seq::kSeqMain:
		return updateMain();
	case Seq::kSeqStageClear:
		return updateStageClear();
	case Seq::kSeqGameover:
		return updateGameover();
	}
	return this;
}

void SceneMain::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	drawBg();
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); ++itr)
	{
		(*itr)->draw();
	}
	for (auto itr = m_itemList.begin(); itr != m_itemList.end(); ++itr)
	{
		(*itr)->draw();
	}

	m_player.draw();
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
	{
		(*itr)->draw();
	}
	m_effect.draw();

	if (m_levelupDispFrame >= 0)
	{
		DrawGraphF(m_levelUpPos.x, m_levelUpPos.y, m_graphicHandle[kGraphicData_LevelUp], 1);
		DrawString(32, 480, m_pLevelupText, GetColor(255, 255, 255));
	}

	int graphSizeX = 0;
	int graphSizeY = 0;
	int blend = m_frameCount*2;
	if (blend > 255)	blend = 255;
	switch (m_seq)
	{
	case Seq::kSeqStageClear:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		GetGraphSize(m_graphicHandle[kGraphicData_Clear], &graphSizeX, &graphSizeY);
		DrawGraph((Game::cScreenWidth- graphSizeX)/2, (Game::cScreenHeight - graphSizeY) / 2, m_graphicHandle[kGraphicData_Clear], 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case Seq::kSeqGameover:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		GetGraphSize(m_graphicHandle[kGraphicData_Gameover], &graphSizeX, &graphSizeY);
		DrawGraph((Game::cScreenWidth - graphSizeX) / 2, (Game::cScreenHeight - graphSizeY) / 2, m_graphicHandle[kGraphicData_Gameover], 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
	
#if false
	// デバッグ表示
	DrawFormatString(0,  0, GetColor(255, 255, 255), "敵の数:%d", m_enemyList.size());
	DrawFormatString(0, 32, GetColor(255, 255, 255), "ショットの数:%d", m_shotList.size());
	DrawFormatString(0, 64, GetColor(255, 255, 255), "アイテムの数:%d", m_itemList.size());
#endif
}

void SceneMain::addEnemy(EnemyBase* pEnemy)
{
	m_enemyList.push_back(pEnemy);
}

Shot* SceneMain::createPlayerShot(VECTOR pos)
{
	Shot* pShot = new Shot;
	pShot->createPlayerShot(pos, m_graphicHandle[kGraphicData_Shot]);
	m_shotList.push_back(pShot);
	return pShot;
}

Shot* SceneMain::createEnemyShot(VECTOR pos)
{
	Shot* pShot = new Shot;
	pShot->createEnemyShot(pos, m_graphicHandle[kGraphicData_EnemyShot]);
	m_shotList.push_back(pShot);
	return pShot;
}

void SceneMain::createDeadEffect(VECTOR pos)
{
	m_effect.create(pos.x, pos.y);
}

void SceneMain::createItem(VECTOR pos)
{
	Item* pItem = new Item;
	pItem->createGraphic(pos.x, pos.y, m_graphicHandle[kGraphicData_Item]);
	m_itemList.push_back(pItem);
}

void SceneMain::setLevelup(VECTOR pos, const char* text)
{
	// プレイヤー位置に演出表示
	m_levelUpPos.x = pos.x;
	m_levelUpPos.y = pos.y;

	// レベルが上がった時のパワーアップ内容
	m_pLevelupText = text;
	m_levelupDispFrame = kLevelupTextDispFrame;
}

void SceneMain::initBg()
{
	for (int i = 0; i < kStarNum; i++)
	{
		float posX = static_cast<float>(GetRand(Game::cScreenWidth));
		float posY = static_cast<float>(GetRand(Game::cScreenHeight));

		int colorElem = GetRand(128);

		m_bgStar[i].create(posX, posY, 1.5f, GetColor(colorElem, colorElem, colorElem));

		float speed = static_cast<float>(GetRand(64)) / 10.0f;
		VECTOR vec;
		vec.x = -speed;
		vec.y = 0.0f;
		m_bgStar[i].setVec(vec);
	}
}

SceneBase* SceneMain::updateMain()
{
	m_fadeBright += Game::cFadeSpeedNormal;
	if (m_fadeBright >= 255)	m_fadeBright = 255;

	// ゲームオーバーで終了待ち
	if (m_player.getHp() <= 0)	return this;

	// 敵の生成など
	m_stage.update();

	// 背景演出	
	updateBg();

	m_player.update();
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// 敵の処理
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	for (auto itr = m_itemList.begin(); itr != m_itemList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();

	// 衝突判定
	if (m_player.isGetDamage())
	{
		for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
		{
			if (m_player.isCol((*itr)))
			{
				m_player.damage((*itr)->getHitDamage());
			}
		}
	}

	// アイテム取得
	for (auto itr = m_itemList.begin(); itr != m_itemList.end(); ++itr)
	{
		if (!(*itr)->isExist())	continue;
		// プレイヤーが敵にぶつかった
		if (m_player.isCol((*itr)))
		{
			(*itr)->erase();
			m_player.addExp(5);
		}
	}

	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		Shot* pShot = (*itr);

		if (!pShot->isExist())	continue;

		if (pShot->isHitEnemy())
		{
			// 敵に当たる弾
			for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
			{
				EnemyBase* pEnemy = (*itr);
				if (!pEnemy->isExist())	continue;
				// 敵にショットをあてた
				if (pEnemy->isCol(pShot))
				{
					//	m_effect.create(static_cast<int>(m_enemy[i].getPos().x), static_cast<int>(m_enemy[i].getPos().y));
					pShot->hit();
					pEnemy->hit(pShot->getPower());

					break;
				}
			}
		}
		else
		{
			// プレイヤーに当たる弾
			if (m_player.isGetDamage() && m_player.isCol(pShot))
			{
				pShot->hit();
				m_player.damage(pShot->getPower());
			}
		}
	}
	// プレイヤー死亡
	if (m_player.getHp() <= 0)
	{
		m_player.setSeq(Player::Seq::kSeqGameOver);
		m_endWait = 0;
		m_effect.create(m_player.getPos().x, m_player.getPos().y);
		m_seq = Seq::kSeqGameover;
		m_frameCount = 0;
	}
	// ステージ終了処理
	if (m_stage.isEnd())
	{
		// ボスが残っていればまだ終わらない
		bool isEnd = true;
		for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
		{
			if (!(*itr)->isExist())	continue;
			if ((*itr)->isBoss())
			{
				isEnd = false;
			}
		}

		if (isEnd)
		{
			// 残ってるザコ敵、敵の弾を消す
			for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
			{
				if (!(*itr)->isExist())	continue;

				(*itr)->erase();
				m_effect.create((*itr)->getPos().x, (*itr)->getPos().y);
			}
			for (auto itr = m_shotList.begin(); itr != m_shotList.end(); ++itr)
			{
				if (!(*itr)->isExist())	continue;

				if (!(*itr)->isHitEnemy())
				{
					(*itr)->erase();
				}
			}
			m_endWait = 0;
			m_player.setSeq(Player::Seq::kSeqGameClear);
			m_seq = Seq::kSeqStageClear;
			m_frameCount = 0;
		}
	}

	return this;
}

SceneBase* SceneMain::updateStageClear()
{
	m_frameCount++;

	if (m_endWait > 0)
	{
		// フェードアウトして終了
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneTitle);
		}
		return this;
	}

	// 背景演出
	updateBg();
	
	m_player.update();

	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// 敵の処理
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();


	// ボタン待ち
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if (m_endWait == 0)
		{
			m_endWait = 1;
		}
	}

	return this;
}

SceneBase* SceneMain::updateGameover()
{
	m_frameCount++;

	if (m_endWait > 0)
	{
		// フェードアウトして終了
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneTitle);
		}
		return this;
	}

	// 背景演出
	updateBg();
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// 敵の処理
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();


	// ボタン待ち
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if (m_endWait == 0)
		{
			m_endWait = 1;
		}
	}

	return this;
}

void SceneMain::updateBg()
{
	for (int i = 0; i < kStarNum; i++)
	{
		m_bgStar[i].update();
		if (m_bgStar[i].getPos().x < 0.0f - 2.0f)
		{
			float posX = static_cast<float>(Game::cScreenWidth + 2);
			float posY = static_cast<float>(GetRand(Game::cScreenHeight));
			VECTOR pos;
			pos.x = posX;
			pos.y = posY;
			m_bgStar[i].setPos(pos);
		}
	}
}

void SceneMain::drawBg()
{
	for (int i = 0; i < kStarNum; i++)
	{
		m_bgStar[i].draw();
	}
}