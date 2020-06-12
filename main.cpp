#include <SFML/Graphics.hpp>  //����ͼ��
#include <time.h>  //����ʱ��
#include <SFML/Audio.hpp>  //��������
#include<conio.h>
#include<stdio.h>
#include<cstdlib> 
using namespace sf;
//1.����SFML����
//2.������
//3.���ɷ���
//3.1 ����˹����ı�ʾ
const float SPEED_NORMAL = 0.5;
const float SPEED_QUICK = 0.05;
float delay = 0.5;
const float SPEED_NORMAL1 = 0.5;
const float SPEED_QUICK1 = 0.05;
float delay1 = 0.5;
int blocks[7][4] = {
	{1,3,5,7},//1����
	{2,4,5,7},//����1��
	{3,5,4,6},//����2��
	{3,5,4,7},//T
	{2,3,5,7},//L
	{3,5,7,6},//J
	{2,3,4,5}//��
};
const int ROW_COUNT = 21;//��
const int COL_COUNT = 12;//��
const int ROW_COUNT1 = 21;
const int COL_COUNT1 = 24;
int table[ROW_COUNT][COL_COUNT] = {0};  //��table[i][j]==0 Ϊ�հף�����Ϊ���飬��ȷ������ɫ
int table1[ROW_COUNT1][COL_COUNT1] = { 0 };  //��table[i][j]==0 Ϊ�հף�����Ϊ���飬��ȷ������ɫ
int blockIndex; //��ʾ��ǰ���������
int blockIndex1;  //��ʾ��ǰ���������
struct Point
{
	int x;
	int y;
}curBlock[4], BakBlock[4],curBlock1[4], BakBlock1[4];
//����
Font font;
Text textScore;
Text textScore1;
int score = 0;
int score1 = 0;
bool check()  //��鷽��ĺϷ���
{
	for (int i = 0; i < 4; i++)
	{
		if (curBlock[i].x < 0 || curBlock[i].x >= COL_COUNT || curBlock[i].y >= ROW_COUNT || table[curBlock[i].y][curBlock[i].x])
		{
			return false;
		}
	}
	return true;
}
bool check1()  //��鷽��ĺϷ���
{
	for (int i = 0; i < 4; i++)
	{
		if (curBlock1[i].x < 12 || curBlock1[i].x >= COL_COUNT1 || curBlock1[i].y >= ROW_COUNT1 || table1[curBlock1[i].y][curBlock1[i].x])
		{
			return false;
		}
	}
	return true;
}
void moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		BakBlock[i] = curBlock[i];
		curBlock[i].x += offset;
	}
	if (!check())
	{
		for (int i = 0; i < 4; i++)
		{
			curBlock[i] = BakBlock[i];
		}
	}
}
void moveLeftRight1(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		BakBlock1[i] = curBlock1[i];
		curBlock1[i].x += offset;
	}
	if (!check1())
	{
		for (int i = 0; i < 4; i++)
		{
			curBlock1[i] = BakBlock1[i];
		}
	}
}
void doRotate()  //��ת
{
	if (blockIndex == 7)
	{
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		BakBlock[i] = curBlock[i];
	}

	Point p = curBlock[1];

	for (int i = 0; i < 4; i++)
	{
		Point tmp = curBlock[i];
		curBlock[i].x = p.x - tmp.y + p.y;
		curBlock[i].y = tmp.x - p.x + p.y;
	}
	//���Ϸ���
	if (!check())
	{
		for (int i = 0; i < 4; i++)
		{
			curBlock[i] = BakBlock[i];
		}
	}
}
void doRotate1()  //��ת
{
	if (blockIndex1 == 7)
	{
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		BakBlock1[i] = curBlock1[i];
	}

	Point p = curBlock1[1];

	for (int i = 0; i < 4; i++)
	{
		Point tmp = curBlock1[i];
		curBlock1[i].x = p.x - tmp.y + p.y;
		curBlock1[i].y = tmp.x - p.x + p.y;
	}
	//���Ϸ���
	if (!check1())
	{
		for (int i = 0; i < 4; i++)
		{
			curBlock1[i] = BakBlock1[i];
		}
	}
}
void newBlock()
{
	//�����ȡһ��ֵ��1~7��
	blockIndex=1+rand()%7;
	int n = blockIndex - 1;
	for (int i = 0; i < 4; i++)
	{
		curBlock[i].x = blocks[n][i] % 2+2;
		curBlock[i].y = blocks[n][i] / 2;

	}
}
void newBlock1()
{
	//�����ȡһ��ֵ��1~7��
	blockIndex1 = 1 + rand() % 7;
	int n = blockIndex1 - 1;
	for (int i = 0; i < 4; i++)
	{
		curBlock1[i].x = blocks[n][i] % 2+19;
		curBlock1[i].y = blocks[n][i] / 2;

	}


}
void drawBlocks(Sprite *spriteBlock,RenderWindow *window)
{
	//�Ѿ����䵽�ײ��ķ���
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COL_COUNT; j++)
		{
			if (table[i][j]!=0)
			{
				//��С����
				//��Ҫ��ʹ��sprite��ʾ�����ķ���ͼƬ
				spriteBlock->setTextureRect(IntRect(table[i][j] * 42, 0, 42, 42));
				spriteBlock->setPosition(j * 42, i * 42);
				//����ƫ����
				spriteBlock->move(110,152);
				window->draw(*spriteBlock);
			}

		}
	}
	//���ڽ�������еķ��飨��ǰ���飩
	for (int i = 0; i < 4; i++)
	{
		spriteBlock->setTextureRect(IntRect(blockIndex * 42, 0, 42, 42));
		spriteBlock->setPosition(curBlock[i].x* 42, curBlock[i].y* 42);
		spriteBlock->move(110,152);
		window->draw(*spriteBlock);
	}
}
void drawBlocks1(Sprite* spriteBlock, RenderWindow* window)
{
	//�Ѿ����䵽�ײ��ķ���
	for (int i = 0; i < ROW_COUNT1; i++)
	{
		for (int j = 11; j < COL_COUNT1; j++)
		{
			if (table1[i][j] != 0)
			{
				//��С����
				//��Ҫ��ʹ��sprite��ʾ�����ķ���ͼƬ
				spriteBlock->setTextureRect(IntRect(table1[i][j] * 42, 0, 42, 42));
				spriteBlock->setPosition(j * 42, i * 42);
				//����ƫ����
				spriteBlock->move(110, 152);
				window->draw(*spriteBlock);
			}

		}
	}
	//���ڽ�������еķ��飨��ǰ���飩
	for (int i = 0; i < 4; i++)
	{
		spriteBlock->setTextureRect(IntRect(blockIndex1 * 42, 0, 42, 42));
		spriteBlock->setPosition(curBlock1[i].x * 42, curBlock1[i].y * 42);
		spriteBlock->move(110, 152);
		window->draw(*spriteBlock);
	}
}
void drop()
{
	for (int i = 0; i < 4; i++)
	{
		BakBlock[i] = curBlock[i];
		curBlock[i].y += 1;
	}

	if (check() == false)
	{
		//�̻�
		for (int i = 0; i < 4; i++)
		{
			table[BakBlock[i].y][BakBlock[i].x] = blockIndex;
		}
		
		//����һ���·���
		newBlock();
	}
}
void drop1()
{
	for (int i = 0; i < 4; i++)
	{
		BakBlock1[i] = curBlock1[i];
		curBlock1[i].y += 1;
	}

	if (check1() == false)
	{
		//�̻�
		for (int i = 0; i < 4; i++)
		{
			table1[BakBlock1[i].y][BakBlock1[i].x] = blockIndex1;
		}

		//����һ���·���
		newBlock1();
	}
}
void clearLine()
{
	int k = ROW_COUNT - 1;
	for (int i = ROW_COUNT - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < COL_COUNT; j++)
		{
			if (table[i][j])
			{
				count++;
			}
			table[k][j] = table[i][j];
		}
		if (count < COL_COUNT)
		{
			k--;
		}
		else
			score += 10;
			
	}
	char tmp[16];
	sprintf_s(tmp, "%d", score);
	textScore.setString(tmp);
}
void clearLine1()
{
	int k = ROW_COUNT1 - 1;
	for (int i = ROW_COUNT1 - 1; i > 0; i--)
	{
		int count = 12;
		for (int j = 11; j < COL_COUNT1; j++)
		{
			if (table1[i][j])
			{
				count++;
			}
			table1[k][j] = table1[i][j];
		}
		if (count < COL_COUNT1)
		{
			k--;
		}
		else
			score1 += 10;

	}
	char tmp[16];
	sprintf_s(tmp, "%d", score1);
	textScore1.setString(tmp);
}
void initScore()
{
	if (!font.loadFromFile("Sansation.ttf")) {
		exit(1);
	}
	textScore.setFont(font); // font is a sf::Font
	textScore.setCharacterSize(30);// set the character size
	textScore.setFillColor(sf::Color::Black); // set the color
	textScore.setStyle(sf::Text::Bold); // set the text style
	textScore.setPosition(1500, 200);
	textScore.setString("0");
}
void initScore1()
{
	if (!font.loadFromFile("Sansation.ttf")) {
		exit(1);
	}
	textScore1.setFont(font); // font is a sf::Font
	textScore1.setCharacterSize(30);// set the character size
	textScore1.setFillColor(sf::Color::Blue); // set the color
	textScore1.setStyle(sf::Text::Bold); // set the text style
	textScore1.setPosition(1500, 400);
	textScore1.setString("0");
}
void keyEvent(RenderWindow* window)
{
		bool rotate = false;
		bool rotate1 = false;
		int dx = 0;
		int dx1 = 0;
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}
			if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case Keyboard::W:
					rotate1 = true;
					if (rotate1)
					{
						doRotate1();
					}
					break;
				case Keyboard::Up:
					rotate = true;
					if (rotate)
					{
						doRotate();
					}
					break;
				case Keyboard::A:
					dx1 = -1;
					if (dx1 != 0)
					{
						moveLeftRight1(dx1);
					}
					break;
				case Keyboard::Left:
					dx = -1;
					if (dx != 0)
					{
						moveLeftRight(dx);
					}
					break;
				case Keyboard::D:
					dx1 = 1;
					if (dx1 != 0)
					{
						moveLeftRight1(dx1);
					}
					break;
				case Keyboard::Right:
					dx = 1;
					if (dx != 0)
					{
						moveLeftRight(dx);
					}
					break;
				case Keyboard::S:
					delay1 = SPEED_QUICK1;
					break;
				case Keyboard::Down:
					delay = SPEED_QUICK;
					break;
				default:
					break;
				}
			}																			
		}
}
//void keyEvent1(RenderWindow* window)
//{
//	bool rotate = false;
//	int dx = 0;
//	Event e;
//	while (window->pollEvent(e))
//	{
//		if (e.type == Event::Closed)
//		{
//			window->close();
//		}
//		if (e.type == Event::KeyPressed)
//		{
//			switch (e.key.code)
//			{
//			case Keyboard::W:
//				rotate = true;
//				break;
//			case Keyboard::A:
//				dx = -1;
//				break;
//			case Keyboard::D:
//				dx = 1;
//				break;
//			default:
//				break;
//			}
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::S))
//		{
//			delay1 = SPEED_QUICK1;
//		}
//
//
//		if (dx != 0)
//		{
//			moveLeftRight1(dx);
//		}
//
//		if (rotate)
//		{
//			doRotate1();
//		}
//	}
//}
int main()
{
	srand(time(0));   //�������
	//��������
	Music music;
	if (!music.openFromFile("beijing.wav"))
	{
		return -1;
	}
	music.setLoop(true);
	music.play();

	//��Ϸ����
	//1.������Ϸ����
	//1.1 ����ͼƬ
	RenderWindow window(
		VideoMode(2000, 1125),//ͼƬ��С
		"woluosi");  //���ڱ���
	//2.���뱳��
	Texture t1;  //��ͼƬ�ļ����ص��ڴ�
	t1.loadFromFile("image/image.jpg");
	Sprite spriteBg(t1);  
	Texture t2;
	t2.loadFromFile("image/tiles.png");
	Sprite spriteBlock(t2);
	Texture t22;
	t22.loadFromFile("image/tiles.png");
	Sprite spriteBlock1(t22);
	//�߿�
	Texture t3;
	t3.loadFromFile("image/2.png");
	Sprite spriteFrame(t3);
	initScore();
	initScore1();
	window.draw(spriteBg);
	window.display();  //��ʾ����
	//����һ������
	newBlock();
	newBlock1();
	//��ʱ��
	Clock clock,clock1;
	float timer = 0;
	float timer1 = 0;
	//������Ϸѭ��
	while (window.isOpen())  //������ڻ��ڴ�״̬�ͽ���ѭ��
	{
		//��ȡ��clock������������֮�󣬵����ڵ�ʱ��
		float time = clock.getElapsedTime().asSeconds();
		float time1 = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		clock1.restart();
		timer1 += time1;
		keyEvent(&window);
		if (timer1 > delay) {
			drop1();
			timer1 = 0;
		}
		clearLine1();
		delay1 = SPEED_NORMAL1;
		/*keyEvent(&window);*/
		if (timer > delay)
		{
			//����
			drop();//�½�һλλ��
			
			timer = 0;
		}
		clearLine();  //����һ��
		delay = SPEED_NORMAL;

		
		//������Ϸ
		window.draw(spriteBg);
	
		window.draw(spriteFrame);
		//1.���Ʒ���
		drawBlocks(&spriteBlock,&window);
		drawBlocks1(&spriteBlock1,&window);

		window.draw(textScore);
		window.draw(textScore1);
		window.display();  //��ʾ����
	}
	
	if (score > score1)
		printf("play1 win!!!\n");
	if (score == score1)
		printf("ƽ��\n");
	if (score < score1)
		printf("play2 win!!!\n");

	system("pause");
	return 0;
}