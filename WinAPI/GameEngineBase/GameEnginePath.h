#pragma once
#include <string>
#include <filesystem>

// 설명 : 주소 관련 클래스
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::string& _Path);	
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath & _Other) = delete;
	GameEnginePath(GameEnginePath && _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath & _Other) = delete;
	GameEnginePath& operator=(GameEnginePath && _Other) noexcept = delete;

	// 파일 이름 리턴 함수
	std::string GetFileName();

	// 현재 경로 설정
	void SetCurrentPath();

	// 부모 폴더로 이동
	void MoveParent();

	// 지정한 자식 경로(폴더)가 있는지 확인
	void MoveParentToExistsChild(const std::string& _ChildPath);

	// 지정한 자식 경로(폴더)로 이동
	void MoveChild(const std::string& _ChildPath);

	// 지정한 자식 경로(폴더)로 이동한걸 리턴
	std::string PlusFilePath(const std::string& _ChildPath);

	// 경로를 string형으로 리턴
	std::string GetStringPath()
	{
		return Path.string();
	}

	bool IsDirectory();

protected:
	std::filesystem::path Path;

private:
};

