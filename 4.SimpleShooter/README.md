# Simple Shooter
-----------------------------
    * Asset의 크기가 커 Github에 업로드하지 않음

## 내용 정리
- 캐릭터 움직임 만들기 
- 애니메이션
- AI
- 사운드
- 언리얼 기술

### 캐릭터 움직임 만들기
----------------------------

- Bind Axis
```C++
PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
```

위와 같이 BindAxis 함수를 통해 움직임을 만들 수 있다.
Project Setting 에서 Axis에 매핑을 해줄 필요가 있다.

- 컨트롤러 입력에 대한 움직임
![Framerate](/framerate.png)

위의 그림과 같이, Controller 입력의 경우 움직임이 FrameRate의 영향을 받기 때문에 보정이 필요하다.

```C++
void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
```

### 애니메이션
----------------------------

- 가장 단순하게 애니메이션 적용하기

Blueprint에서 Animation Mode를 'Use Animation Asset' 로 설정하고,
원하는 애니메이션을 할당하면 해당 애니메이션을 적용시킬 수 있다.

- Animation Blueprint 적용

Animation 에도 Blueprint와 같은 사고흐름(?)을 적용시킬 수 있다.
Animation 여러 개를 합성하는 Blend 노드 등을 활용하여 조금 더 복잡한 애니메이션을 만들 수 있다. 
Blueprint에서 Animation Mode를 'Use Animation Blueprint'로 설정하여 사용할 수 있다.

- 2D Blend Space

걷기, 달리기 같은 방향에 따라 미세하게 바뀌는 애니메이션을 2D Blend Space를 통해 구현할 수 있다.

![Blend Space](/blendspace.png)

위와 같이, 각 위치에 적절한 애니메이션을 대응시켜 연속적인 애니메이션 변화를 구현한다.

Speed에 따른 걷기 애니메이션을 구현할 경우, 애니메이션의 재생속도를 고려하여 위치를 정할 필요가 있다. 
애니메이션의 재생속도와 Speed가 적절히 대응되지 않으면 걷는 동작에 비해 속도가 너무 빠른 등의 위화감이 생긴다.

- State Machine
  
AnimGraph 에 State Machine을 추가하여, 각 State에 대한 애니메이션을 할당할 수 있다.
각 State 사이의 Transition 시간, 조건 등을 Custom으로 만들어 자연스러운 애니메이션 전환이 이루어지도록 할 수 있다.

### AI
----------------------------
- AI 만들기

기존 Character BP의 Detail을 보면 'AI Controller Class'가 존재한다. 해당 Class를 설정하여 AI를 설정할 수 있다.
AI Class는 AIController 클래스를 Parent로 설정하여 구현하면 편하다. 
(MoveToActor, SetFocus 등의 기본함수 존재)

- NavMesh

언리얼의 NavMesh는 Bake 없이 단순히 Volume을 통해 구현된다.

- Behavior Tree, Blackboard

Behavior Tree는 AI의 행동패턴을 표현하는 양식이고, Blackboard는 행동패턴에 필요한 변수를 저장하는 공간이라고 볼 수 있다.
AIController에 Behavior Tree 와 상호작용하는 함수가 존재하므로, 코드에서 행동패턴을 만들어낼 수 있다.

### 사운드
----------------------------
- 특정 위치에서 소리 생성
```C++
UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
```
위의 함수를 통해 사운드를 위치에 따라 생성할 수 있다.

- Sound Cue 
  
Sound Cue를 통해 랜덤 사운드 재생, Modulator를 통한 Pitch 조절 등의 사운드 조작을 할 수 있다.

- 사운드 공간화

sound attenuation (감쇠) 를 통해 소리의 공간적 특성을 조절할 수 있다.
소리가 들리는 최소거리, 거리에 따른 음량 감소 함수 등을 설정할 수 있다.

- BGM

BGM은 단순히 사운드 위치를 플레이어의 현재 위치로 고정하여 구현이 가능하다.

### 언리얼 기술
----------------------------
- Mesh 붙이기

이 프로그램처럼 기존의 총을 새로운 총으로 대체하는 등의 작업을 하고 싶을 경우,
기존 Mesh 에 존재하는 총의 위치에 Socket을 생성하고, 해당 Socket에 원하는 Mesh를 집어넣을 수 있다. (기존 총은 안 보이게 하는 것이 좋을 것이다.)

```C++
Gun = GetWorld()->SpawnActor<AGun>(GunClass);
GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // 기존의 총을 숨긴다.
Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
// 기존 총 위치에 생성한 Socket에 원하는 Mesh를 붙인다.
Gun->SetOwner(this);
```

- Trace
  
언리얼의 트레이스를 통해 직선상에 무엇이 존재하는지 확인할 수 있다.
Line Trace를 통해 직선거리의 충돌을 감지할 수도 있고, Shape Trace를 활용하면 원뿔모양의 충돌을 감지하여 시야 등을 구현할 수 있다.

```C++
bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End,
    ECollisionChannel::ECC_GameTraceChannel1, Params);
```
위의 함수를 사용하기 전에 프로젝트 세팅에서 Trace Channel을 설정해야 한다.


- 기본 제공 함수들

언리얼에는 Jump, TakeDamage 등 기본 제공하는 함수가 많다.
구현하기 전에 한 번 검색해보는 것이 좋다. 
따로 구현하더라도 참고가 가능하고, virtual method 인 경우 override를 통해 확장하여 사용할 수 있다.

- BlueprintPure & BlueprintCallable

BlueprintPure
```C++
UFUNCTION(BlueprintPure)
    bool IsDead() const;
```
수학 (+, - , *, 등) 노드, 변수 getter, 아무 것도 영원히 바꾸지 않는 함수는 BlueprintPure 함수이다.
블루프린트에서 호출할 수 있고, 오브젝트나 글로벌한 상태를 바꾸지 않는다.

반대로, BlueprintCallable은 블루프린트에서 호출할 수 있고, 호출중인 오브젝트나 글로벌한 상태를 바꾼다.


- Timer
```C++
GetWorldTimeManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
```
GetWorldTimeManager를 통해 시간에 관한 조작을 해주는 FTimeManager를 가져올 수 있다.

- 변수와 상호작용하는 UI

체력바와 같이 현재 변수와 상호작용하는 UI의 경우, Bind 를 사용하여 구현이 가능하다.
Detail 창의 몇몇 설정에 대해 Bind가 존재하므로 해당 설정을 변수로 조절할 수 있다.
