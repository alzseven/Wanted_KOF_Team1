#include "AngerGauge.h"
#include "Image.h"

void AngerGauge::Init()
{
	anger = new Image[3];

	// ��
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGaugeBar"), 78, 6, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGaugeBar �ε� ����"), TEXT("���"), MB_OK);
	}
	// ������
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGauge"), 78, 18, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGauge �ε� ����"), TEXT("���"), MB_OK);
	}
	// �ƽø�
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGaugeBar"), 78, 6, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGaugeBar �ε� ����"), TEXT("���"), MB_OK);
	}


}

void AngerGauge::Release()
{
	if (anger)
	{
		anger->Release();
		delete anger;
		anger = nullptr;
	}
}

void AngerGauge::Update()
{
}

void AngerGauge::Render(HDC hdc)
{
}

AngerGauge::AngerGauge()
{
}

AngerGauge::~AngerGauge()
{
}
