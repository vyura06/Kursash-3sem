#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//�����, ���������� �� ������ �� ���������
class SpriteManager {
public:

	//�������� � ������
	Texture texture;
	Sprite sprite;

	//����������� �� ���������
	SpriteManager() {}

	//����� ���������� ���� � ����������� �������� � ������
	void setSp(String path) {
		texture.loadFromFile(path);//�������� �������
		sprite.setTexture(texture);//�������� �������
	}
};

