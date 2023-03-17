// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"

// 클래스 생성자의 값은 CDO에 저장되고 이후에 Init함수에서 SchoolName을 바꿔도
// CDO에 저장된 기본 값은 바뀌지 않는다.
UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	/*
	 * 1. UMyGameInstance()의 Class정보를 Run time에 얻을 수 있다.
	 * 2. UMyGameInstance()의 Class정보를 Compile time에 얻을 수 있다.
	 * ClassRumtime과 ClassCompile은 같은 값을 가리킨다.
	 */
	UE_LOG(LogTemp, Log, TEXT("==========================="));
	const UClass* ClassRuntime = this->GetClass();
	const UClass* ClassCompile = UMyGameInstance::StaticClass();
	// 반드시 검증하고 넘어가야하는 부분에서는 assertion함수를 사용한다.
	ensure(ClassRuntime == ClassCompile);
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s\n"), *ClassRuntime->GetName());

	UE_LOG(LogTemp, Log, TEXT("==========================="));
	SchoolName = TEXT("바뀐 학교");
	UE_LOG(LogTemp, Log, TEXT("학교 이름 -> %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본-> %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);


	UE_LOG(LogTemp, Log, TEXT("==========================="));
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();
	//일반적인 방법으로 이름을 바꾸는 법
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 : %s"), *Student->GetName());

	// Reflection 시스템을 이용한 방법

	FString CurrentTeacherName;
	FProperty* NameProperty = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProperty)
	{
		NameProperty->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *Teacher->GetName());
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *CurrentTeacherName);

		CurrentTeacherName = TEXT("새선생");
		NameProperty->SetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름: %s"), *Teacher->GetName());
	}


	UE_LOG(LogTemp, Log, TEXT("==========================="));
	Teacher->DoLesson(); 
	// DoLesson이라는 이름의 함수(객체)를 찾는다.
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
	UE_LOG(LogTemp, Log, TEXT("==========================="));
	UE_LOG(LogTemp, Log, TEXT("==========================="));
}
