#pragma once
#include "Class2.h"

namespace CppLib
{
	public ref class Class3 sealed
	{
	public:
		Class3();
	public:
		Class2^ GetInstance();
	};
}