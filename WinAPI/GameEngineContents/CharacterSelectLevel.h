#pragma once

// Ό³Έν : 
class CharacterSelectLevel
{
public:
	// constrcuter destructer
	CharacterSelectLevel();
	~CharacterSelectLevel();

	// delete Function
	CharacterSelectLevel(const CharacterSelectLevel & _Other) = delete;
	CharacterSelectLevel(CharacterSelectLevel && _Other) noexcept = delete;
	CharacterSelectLevel& operator=(const CharacterSelectLevel & _Other) = delete;
	CharacterSelectLevel& operator=(CharacterSelectLevel && _Other) noexcept = delete;

protected:

private:

};

