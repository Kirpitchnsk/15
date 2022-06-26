#include <SFML/Graphics.hpp>//����������� ���������� SFML
#include <SFML/Audio.hpp>//��� �����
#include <time.h>//��� �������
const int Field_SIZE_pl = 4;//����� ������ � ����� � ������
const int ARRAY_OF_NUMBER = Field_SIZE_pl * Field_SIZE_pl;//���������� ��������� � ������� � �������
const int PLAYGROUND_SIZE = 480;//������ ������� �������� � �������� � ����� � ������
const int NUMBERFIELD = 120;//������ ������ � ��������
//�������� ������������ �����������
bool FinishCheck(int * elements, int empty)
{
	for (int i = 0; i < ARRAY_OF_NUMBER; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1 && empty != 16) return false;
	}
	return true;
}
//������ ����������� ��� �������
enum Direction
{
	LEFT = 0,RIGHT = 1,UP = 2,DOWN = 3,STOP = 4
};
//���������� ������� ������, ������ ����
void JustStart(int* elements, bool& solved, int& empty, sf::Sprite* s)
{
	for (int i = 0; i < ARRAY_OF_NUMBER; i++)
	{
		elements[i] = i + 1;
	}
	empty = ARRAY_OF_NUMBER - 1;
	elements[empty] = 0;
	solved = true;
}
//�������� ������ �� �����������
void Move(Direction dir, int* elements, bool & solved, int &empty, sf::Sprite *s)
{
	int column = empty % Field_SIZE_pl;
	int stroke = empty / Field_SIZE_pl;

	int move = -1;
	if (column < Field_SIZE_pl - 1 && dir == Direction::LEFT) move = empty + 1;
	if (column > 0 && dir == Direction::RIGHT) move = empty - 1;
	if (stroke < Field_SIZE_pl - 1 && dir == Direction::UP) move = empty + Field_SIZE_pl;
	if (stroke > 0 && dir == Direction::DOWN) move = empty - Field_SIZE_pl;
	if (dir == Direction::STOP) move = -1;

	if (empty >= 0 && move >= 0)
	{
		int temp = elements[empty];
		elements[empty] = elements[move];
		s[empty] = s[move];
		elements[move] = temp;
		empty = move;
	}
	solved = FinishCheck(elements,empty);
}
int main()
{
	double ctartclock = clock() / 1000;//�������� ������ �������
	int elements[ARRAY_OF_NUMBER];//������ � �������
	bool solved = true;//�������� ����������� �����������
	int empty = ARRAY_OF_NUMBER - 1;// ������ ������� ����
	int n = 0;//���������� ��� ���������� ������� � ����������
	int koeffincial = 0;//����������� �������������
	int move_counter = 0;//������� ������������
	int topic = 0;//����
	double gametime = 0;//����������� ����� ����
	double lastgametime = 0;
	bool gamestart = false;//�������� �������� �� ����

	//������� ���� �������� 600 �� 600, 60 ������ � �������
	sf::RenderWindow window(sf::VideoMode(600, 600), "15");
	window.setFramerateLimit(60);

    //������ ������� �������� �� �� ����� � ������
	sf::Texture t;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//�����
	sf::Font font;
	font.loadFromFile("Cyrillic_Old.ttf");

	//��������� ���� ��� ������� � ������� �������, ��� ���������
	srand(time(NULL));
	topic = rand() % 5 + 1;
	sf::Text text4("", font, 10);
	switch (topic)
	{
	case 1: 
	{
		t.loadFromFile("image.jpg");
		buffer.loadFromFile("music.ogg");
		text4.setString("Topic: 9th of May - Victory day");
		text4.setFillColor(sf::Color::Red);
		text4.setPosition(50.f, 20.f);
		break;
	}
	case 2:
	{
		t.loadFromFile("image2.png");
		buffer.loadFromFile("music2.ogg");
		text4.setString("Topic: Kurth Cobain (Nirvana)");
		text4.setFillColor(sf::Color::Cyan);
		text4.setPosition(50.f, 20.f);
		break;
	}
	case 3:
	{
		t.loadFromFile("image3.jpg");
		buffer.loadFromFile("music3.ogg");
		text4.setString("Topic: My home budgie");
		text4.setFillColor(sf::Color::Green);
		text4.setPosition(50.f, 20.f);
		break;
	}
	case 4:
	{
		t.loadFromFile("image4.jpg");
		buffer.loadFromFile("music4.ogg");
		text4.setString("Topic: AC/DC music band");
		text4.setFillColor(sf::Color::Red);
		text4.setPosition(50.f, 20.f);
		break;
	}
	default:
	{
		t.loadFromFile("image5.jpg");
		buffer.loadFromFile("music5.ogg");
		text4.setString("Topic: Star Wars");
		text4.setFillColor(sf::Color::White);
		text4.setPosition(50.f, 20.f);
		break;
	}
	}
	//��������� ����������� �� �������
	sf::Sprite s[17];
	for (int i = 0; i < Field_SIZE_pl; i++)
	{
		for (int j = 0; j < Field_SIZE_pl; j++)
		{
			s[n].setTexture(t);
			s[n].setTextureRect(sf::IntRect(j* NUMBERFIELD, i* NUMBERFIELD, NUMBERFIELD, NUMBERFIELD));
			s[n].setPosition(j * NUMBERFIELD + 50.f, i * NUMBERFIELD + 50.f);
			n++;
		}
	}

	//���������� ������ � �������� ��
	sound.setBuffer(buffer);
	sound.setVolume(100);
	sound.play();
	
	//����� � �����
	sf::Text text("Course Progect Programming, 15 - Fifteen ", font, 20);
	text.setFillColor(sf::Color::White);
	text.setPosition(50.f, 0.f);

	//����� ��� �������� �����
	sf::Text text3("", font, 20);
	text3.setFillColor(sf::Color::White);
	text3.setPosition(50.f, 550.f);

	//����� ��� ������ � ������ ������
	sf::Text text5("You win=) Enter - start new game", font, 20);
	text5.setFillColor(sf::Color::Red);
	text5.setPosition(50.f, 0.f);

	//����� ��� ������ ����������� ����
	sf::Text text6("", font, 20);
	text6.setFillColor(sf::Color::Red);
	text6.setPosition(50.f, 20.f);

	//������ �������
	sf::Event event; 

	//�������� ���� ����� ������� �� ����� �������� �����������
	JustStart(elements, solved, empty,s);

	sf::Clock clocke;
	
	//���� ���� �������
	while (window.isOpen())
	{

		// ������� ����� ������� ��� �������� � ����
		sf::Text text2("", font, 52);
		sf::Color color = sf::Color(200, 100, 200);

		// ����� ��� ������ ������� �� �����
		sf::Text text_time("", font, 20);
		text_time.setPosition(350.f, 550.f);

		//������� ����� ���������
		sf::Time time = clocke.getElapsedTime();

		// ������� �������� �������� ���� � ����� ������
		sf::RectangleShape shape(sf::Vector2f(PLAYGROUND_SIZE, PLAYGROUND_SIZE));
		sf::RectangleShape pl(sf::Vector2f(NUMBERFIELD-2, NUMBERFIELD-2));

		//���� �������
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close(); //���� ���� ������� �� ��� ���������
			if (event.type == sf::Event::KeyPressed)
			{
				//���� ����������� ������ �� �� �� ������ �� ���������
				if (solved)
				{
					if (event.key.code == sf::Keyboard::Left) Move(Direction::STOP, elements, solved, empty, s);
					if (event.key.code == sf::Keyboard::Right) Move(Direction::STOP, elements, solved, empty,s);
					if (event.key.code == sf::Keyboard::Up) Move(Direction::STOP, elements, solved, empty, s);
					if (event.key.code == sf::Keyboard::Down) Move(Direction::STOP, elements, solved, empty,s);
				}
				//���� �� ��� ��� ������� �� ������� �������� �������� ������
				else 
				{
					if (event.key.code == sf::Keyboard::Left) Move(Direction::LEFT, elements, solved, empty, s);
					if (event.key.code == sf::Keyboard::Right) Move(Direction::RIGHT, elements, solved, empty, s);
					if (event.key.code == sf::Keyboard::Up) Move(Direction::UP, elements, solved, empty,s);
					if (event.key.code == sf::Keyboard::Down) Move(Direction::DOWN, elements, solved, empty, s);
					move_counter++;
				}
				if (event.key.code == sf::Keyboard::Escape) window.close(); //������� ����
				//������������ ����������� � ������ ������� enter
				if (event.key.code == sf::Keyboard::Enter)
				{
					window.clear();
					JustStart(elements, solved, empty, s);
					gamestart = true;
					clocke.restart();
					move_counter = 0;
					koeffincial = 100;
				}
			}
		}
		window.clear();

		//������������ �����������
		koeffincial--;
		if (koeffincial > 0)
		{
			int random = rand() % 4;
			Move((Direction)(random), elements, solved, empty, s);
		}

		//�������������� �������� ���� � ��� ���������
		shape.setOutlineThickness(4.f);
		shape.setOutlineColor(color);
		shape.setPosition(50.f,50.f);
		shape.setFillColor(sf::Color::Transparent);
		window.draw(shape);

		//�������������� ������
		pl.setOutlineThickness(4.f);
		pl.setOutlineColor(color);
		pl.setFillColor(sf::Color::Transparent);

		//���������� �� ������ ������
		for (int i = 0; i < ARRAY_OF_NUMBER; i++)
		{
			//������ ���������� ������ � ��� ��������������, ��������� � ����� �������� �������
			sf::Vector2f position(i % Field_SIZE_pl * NUMBERFIELD + 50.f, i / Field_SIZE_pl * NUMBERFIELD + 50.f);
			text2.setFillColor(color);
			text2.setString(std::to_string(elements[i]));

			//���� ����������� ������ �� ��� ���������� �������
			if (solved)
			{
				shape.setOutlineColor(sf::Color::Green);
				text2.setFillColor(sf::Color::Green);
				pl.setOutlineColor(sf::Color::Green);
			}
			//���� ������� �� ����� ����� �� �� � ������� ����������
			else if (elements[i] == i + 1)
			{
				text2.setFillColor(sf::Color::Cyan);
			}
			//������ ������ ������
			if (elements[i] > 0)
			{
				pl.setPosition(position);
				text2.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
				s[i].setPosition(position);
				window.draw(s[i]);
				window.draw(pl);
				window.draw(text2);
			}
		}
		//����� ����� �����
		text3.setString("Steps: "+ std::to_string(move_counter));
		window.draw(text3);

		//����� �������
		text_time.setString("Timer: " + std::to_string((int)(time.asSeconds() / 60)) + ":" + ((int)time.asSeconds() % 60 >= 10  ? "" : "0") + std::to_string((int)time.asSeconds() % 60));
		window.draw(text_time);

		double endclock = clock() / 1000;// �������� ����� ������� ������

		//���� ����������� ������, �� �� ����� ��������� ����� ����������� � ����� ����� �����
		if (solved)
		{
			//��������� ����� � ������� ��� � ���� ��� ������ ����
			gametime = gametime;
			text6.setString("Timer: " + std::to_string((int)(gametime / 60)) + ":" + ((int)gametime % 60 >= 10 ? "" : "0") + std::to_string((int)gametime % 60) + " Your moves:" + std::to_string(move_counter));
			clocke.restart();
			if (gamestart)// ���� ���� ��������, �� ��������� ����� � ���� �����, ���� �� ������ �� �������� ����� � ������
			{
				window.draw(text5);
				window.draw(text6);
			}
			else
			{
				window.draw(text);
				window.draw(text4);
			}
		}
		else//����������� �� ������ �� �������� ������ � ����������� ����� ���������
		{
			window.draw(text);
			window.draw(text4);
			gametime = endclock - ctartclock - 3;
		}
		window.display();
	}
	return 0;
}