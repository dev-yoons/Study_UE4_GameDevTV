# Building Escape Game

## 내용 정리
  - [Unreal C++](#unreal-c++)
  - [Mesh, Texture 조작](#mesh,-texture-조작)

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