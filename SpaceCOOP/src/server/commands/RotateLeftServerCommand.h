#pragma once
#include "../../shared/HeldCommand.h"
#include "PlayerCommand.h"
class RotateLeftServerCommand :
	public HeldCommand,
	public PlayerCommand {
public:
	RotateLeftServerCommand();
	~RotateLeftServerCommand();
	void execute();
};

