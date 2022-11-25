#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include "system/system.hpp"
#ifdef SYS
	#include "system/unix/keyboard.hpp"
	#include "system/unix/define.hpp"
#else
	#include "system/win/win-keyboard.hpp"
	#include "system/win/define.hpp"
#endif

#endif