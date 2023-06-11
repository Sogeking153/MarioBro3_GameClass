#pragma once
#include <Windows.h>
class TimeCustom
{
public:
	int startTime;
	int limitTime;

public:

	TimeCustom(int limitTime) { this->limitTime = limitTime; startTime = 0; };

	TimeCustom() {};
	~TimeCustom() {};


	void StartTime() { startTime = GetTickCount64(); };
	bool IsTimeUp() { return (startTime && GetTickCount64() - startTime >= limitTime); };
	void Reset() { startTime = 0; }
};