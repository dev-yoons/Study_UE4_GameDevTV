# Toon Tanks

## 내용 정리
- 언리얼 용어
- Movement 구현

### 언리얼 용어
----------------------------
- Pawn
Pawn 클래스는 플레이어나 AI 가 제어할 수 있는 모든 액터의 베이스 클래스를 말한다.

- Component
컴포넌트는 액터에 추가시킬 수 있는 함수성 조각을 말한다.
컴포넌트는 독립적으로 존재할 수는 없지만, 액터에 추가시키면 자립적인 함수성 조각으로, 액터에 포함시켜야 하며, 그 자체로 존재할 수는 없다.

* Component 붙이기
```C++
CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
RootComponent = CapsuleComp;

BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
BaseMesh->SetupAttachment(RootComponent);
```
위와 같이 계층구조에 원하는 component를 붙일 수 있다.

### Movement 구현
----------------------------
- BindAxis
먼저 프로젝트세팅 - 입력에서 사용할 버튼과 이름을 등록해두고,
BindAxis 함수를 통해 InputComponent에 함수를 설정해줄 수 있다.
```C++
UInputComponent *PlayerInputComponent
PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
```

- AddActorLocalOffset / AddActorLocalRotation
위의 함수를 이용하여, 움직임을 구현할 수 있다.
```C++
void APawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
    AddActorLocalOffset(MoveDirection, true);
}
void APawnTank::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0,Rotation,0);
    RotationDirection = FQuat(Rotation);
    AddActorLocalRotation(RotationDirection, true);
}
```


