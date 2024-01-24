#include "../stdafx.h"
#include "Controller.h"

Controller::Controller(bool activated) : _activated{activated}
{
}

void Controller::SetActivation(bool value)
{
	_activated = value;
}