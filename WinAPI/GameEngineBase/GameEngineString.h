#pragma once
#include <string>

// 설명 : string 관련 함수
class GameEngineString
{
public:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString & _Other) = delete;
	GameEngineString(GameEngineString && _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString & _Other) = delete;
	GameEngineString& operator=(GameEngineString && _Other) noexcept = delete;

	// 인자로 받은 string을 대문자로 리턴
	static std::string ToUpperReturn(const std::string& _Value)
	{
		std::string UpperString = _Value;

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}
		return UpperString;
	}

protected:

private:

};

