// Class2.cpp
#include "pch.h"
#include "Class2.h"

using namespace CppLib;
using namespace Platform;

Class2::Class2()
{
}

Class2^ Class2::GetInstance()
{
	static Class2^ s_inst= ref new Class2(); 
	return s_inst;
}