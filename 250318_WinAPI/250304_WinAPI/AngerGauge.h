#pragma once
#include "GameObject.h"

class Image;

class AngerGauge: public GameObject
{
private:
	// 
	Image* anger;
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	AngerGauge();
	~AngerGauge();
};

