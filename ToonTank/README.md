# Toon Tanks

## 내용 정리
- 언리얼 용어, 언리얼 C++
- Movement 구현
- 총알 발사 구현
- 델리게이트
- 각종 효과

### 언리얼 용어, 언리얼 C++
----------------------------
- Pawn
  
Pawn 클래스는 플레이어나 AI 가 제어할 수 있는 모든 액터의 베이스 클래스를 말한다.

- Component
  
컴포넌트는 액터에 추가시킬 수 있는 함수성 조각을 말한다.
컴포넌트는 독립적으로 존재할 수는 없지만, 액터에 추가시키면 자립적인 함수성 조각으로, 액터에 포함시켜야 하며, 그 자체로 존재할 수는 없다.

- Component 붙이기
```C++
CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
RootComponent = CapsuleComp;

BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
BaseMesh->SetupAttachment(RootComponent);
```
위와 같이 계층구조에 원하는 component를 붙일 수 있다.

- 형변환
```C++
GameModeRef = Cast<ATankGameModeBase>
(UGameplayStatics::GetGameMode(GetWorld()));
```
와 같이 형변환을 사용할 수 있다.

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

### 총알 발사 구현
----------------------------
- Timer
  
SetTimer 함수를 이용하여 시간에 따라 동작하는 기능을 구현할 수 있다.
```C++
GetWorld()->GetTimeManager().SetTimer
(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, 2.0f, true);
```

- 커서 위치 찾기

GetHitResultUnderCurso 함수를 이용하여 커서의 움직임에 대응할 수 있다.

```C++
FHitResult TraceHitResult;
PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
FVector HitLocation = TraceHitResult.ImpactPoint;
```

- 발사체 움직임

UProjectileMovementComponent 클래스를 통해 발사체 움직임 구현을 편리하게 할 수 있다.

```C++
ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>
                        (TEXT("Projectile Movement"));
ProjectileMovement->InitialSpeed = 2.0f;
ProjectileMovement->MaxSpeed = 3.0f;
```

- Script 내에서 Actor 생성하기

SpawnActor 함수를 통해 Actor를 생성할 수 있다.
```C++
AProjectileBase* TempProjectile = 
GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
```

### 델리게이트
----------------------------

델리게이트란, **오브젝트 상의 멤버 함수를 가리키고 실행시키는 데이터 유형**이다.

```C++
class FLogWriter
{
    void WriteToLog( FString );
};
```
위의 WriteToLog 함수를 아무데서나 사용하기 위해, 델리게이트를 선언한다.
```C++
DECLARE_DELEGATE_OneParam( FStringDelegate, FString );
```
위의 매크로를 통해, FStringDelegate 라는 델리게이트 유형을 선언할 수 있다.
``` C++
class FMyClass
{
    FStringDelegate WriteToLogDelegate;
};
```
다른 클래스에서 이 FStringDelegate를 사용할 수 있다.
``` C++
TSharedRef< FLogWriter > LogWriter( new FLogWriter() );

WriteToLogDelegate.BindSP( LogWriter, &FLogWriter::WriteToLog );

WriteToLogDelegate.Execute(TEXT("델리게이트"));
// WriteToLogDelegate.ExecuteIfBound() 도 사용 가능.
```
위와 같이, 델리게이트를 사용하여 FMyClass에서 FLogWriter에 대한 정보 없이 WriteToLog 함수를 호출 할 수 있다.

```C++
ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
```
이번 프로그램에선 위와 같이 사용하였다.

**다이나믹 델리게이트**는 함수 포인터가 아닌 함수의 이름을 기반으로 호출한다. 일반 델리게이트보다 느리다.



### 각종 효과
----------------------------
- 파티클 생성
  
파티클 시스템은 SpawnEmitter를 통해 생성한다.

```C++
UParticleSystem* DeathParticle;
UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetAcotrLocation());
```

- 사운드

USoundBase 클래스를 활용하여 사운드를 출력한다.
```C++
USoundBase* HitSound;
UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
```

- Camera Shake

UCameraShakeBase 클래스를 활용하여 카메라 흔들림을 설정한다.
```C++
TSubclassOf<UCameraShakeBase> HitShake;
GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
```

블루프린트 내에서 카메라 흔들림 설정을 조정할 수 있다.