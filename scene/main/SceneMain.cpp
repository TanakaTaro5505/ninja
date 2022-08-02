#include "Game.h"
#include "SceneMain.h"

// �G���
static const int cEnemyHitDamage	= 10;		// �����������̃_���[�W
static const int cEnemyShotDamage	= 10;		// �V���b�g�ɓ����������̃_���[�W
static const int cEnemyShotWait		= 120;		// ������V���b�g�����܂ł̎���(�t���[��)

void SceneMain::init()
{
	m_endWait = -1;

	m_playerGraphic = LoadGraph("data/main/player.bmp");
	m_shotGraphic = LoadGraph("data/main/shot.bmp");
	m_enemyShotGraphic = LoadGraph("data/main/enemyShot.bmp");
	m_enemyGraphic = LoadGraph("data/main/enemy.bmp");

	m_player.createGraphic(Game::cScreenWidth / 2, Game::cScreenHeight / 2, m_playerGraphic);
	m_player.init();
	m_player.setMain( this );

	m_stage.init(this, 0);

	initBg();
}

void SceneMain::deleteGraph()
{
	DeleteGraph(m_playerGraphic);
	DeleteGraph(m_shotGraphic);
	DeleteGraph(m_enemyShotGraphic);
	DeleteGraph(m_enemyGraphic);
}

SceneBase* SceneMain::update()
{
	if (m_endWait >= 0)
	{
		m_endWait++;

		// �t�F�[�h�A�E�g���ďI��
		m_fadeBright -= Game::cFadeSpeedNormal;
		if (m_fadeBright <= 0)
		{
			m_fadeBright = 0;
			return (new SceneTitle);
		}
		return this;
	}

	m_fadeBright += Game::cFadeSpeedNormal;
	if (m_fadeBright >= 255)	m_fadeBright = 255;

	// �Q�[���I�[�o�[�ŏI���҂�
	if (m_player.getHp() <= 0)	return this;

	// �G�̐����Ȃ�
	m_stage.update();

	// �w�i���o
	updateBg();

	m_player.update();
	for (int i = 0; i < cShotMax; i++)
	{
		m_shot[i].update();
	}
	int enemyNum = 0;
	for (int i = 0; i < cEnemyMax; i++)
	{
		if (m_shot[i].isExist())	enemyNum++;
		m_enemy[i].update();
	}
	m_effect.update();

	// �Փ˔���
	bool isCol = false;
	for (int i = 0; i < cEnemyMax; i++)
	{
		// �v���C���[���G�ɂԂ�����
		if (m_player.isCol(&m_enemy[i]))
		{
			m_player.damage(m_enemy[i].getHitDamage());
		}
	}

	for (int j = 0; j < cShotMax; j++)
	{
		if (!m_shot[j].isExist())	continue;

		if (m_shot[j].isHitEnemy())
		{
			// �G�ɓ�����e
			for (int i = 0; i < cEnemyMax; i++)
			{
				if (!m_enemy[i].isExist())	continue;

				// �G�ɃV���b�g�����Ă�
				if (m_enemy[i].isCol(&m_shot[j]))
				{
					//	m_effect.create(static_cast<int>(m_enemy[i].getPos().x), static_cast<int>(m_enemy[i].getPos().y));
					m_shot[j].Hit();
					m_enemy[i].Hit(m_shot[j].getPower());
					// �|����
					if (!m_enemy[i].isExist())
					{
						m_player.addExp(5);
						m_effect.create(m_enemy[i].getPos().x, m_enemy[i].getPos().y);
					}
					break;
				}
			}
		}
		else
		{
			// �v���C���[�ɓ�����e
			if (m_player.isCol(&m_shot[j]))
			{
				m_shot[j].Hit();
				m_player.damage(m_shot[j].getPower());
			}
		}
	}
	
	// �v���C���[���S
	if (m_player.getHp() <= 0)
	{
		m_endWait = 256;
	}
	// �G�����ׂē|����
	if (m_stage.isEnd() && enemyNum <= 0)
	{
		m_endWait = 256;
	}
	return this;
}

void SceneMain::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	drawBg();
	for (int i = 0; i < cShotMax; i++)
	{
		m_shot[i].draw();
	}

	m_player.draw();
	for (int i = 0; i < cEnemyMax; i++)
	{
		m_enemy[i].draw();
	}
	m_effect.draw();
}

void SceneMain::initBg()
{
	for (int i = 0; i < cStarNum; i++)
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

void SceneMain::updateBg()
{
	for (int i = 0; i < cStarNum; i++)
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
	for (int i = 0; i < cStarNum; i++)
	{
		m_bgStar[i].draw();
	}
}

void SceneMain::createEnemy(VECTOR pos, int hp, Enemy::Type type)
{
	for (int i = 0; i < cEnemyMax; i++)
	{
		if (m_enemy[i].isExist())	continue;
		
		m_enemy[i].createGraphic(pos.x, pos.y, m_enemyGraphic);
		m_enemy[i].setMain(this);

		m_enemy[i].init(hp, type);
		m_enemy[i].setHitDamage(cEnemyHitDamage);
		m_enemy[i].setShotDamage(cEnemyShotDamage);
		m_enemy[i].setShotWait(cEnemyShotWait);
		break;
	}
}

Shot* SceneMain::createPlayerShot(VECTOR pos)
{
	for (int i = 0; i < cShotMax; i++)
	{
		if (m_shot[i].isExist())	continue;

		m_shot[i].createPlayerShot(pos, m_shotGraphic);
		return &(m_shot[i]);
	}
	return nullptr;
}

Shot* SceneMain::createEnemyShot(VECTOR pos)
{
	for (int j = 0; j < cShotMax; j++)
	{
		if (m_shot[j].isExist())	continue;
		m_shot[j].createEnemyShot(pos, m_enemyShotGraphic);
		return  &(m_shot[j]);
	}
	return nullptr;
}
