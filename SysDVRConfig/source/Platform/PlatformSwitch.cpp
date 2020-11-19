#ifdef __SWITCH__

#include "Platform.hpp"
#include <iostream>
#include <switch.h>
#include <unistd.h>
#include "../UI/UI.hpp"

#ifdef __NXLINK_ENABLE__
static int nxlink_sock = -1;
#endif

GLFWgamepadstate g_gamepad;

void Platform::Init() 
{
	romfsInit();
	socketInitializeDefault();
#ifdef __NXLINK_ENABLE__
	nxlink_sock = nxlinkStdio();
#endif
}

void Platform::Exit()
{
#ifdef __NXLINK_ENABLE__
	if (nxlink_sock != -1)
		close(nxlink_sock);
#endif
	socketExit();
	romfsExit();
}

void Platform::AfterInit()
{

}

void Platform::GetInputs()
{
	if (!glfwGetGamepadState(GLFW_JOYSTICK_1, &g_gamepad))
		std::cout << "Error reading from gamepad";
}

void Platform::ImguiBindings()
{
	ImGuiIO &io = ImGui::GetIO();
	u32 touch_count = hidTouchCount();
	if (touch_count == 1)
	{
		touchPosition touch;
		hidTouchRead(&touch, 0);
		io.MousePos = ImVec2(touch.px, touch.py);
		io.MouseDown[0] = true;
	}
	else io.MouseDown[0] = false;
}

void Platform::Sleep(float time)
{
	usleep(time * 1000);
}

#endif