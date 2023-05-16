#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// Ό³Έν : 
class GameEngineSprite;
class GameEngineWindowTexture;
class ResourcesManager
{
public:
	
	// delete Function
	ResourcesManager(const ResourcesManager & _Other) = delete;
	ResourcesManager(ResourcesManager && _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager & _Other) = delete;
	ResourcesManager& operator=(ResourcesManager && _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	GameEngineSprite* FindSprite(const std::string& _Name);

	GameEngineSprite* CreateSpriteFolder(const std::string& _Path)
	{
		GameEnginePath FolderPath = _Path;

		CreateSpriteFolder(FolderPath.GetFileName(), _Path);
	}

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path);

	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;

		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TextturePath, int _XCount, int _YCount);

	bool IsLoadTexture(const std::string& _Name);

protected:

private:
	static ResourcesManager Inst;

	// constrcuter destructer
	ResourcesManager();
	~ResourcesManager();

	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	
	std::map<std::string, GameEngineSprite*> AllSprite;

};

