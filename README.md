# Wanted_KOF_Team1

## 프로젝트 소개

이 프로젝트는 SNK의 인기 격투 게임 시리즈인 '더 킹 오브 파이터즈(The King of Fighters)'를 Windows API(WinAPI)와 C++를 이용하여 모작한 게임입니다.

## 프로젝트 목표 및 의의

- WinAPI와 C++를 활용한 게임 개발 역량 강화
- 클래식 대전 격투 게임의 단순화된 메커니즘 이해 및 구현
- WinAPI의 이미지 출력 방식 및 기초적인 충돌처리 로직 학습
## 개발 환경 및 기술 스택

- 언어: C++
- 그래픽 API: Windows GDI (Graphics Device Interface)
- 개발 환경: Visual Studio
- 버전 관리: Git

## 구현된 기능

### 핵심 시스템

- 2D 그래픽 렌더링
- 키보드 입력 처리 시스템
- 충돌 감지 및 히트박스 관리

### 게임플레이 요소

- 캐릭터 움직임 및 애니메이션
- 기본 공격(강/약,펀치/킥) 및 가드(상단/하단)
- 현재 체력 표시 UI
- 배경 애니메이션 및 스크롤

## 설치 및 실행 방법

1. 프로젝트 클론하기

```
git clone https://github.com/alzseven/Wanted_KOF_Team1.git
```

2. Visual Studio에서 솔루션 파일 열기

```
cd Wanted_KOF_Team1/250318_WinAPI
```

솔루션 파일(.sln)을 Visual Studio에서 엽니다.

3. 프로젝트 빌드 및 실행 Visual Studio에서 솔루션을 빌드하고 실행합니다.

## 조작 방법

### 플레이어 1
- **전진**: D
- **후진**: A
- **앉기**: S
- **약 펀치**: G
- **강 펀치**: T
- **약 발차기**: H
- **강 발차기**: Y

### 플레이어 2
- **전진**: J
- **후진**: L
- **앉기**: | (VK_SEPARATOR)
- **약 펀치**: Numpad5
- **강 펀치**: Numpad8
- **약 발차기**: Numpad6
- **강 발차기**: Numpad9

## 팀원 및 역할 분담

- [**alz7**](https://github.com/alzseven) : 캐릭터, FSM, 충돌처리
- [**Tae Gwan Cha**](https://github.com/chataeg) : 캐릭터, UI
- [**Fillmore**](https://github.com/clcmd9701) : UI
- [**jin**](https://github.com/kimmjiinn) : 캐릭터, 아트
- [**Jisoo Lee**](https://github.com/diduo7) : 백그라운드 UI

## 스크린샷

[Screenshot](https://github.com/alzseven/Wanted_KOF_Team1/blob/master/KOFClone_Screenshot.png)
