#pragma once
#include <string>
#include <filesystem>

// ���� : �ּ� ���� Ŭ����
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

	// ���� �̸� ���� �Լ�
	std::string GetFileName();

	// ���� ��� ����
	void SetCurrentPath();

	// �θ� ������ �̵�
	void MoveParent();

	// ������ �ڽ� ���(����)�� �ִ��� Ȯ��
	void MoveParentToExistsChild(const std::string& _ChildPath);

	// ������ �ڽ� ���(����)�� �̵�
	void MoveChild(const std::string& _ChildPath);

	// ������ �ڽ� ���(����)�� �̵��Ѱ� ����
	std::string PlusFilePath(const std::string& _ChildPath);

	// ��θ� string������ ����
	std::string GetStringPath()
	{
		return Path.string();
	}

	bool IsDirectory();

protected:
	std::filesystem::path Path;

private:
};

