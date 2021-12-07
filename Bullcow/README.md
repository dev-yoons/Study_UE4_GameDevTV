# BullCowGame

## 내용 정리
* 간단한 에디터 동작
* In Game Terminal에 텍스트 출력하기
* C++ 코드 복습 
* Unreal C++

### 간단한 에디터 동작
---------------------------------
- 뷰포트
    * 카메라 이동 (둘러보기)
    * 뷰포트 여러 개 만들기

- Editing Actor
    * Transform - Location, Rotation, Scale 조작
    * Grid 조절
    * 표면에 붙이기
    * global/local 

- Landscape 조작
    * Mode-Landscaping-Sculpting 을 통해 언덕 등등을 마우스 조작으로 만들 수 있다.
  
### In Game Terminal에 텍스트 출력하기
---------------------------------
- PrintLine() 함수를 통해 출력이 가능하다.
```C++
PrintLine(TEXT("Hello"));
```  
%s 등을 사용하여 변수 출력이 가능하다.
```C++
PrintLine(TEXT("Hello %s"), name);
```  
- ClearScreen() 을 통해 Screen을 지운다.
```C++
ClearScreen();
```  
- FString Type

Unreal에선 string 을 대신하여 FString을 사용한다.

```C++
FString HiddenWord = TEXT("water");
```  

FString은 **TCHAR의 TARRAY**이다.
마찬가지로, 마지막에 \0 이 붙는다.
```C++
HiddenWord[0];
``` 
>w

Len() 함수를 사용하여 FString의 길이를 알 수 있다.
```C++
HiddenWord.Len();
```  
> 5

- TEXT() 매크로

string variable을 사용할 때, TEXT() 매크로를 일반적으로 사용한다.
유니코드 사용 유무에 상관없이 문자열을 처리하도록 도와준다. 
```C++
TEXT("water");
```  

### C++ 코드
---------------------------------
* Const Member Function
```C++
bool UBullCowCartridge::IsIsogram(FString Word) const
{ 
    // ...
}
```  
와 같이 표현되는 const 멤버함수는 객체의 멤버변수를 변경할 수 없는 읽기 전용 함수이다.

* 범위 기반 for문 (Range-based for loop)
```C++
for (int num:IntArr)
    std::cout << num << ' ';
```  
C++11 부터 위와 같은 for문을 사용할 수 있다. 
### Unreal C++
---------------------------------
* TArray
```C++
const TArray<type> Name = {e1, e2, e3, ... };
```  
언리얼 엔진에서는 TArray를 배열로 자주 사용한다.
```C++
const TArray<int32> IntArr;

IntArr.Init(10,5);  // [10,10,10,10,10]
IntArr.Emplace(11); // [10,10,10,10,10,11]
IntArr.Add(11);     // [10,10,10,10,10,11,11]
// Emplace는 임시 변수 생성을 하지 않으므로 복잡한 type을 사용할 때 바람직하다. 일반적으로 Emplace가 더 좋다.

IntArr.Num(); // 배열 길이를 return한다.

IntArr.Sort(); // 기본으로 정렬을 제공한다.

// 기타 등등 ...
``` 

