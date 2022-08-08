#include "Game.h"
#include "SceneMain.h"

// �G���
static const int cEnemyHitDamage	= 10;		// �����������̃_���[�W
static const int cEnemyShotDamage	= 10;		// �V���b�g�ɓ����������̃_���[�W
static const int cEnemyShotWait		= 120;		// ������V���b�g�����܂ł̎���(�t���[��)

void SceneMain::init()
{
	m_seq = Seq::kSeqMain;
	m_endWait = -1;

	m_playerGraphic = LoadGraph("data/main/player.bmp");
	m_shotGraphic = LoadGraph("data/main/shot.bmp");
	m_enemyShotGraphic = LoadGraph("data/main/enemyShot.bmp");
	m_enemyGraphic = LoadGraph("data/main/enemy.bmp");
	m_itemGraphic = LoadGraph("data/main/item.bmp");

	m_clearGraphic = LoadGraph("data/font/end.png");
	m_gameoverGraphic = LoadGraph("data/font/gameover.png");

	m_player.createGraphic(Game::cScreenWidth / 2, Game::cScreenHeight / 2, m_playerGraphic);
	m_player.init();
	m_player.setMain( this );

	m_stage.init(this, 0);

	initBg();
}

void SceneMain::deleteGraph()
{
	// �e�f�[�^�̍폜
	for (auto itr = m_shotList.begin(); itr != m_shotList.end();)		// �����ł�itr++���Ȃ�
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_shotList.erase(itr);
		}
	}
	// �G�f�[�^�̍폜
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end();)		// �����ł�itr++���Ȃ�
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_enemyList.erase(itr);
		}
	}
	// �A�C�e���f�[�^�̍폜
	for (auto itr = m_itemList.begin(); itr != m_itemList.end();)		// �����ł�itr++���Ȃ�
	{
		if ((*itr))
		{
			delete (*itr);
			itr = m_itemList.erase(itr);
		}
	}

	DeleteGraph(m_playerGraphic);
	DeleteGraph(m_shotGraphic);
	DeleteGraph(m_enemyShotGraphic);
	DeleteGraph(m_enemyGraphic);
	DeleteGraph(m_itemGraphic);

	DeleteGraph(m_clearGraphic);
	DeleteGraph(m_gameoverGraphic);
}

SceneBase* SceneMain::update()
{
	// List����s�v�ɂȂ������̂��폜����
	for (auto itr = m_shotList.begin(); itr != m_shotList.end();)		// �����ł�itr++���Ȃ�
	{
		if (!(*itr)->isExist())
		{
			delete (*itr);
			itr = m_shotList.erase(itr);
			continue;
		}
		itr++;
	}
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end();)		// �����ł�itr++���Ȃ�
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

//	DrawFormatString(0,0,GetColor(255,255,255), "�e�X�g:%6d", 100);

	int graphSizeX = 0;
	int graphSizeY = 0;
	switch (m_seq)
	{
	case Seq::kSeqStageClear:
		GetGraphSize(m_clearGraphic, &graphSizeX, &graphSizeY);
		DrawGraph((Game::cScreenWidth- graphSizeX)/2, (Game::cScreenHeight - graphSizeY) / 2, m_clearGraphic, 1);
		break;
	case Seq::kSeqGameover:
		GetGraphSize(m_gameoverGraphic, &graphSizeX, &graphSizeY);
		DrawGraph((Game::cScreenWidth - graphSizeX) / 2, (Game::cScreenHeight - graphSizeY) / 2, m_gameoverGraphic, 1);
		break;
	}
	
	// �f�o�b�O�\��
	DrawFormatString(0,  0, GetColor(255, 255, 255), "�G�̐�:%d", m_enemyList.size());
	DrawFormatString(0, 32, GetColor(255, 255, 255), "�V���b�g�̐�:%d", m_shotList.size());
	DrawFormatString(0, 64, GetColor(255, 255, 255), "�A�C�e���̐�:%d", m_itemList.size());
}

#if false
void SceneMain::createEnemy(VECTOR pos, int hp, Enemy::Type type)
{
	Enemy* pEnemy = new Enemy;
	pEnemy->createGraphic(pos.x, pos.y, m_enemyGraphic);
	pEnemy->setMain(this);

	pEnemy->init(hp, type);
	pEnemy->setHitDamage(cEnemyHitDamage);
	pEnemy->setShotDamage(cEnemyShotDamage);
	pEnemy->setShotWait(cEnemyShotWait);
	m_enemyList.push_back(pEnemy);
}
#else
void SceneMain::addEnemy(EnemyBase* pEnemy)
{
	m_enemyList.push_back(pEnemy);
}
#endif

Shot* SceneMain::createPlayerShot(VECTOR pos)
{
	Shot* pShot = new Shot;
	pShot->createPlayerShot(pos, m_shotGraphic);
	m_shotList.push_back(pShot);
	return pShot;
}

Shot* SceneMain::createEnemyShot(VECTOR pos)
{
	Shot* pShot = new Shot;
	pShot->createEnemyShot(pos, m_enemyShotGraphic);
	m_shotList.push_back(pShot);
	return pShot;
}

void SceneMain::createItem(VECTOR pos)
{
	Item* pItem = new Item;
	pItem->createGraphic(pos.x, pos.y, m_itemGraphic);
	m_itemList.push_back(pItem);
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

	// �Q�[���I�[�o�[�ŏI���҂�
	if (m_player.getHp() <= 0)	return this;

	// �G�̐����Ȃ�
	m_stage.update();

	// �w�i���o	
	updateBg();

	m_player.update();
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// �G�̏���
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	for (auto itr = m_itemList.begin(); itr != m_itemList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();

	// �Փ˔���
	bool isCol = false;
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
	{
		if (m_player.isCol((*itr)))
		{
			m_player.damage((*itr)->getHitDamage());
		}
	}

	// �A�C�e���擾
	for (auto itr = m_itemList.begin(); itr != m_itemList.end(); ++itr)
	{
		if (!(*itr)->isExist())	continue;
		// �v���C���[���G�ɂԂ�����
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
			// �G�ɓ�����e
			for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
			{
				EnemyBase* pEnemy = (*itr);
				if (!pEnemy->isExist())	continue;
				// �G�ɃV���b�g�����Ă�
				if (pEnemy->isCol(pShot))
				{
					//	m_effect.create(static_cast<int>(m_enemy[i].getPos().x), static_cast<int>(m_enemy[i].getPos().y));
					pShot->hit();
					pEnemy->hit(pShot->getPower());
					// �|����
					if (!pEnemy->isExist())
					{
						//	m_player.addExp(5);
						m_effect.create(pEnemy->getPos().x, pEnemy->getPos().y);
						createItem(pEnemy->getPos());
					}
					break;
				}
			}
		}
		else
		{
			// �v���C���[�ɓ�����e
			if (m_player.isCol(pShot))
			{
				pShot->hit();
				m_player.damage(pShot->getPower());
			}
		}
	}
	// �v���C���[���S
	if (m_player.getHp() <= 0)
	{
		m_endWait = 0;
		m_effect.create(m_player.getPos().x, m_player.getPos().y);
		m_seq = Seq::kSeqGameover;
	}
	// �X�e�[�W�I������
	if (m_stage.isEnd())
	{
		// �{�X���c���Ă���΂܂��I���Ȃ�
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
			// �c���Ă�U�R�G�A�G�̒e������
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
			m_seq = Seq::kSeqStageClear;
		}
	}
	return this;
}

SceneBase* SceneMain::updateStageClear()
{
	if (m_endWait > 0)
	{
		// �t�F�[�h�A�E�g���ďI��
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneTitle);
		}
		return this;
	}

	// �w�i���o
	updateBg();
	// �v���C���[�͑���s�@�O���ɋ삯������
//	m_player.update();
	VECTOR pos = m_player.getPos();
	pos.x += 8.0f;
	m_player.setPos(pos);
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// �G�̏���
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();


	// �{�^���҂�
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
	if (m_endWait > 0)
	{
		// �t�F�[�h�A�E�g���ďI��
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneTitle);
		}
		return this;
	}

	// �w�i���o
	updateBg();
	for (auto itr = m_shotList.begin(); itr != m_shotList.end(); itr++)
	{
		(*itr)->update();
	}
	// �G�̏���
	for (auto itr = m_enemyList.begin(); itr != m_enemyList.end(); itr++)
	{
		(*itr)->update();
	}
	m_effect.update();


	// �{�^���҂�
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