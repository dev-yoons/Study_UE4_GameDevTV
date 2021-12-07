# Building Escape Game

## 내용 정리
  - Unreal C++
  - Mesh, Texture 조작
  - 문 열고 닫기
  - 물건 잡기

### Unreal C++ 
---------------------------------
- Log 출력
```C++
// UE_LOG(Category, Verbosity, TEXT("메시지"));
UE_LOG(LogTemp, Error, TEXT("메시지"));
UE_LOG(LogTemp, Warning, TEXT("메시지"));
UE_LOG(LogTemp, Log, TEXT("메시지"));
```  
와 같이 로그를 출력하여, 출력 로그 창을 통해 볼 수 있다.

- Owner와의 상호작용
  
GetOwner() 함수를 통해 Owner(Actor)를 읽어올 수 있다.
```C++
FString ObjectName = GetOwner()->GetName();
```

- FVector
  
struct FVector를 이용하여 3D 좌표를 표현할 수 있다.
```C++
FVector MyVector(1,1,1);
```

Owner의 GetActorLocation() 함수를 통해 Actor 좌표를 읽어올 수 있다.
```C++
FVector MyVector = GetOwner()->GetActorLocation();
```

- UPROPERTY
  
UPROPERTY(EditAnywhere) 를 사용하여 Editor에서 값을 조정할 수 있다.
```C++
UPROPERTY(EditAnywhere)
float TargetYaw = 90.0f;
```

UPROPERTY 매크로는 프로그램의 런타임 시점에서 객체의 정보와 구조를 관리,수정할 수 있도록(리플렉션할 수 있도록) 하는데, C#과 JAVA와 달리 C++에서는 리플렉션을 지원하지 않기 때문에 UE4에서 자체적으로 구현된 것이다.

- FindComponentByClass

Actor의 Component를 FindComponentByClass 함수를 통해 가져올 수 있다.
```C++
PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
```


### Mesh, Texture 조작
---------------------------------
Material은 텍스처에 대한 정보를 포함하여 렌더링하는 방법을 정의한다. 
Texture가 Material의 하위 개념이라고 볼 수 있다.

* Mesh에 Texture를 입혀 Material을 생성해낼 수 있다.

* 액터 배치 - Geometry - Subtract를 이용해 Mesh의 겹치는 부분을 삭제하는 조작을 할 수 있다.

* 모드 - 브러시 편집을 통해 다양한 다면체를 조작하여 만들 수 있다.

* 뷰포트 최대화를 통해 평면/정면/우측면 을 와이어프레임에 따라 볼 수 있다.

* Z-Fighting : 두 개의 폴리곤이 유사한 z-depth값으로 인해 깜박거리는 현상


* 블루프린트를 이용하여 Material Texture를 조작할 수 있다. 
![Material Blueprint](/material%20blueprint.png)
위처럼 U Texture Scale, V Texture Scale을 파라미터로 만들어주면,
![Material Instance](/material%20instance.png)
위와 같이 머티리얼 인스턴스 내에서 조작하기 쉬워진다.


### 문 열고 닫기
---------------------------------
* AActor 멤버 함수
```C++
FVector MyVector = GetOwner()->GetActorLocation();
GetOwner()->SetActorRotation(NewRotation);
```
위와 같은 함수들을 활용할 수 있다.
자세한 Actor 멤버 함수는 
https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/ 
에서 볼 수 있다.

* Linear Interpolation
```C++
FMath::Lerp(Current, Target, Speed);
FMath::FInterpConstantTo(Current, Target, DeltaTime, InterpSpeed);
```
위의 함수를 사용하여 순차적으로 값을 변경시킬 수 있다.
Lerp의 경우 컴퓨터의 성능 (FPS)에 따라 속도가 달라지므로, DeltaTime을 고려하는 함수를 사용하는 것이 좋다.

* Trigger Volume
  
Trigger Volume (Class명 ATriggerVolume) 을 활용하여 Trigger 를 사용할 수 있다.
```C++
ATriggerVolume* PressurePlate;
if (PressurePlate->IsOverlappingActor(SomethingActor))
  // ...
```

* Player 찾기
  
Pawn(월드 내의 플레이어)를 찾아 상호작용할 수 있다.
```C++
GetWorld()->GetFirstPlayerController()->GetPawn();
```

* 시간 재기
  
게임을 시작한 후 현재까지 경과된 시간을 알 수 있다.
```C++
GetWorld()->GetTimeSeconds();
```

* 소리 내기

UAudioComponent 클래스를 사용하여 사운드를 만들 수 있다.
단, TickComponent 와 같은 함수 안에서 Play()를 사용하면 끊임없이 소리가 재생되므로 조절해주어야한다.
```C++
if (AudioComponent && !DoorOpenSound)
{
  AudioComponent->Play();
  DoorOpenSound = true;
}
```

### 물건 잡기
---------------------------------
* 키 할당하기 

프로젝트 세팅 - 엔진 - 입력 - 바인딩 - 액션 매핑
에서 원하는 버튼을 동작이름에 매핑할 수 있다.

* Default Pawn Actor 바꾸기

기본 Default Pawn Actor는 접근이 어렵기 때문에, BluePrint를 만들어 Pawn을 교체해 줄 수 있다.
프로젝트 세팅 - 프로젝트 - 맵&모드 - Default Modes 에서 교체가 가능하다.
단, 게임모드가 GamdModeBase 등이면 교체가 불가능하므로 게임모드 또한 바꿔주어야 한다.

게임모드 BP를 생성할 때, 기존의 프로젝트 Game Mode Base를 상속받아야한다.

* Player 시점

APlayerController 클래스의 함수를 이용하여 Player의 현재 상태를 얻어올 수 있다.
```C++
GetWorld()->GetFirstPlayerController()
    ->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
```

* Collision 보기

![Material Instance](/collision%20view.png)
뷰포트의 플레이어 콜리전 모드를 통해 콜리전을 확인할 수 있다.
움직여야하는 물체는 무버블로 설정해야한다.

* Line Tracing

Line Tracing을 활용하여 Object를 가져올 수 있다.
```C++
GetWorld()->LineTraceSingleByObjectType(
  Hit, // FHitResult
  PlayerViewPointLocation, // FVector
  LineTraceEnd, // FVector
  FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
  TraceParams, // FCollisionObjectQueryParams
);

Hit.GetActor();
```

* Input Binding

UInputComponent 클래스를 이용하여 Player Input을 관리할 수 있다.
```C++
InputComponent->BindAction("Grab", IE_Pressed, this, &Grabber::Grab);
```

* PhysicsHandle

UPhysicsHandleComponent의 함수를 이용하여 Grab등의 움직임을 표현할 수 있다.
```C++
PhysicsHandle->GrabComponentAtLocation
(
  ComponentToGrab,
  Name_None, 
  LineTraceEnd
);
```