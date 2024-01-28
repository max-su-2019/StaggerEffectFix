#include "Hooks.h"
#include "Patches.h"

DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif

	DKUtil::Logger::Init(Plugin::NAME, REL::Module::get().version().string());

	//REL::Module::reset();
	SKSE::Init(a_skse);

	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	// do stuff
	SDF::AddStaggerActorPatch::Install();
	SDF::MagicStaggerHook::InstallHooks();

	auto g_message = SKSE::GetMessagingInterface();
	if (!g_message) {
		ERROR("Messaging Interface Not Found!");
		return false;
	}

	g_message->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
		if (msg->type == SKSE::MessagingInterface::kPostLoad) {
			static constexpr auto redundantDLLName = "MaxsuStaggerDirFix.dll";
			auto redundantPlugin = GetModuleHandleA(redundantDLLName);
			if (redundantPlugin) {
				ERROR("Redundant plugin \"{}\" Loaded, please delete the redundant mod first!", redundantDLLName);
			}
		}
	});

	return true;
}
