//
// Note:	this file is to be included in client applications ONLY
//			NEVER include this file anywhere in the engine codebase
//
#pragma once

#include "Nu/Core/Application.h"
#include "Nu/Core/Log.h"

#include "Nu/Core/Events/Event.h"
#include "Nu/Core/Events/ApplicationEvent.h"
#include "Nu/Core/Events/KeyEvent.h"
#include "Nu/Core/Events/MouseEvent.h"

#include "imgui/imgui.h"

// --- Nu Render API ------------------------------
#include "Nu/Renderer/Renderer.h"
#include "NU/Renderer/Framebuffer.h"
#include "Nu/Renderer/Buffer.h"
#include "Nu/Renderer/Texture.h"
#include "Nu/Renderer/Shader.h"
#include "Nu/Renderer/Mesh.h"
#include "Nu/Renderer/Camera.h"
// ---------------------------------------------------

// --- Entry Point ------------
#include "Nu/EntryPoint.h"
// ----------------------------