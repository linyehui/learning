// Class3.cpp
#include "pch.h"
#include "Class3.h"

using namespace CppLib;
using namespace Platform;

Class3::Class3()
{
}

Class2^ Class3::GetInstance()
{
	return nullptr;
	//return Class2::GetInstance();
}