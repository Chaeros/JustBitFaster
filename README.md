# JustBitFaster(좀 더 빨랐죠) - 낯선 도구 해커톤
양쪽 플레이어가 로봇팔을 조작해 진열대에서 아이템 합산 총계를 더 많이 가져가면 승리하는 멀티플레이 콘솔 게임

---

## 프로젝트 소개

**JustBitFaster**는  
두 명의 플레이어가 각각 로봇팔을 조작하여 중앙의 진열대에 생성된 아이템을  
더 빠르게 획득해 점수를 경쟁하는 콘솔 기반 게임입니다.

실시간 입력, 멀티스레드, 뮤텍스 동기화 등  
콘솔 환경에서의 **동시성 처리와 게임 로직 구조화**를 목표로 설계되었습니다.

---

## 게임 규칙

- 게임 시간은 **30초**
- 진열대에는 0~9번 슬롯까지 아이템이 랜덤 생성됨
- 플레이어는 위/아래로 이동하며 원하는 슬롯으로 로봇팔을 움직임
- 선택키로 해당 슬롯의 아이템을 획득
- 특정 아이템은 **글로벌 락(Global Lock)** 을 발생시켜
  - 자신만 아이템 획득 가능  
  - 상대는 이동과 아이템 습득이 잠시 차단됨
  - Lock 상태의 상대의 로봇이 붉은 색으로 포현됨
- 특정 아이템은 **2배 점수 획득** 을 발생시켜, 이 후 먹는 아이템의 점수를 2배로 획득함
- 진열대의 모든 Item을 가져가면, 진열대에 새로운 Item들이 다시 진열됨
- 게임 종료 시 **총 점수가 더 높은 사람이 승리**

---

## 조작 방법

<b>Player1:</b><br>
- W = Up<br>
- S = Down<br>
- D = Select<br>

<b>Player2:</b><br>
- I = Up<br>
- K = Down<br>
- L = Select<br>

---

## 게임 진행 화면
<h3>1. 게임 시작 화면</h3>
<img src="https://github.com/user-attachments/assets/7d336975-c96e-44e6-b438-efcf74628f10" width="400"> <br>
- 중앙 진열대를 기준으로 양 옆에 로봇이 하나씩 존재합니다. <br>
- 2명의 플레이어가 진행할 수 있으며, 각 로봇 당 한명의 플레이어가 플레이합니다. <br>
- 플레이어가 Item을 가져가면, Item 우측의 점수를 획득합니다. <br>
<br>

<h3>2. Lock 아이템 획득 시 화면</h3>
<img src="https://github.com/user-attachments/assets/777d87d0-0d3b-4ad4-abea-3146d7cd2db8" width="400"> <br>
- Lock 아이템을 획득할 경우(GlobalLockItem), 상대는 3초 간 로봇을 이동하거나, 현재 위치의 Item을 가져갈 수 없습니다. <br>
- 위 이미지는 플레이어2가 Lock 아이템을 획득한 모습으로, 상대인 플레이어1의 로봇은 붉은 색을 띕니다. <br>
<br>

<h3>3. 2배 Score 아이템 획득 시 화면</h3>
<img src="https://github.com/user-attachments/assets/84d1fdde-a474-4d80-a8e7-673bc2f2b242" width="400"> <br>
- 2배 Score 아이템을 획득할 경우(DoubleScoreItem), 다음에 획득하는 Item의 접수를 2배 획득합니다. <br>
<br>

<h3>4. 플레이 결과 출력 및 재시도 화면</h3>
<img src="https://github.com/user-attachments/assets/5af42732-d574-48c4-b1c7-2f406fce1edf" width="400"> <br>
- 제한 시간(30초) 내 더 많은 점수를 획득한 플레이어가 승리합니다. <br>
- 입력을 통해 다시 새로운 게임을 플레이할 수 있습니다. <br>
<br>

---

## 폴더 구조

프로젝트는 다음과 같은 구조로 구성됩니다:

<pre>
JustBitFaster/
├─ include/
│  ├─ core/
│  │  ├─ DisplayShelf.h
│  │  ├─ Item.h
│  │  └─ Types.h
│  │
│  ├─ game/
│  │  ├─ controller/
│  │  │  └─ GameController.h
│  │  └─ service/
│  │     ├─ ConsoleGameService.h
│  │     └─ IGameService.h
│  │
│  ├─ input/
│  │  ├─ InputManager.h
│  │  ├─ InputQueue.h
│  │  └─ RetryInputView.h
│  │
│  ├─ output/
│  │  └─ EndGameOutputView.h
│  │
│  ├─ robot/
│  │  └─ Robot.h
│  │
│  └─ ui/
│     └─ Ui.h
│
├─ src/
│  ├─ core/
│  │  └─ DisplayShelf.cpp
│  │
│  ├─ game/
│  │  ├─ controller/
│  │  │  └─ GameController.cpp
│  │  └─ service/
│  │     └─ ConsoleGameService.cpp
│  │
│  ├─ input/
│  │  ├─ InputManager.cpp
│  │  └─ RetryInputView.cpp
│  │
│  ├─ output/
│  │  └─ EndGameOutputView.cpp
│  │
│  ├─ robot/
│  │  └─ Robot.cpp
│  │
│  └─ ui/
│     └─ Ui.cpp
│
├─ main.cpp
├─ README.md
└─ 프로젝트 설정 파일 (JustBitFaster.vcxproj 등)
</pre>
