#include "Application.h"

#include "Core/Logging/Log.h"
#include "Core/Platform/Platform.h"
#include "Core/Types/Function.h"
#include "Core/Types/PrimitiveTypes.h"

#include "Core/FileSystem/FileSystem.h"
#include "Core/FileSystem/FileSystemTest.h"

#include "Resources/Resources.h"

#include "Core/InputSystem/InputSystem.h"
#include "Render/RenderingSystem.h"

#include "Entities/EntityAdmin.h"

#include <GLFW/glfw3.h>

namespace Cookie {

	AppData g_AppData;
	EntityAdmin *g_Admin = new EntityAdmin();
	RenderingSystem *g_RenderingSystem = new RenderingSystem();

	namespace Application {

		void Run(GameInitData *gameInitData) {

			Log::Initialize();

			CKE_LOG_INFO(Log::Channel::Core, "Starting up Cookie Engine");
			Platform::Init(&gameInitData->m_WindowDesc);

			CKE_LOG_INFO(Log::Channel::Core, "Initializing Input System");
			InputSystem::Init(&g_AppData.m_Window);

			CKE_LOG_INFO(Log::Channel::Core, "Initializing Rendering System");
			g_RenderingSystem->Init();

			CKE_LOG_INFO(Log::Channel::Core, "Initializing Resources System");
			ResourcesSystem::Init();

			CKE_LOG_INFO(Log::Channel::Core, "Initializing Entity Admin");
			g_Admin->Init();
			g_Admin->RegisterComponent<TransformComponent>();
			g_Admin->RegisterComponent<RenderComponent>();
			g_Admin->RegisterSystem(g_RenderingSystem);

			CKE_LOG_INFO(Log::Channel::Core, "Loading Game Resources");
			gameInitData->m_LoadResourcesFunc();

			CKE_LOG_INFO(Log::Channel::Core, "Creating Game World");
			gameInitData->m_CreateWorldFunc(g_Admin);

			CKE_LOG_INFO(Log::Channel::Core, "Starting engine loop");
			g_EngineClock.Init();

			while (Platform::IsRunning(g_AppData.m_Window.m_Handle)) {

				// Tick the engine clock
				g_EngineClock.Update();

				InputSystem::Update();
				g_Admin->Update(g_EngineClock.m_TimeData.m_DeltaTime);
				g_RenderingSystem->Update(g_EngineClock.m_TimeData.m_DeltaTime);
			}

			// Shutdown
			CKE_LOG_INFO(Log::Channel::Core, "Shutting down");
			g_RenderingSystem->Shutdown();
			InputSystem::Shutdown();
			Platform::Shutdown();
			ResourcesSystem::Shutdown();
			Log::Shutdown();

			delete g_Admin;
			delete g_RenderingSystem;
		}

	} // namespace Application
} // namespace Cookie