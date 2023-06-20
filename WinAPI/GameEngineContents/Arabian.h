#pragma once
#include "PlayActor.h"


// Ό³Έν : 
class Arabian : public PlayActor
{
public:
	// constrcuter destructer
	Arabian();
	~Arabian();

	// delete Function
	Arabian(const Arabian & _Other) = delete;
	Arabian(Arabian && _Other) noexcept = delete;
	Arabian& operator=(const Arabian & _Other) = delete;
	Arabian& operator=(Arabian && _Other) noexcept = delete;

protected:

private:
	static std::list<Arabian*> AllArabian;

};

