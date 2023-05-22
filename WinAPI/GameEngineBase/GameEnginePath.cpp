#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	:Path(_Path)
{
}

GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}

void GameEnginePath::SetCurrentPath()
{
	Path = std::filesystem::current_path();
}

// ���� ������ �̵�
void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

// ChildPath�� �ִ� ������ MoveParent
void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("��Ʈ ��α��� ������ �������� " + _ChildPath + "�����̳� ������ ������ ������ �ִ� ��θ� ã�� ���߽��ϴ�.");
		}
	}
}

// ������ ���� ��η� �̵�
void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�." + CheckPath.string());
	}

	Path = CheckPath;
}

std::string GameEnginePath::PlusFilePath(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�." + CheckPath.string());
	}

	return CheckPath.string();
}

bool GameEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

std::string GameEnginePath::GetParentString(const std::string& _ChildPath)
{
	int CountBeforeBackSlash = 0;

	while (true)
	{
		if ('\\' == _ChildPath[CountBeforeBackSlash])
		{
			break;
		}

		++CountBeforeBackSlash;
	}

	std::string ChildPath = "";
	ChildPath.reserve(CountBeforeBackSlash);

	for (size_t i = 0; i < CountBeforeBackSlash; i++)
	{
		ChildPath.push_back(_ChildPath[i]);
	}

	return ChildPath;
}
