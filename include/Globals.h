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

// Shader
inline float g_Ambient[3] = { 1.0f, 1.0f, 1.0f };
inline float g_Diffuse[3] = { 1.0f, 1.0f, 1.0f };
inline float g_SpecularStrength = 0.5f;

inline float g_LightPosition[3] = { 0.0f, 1.0f, 0.0f };
inline float g_LightColor[3] = { 0.6f, 0.6f, 0.6f };