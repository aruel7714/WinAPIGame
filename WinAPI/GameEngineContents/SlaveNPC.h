#pragma once
#include "PlayActor.h"

// Ό³Έν : 
class SlaveNPC : public PlayActor
{
public:
	// constrcuter destructer
	SlaveNPC();
	~SlaveNPC();

	// delete Function
	SlaveNPC(const SlaveNPC & _Other) = delete;
	SlaveNPC(SlaveNPC && _Other) noexcept = delete;
	SlaveNPC& operator=(const SlaveNPC & _Other) = delete;
	SlaveNPC& operator=(SlaveNPC && _Other) noexcept = delete;

protected:

private:

};

