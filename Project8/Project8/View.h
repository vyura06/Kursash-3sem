#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

	View view;//��������  ������

	//������� ��� ���������� ��������� ������
	void setViewPosition(float x, float y) {

		float tempX = x; float tempY = y;//��������� ���� ������ � ��������� ��, ����� ������ ����

		//������� �� ���� ����� �����
		if (x < 960) { tempX = 960; }
		if (numberLevel > 6 && numberLevel < 11) { if (x > 3840) tempX = 3840; }
		if (numberLevel > 2 && numberLevel < 7) { if (x > 2640) tempX = 2640; }

		//������� �� ���� ������ �����
		if (numberLevel > 0 && numberLevel < 3) { if (x > 1440) tempX = 1440; }

		//������� ������� �����
		if (y < 540) { tempY = 540; }

		//������� ������ �����
		if (y > 661) { tempY = 661; }

		view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������
	}

	//������� ��� ����������� ������ �� �����
	void viewMap(float time) {

		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
			view.move(0.1 * time, 0);//�������� ����� ������
		}

		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
			view.move(-0.1 * time, 0);//�������� ����� �����
		}

		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space)) {
			view.move(0, 0.1 * time);//�������� ����� �����
		}


		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
			view.move(0, -0.1 * time);//�������� ����� ����
		}
	}