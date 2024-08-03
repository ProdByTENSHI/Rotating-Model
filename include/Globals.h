#pragma once

#include <GLFW/glfw3.h>
#include <stdint.h>

#include "EventSystem.h"
#include "RessourceManager.h"

// Window
inline GLFWwindow* g_Window = nullptr;
inline uint32_t g_WindowWidth = 1280;
inline uint32_t g_WindowHeight = 720;

// Manager
inline std::unique_ptr<RessourceManager> g_RessourceManager;

// Input
inline chroma::Event<int> g_OnKeyDown;
inline chroma::Event<int> g_OnKeyUp;
inline chroma::Event<int> g_OnKeyHold;