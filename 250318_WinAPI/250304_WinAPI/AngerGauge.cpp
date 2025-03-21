#include "AngerGauge.h"
#include "Image.h"

void AngerGauge::Init()
{
	anger = new Image[3];

	// 바
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGaugeBar"), 78, 6, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGaugeBar 로드 실패"), TEXT("경고"), MB_OK);
	}
	// 게이지
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGauge"), 78, 18, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGauge 로드 실패"), TEXT("경고"), MB_OK);
	}
	// 맥시멈
	if (FAILED(anger[0].Init(TEXT("Image/anger/AngerGaugeBar"), 78, 6, 1, 1,
		true, RGB(224, 0, 237))))
	{
		MessageBox(g_hWnd, TEXT("Image/anger/AngerGaugeBar 로드 실패"), TEXT("경고"), MB_OK);
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
