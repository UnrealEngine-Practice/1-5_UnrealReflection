// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("이학생");
	Year = 1;
	Id = 1;
}

void UStudent::DoLesson()
{
	Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%학년 %d반 %s님이 수업을 듣습니다."), Year, Id, *Name);
}
