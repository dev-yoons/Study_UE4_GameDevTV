# Building Escape Game

## 내용 정리
  - Unreal C++
  - Mesh, Texture 조작

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
  
GetOwner() 함수를 통해 Owner를 읽어올 수 있다.
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