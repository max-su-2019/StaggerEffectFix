#include "Hooks.h"

namespace SDF
{
	void MagicStaggerHook::Hooks::ProcessStagger::thunk(RE::Actor* a_target, float a_staggerMult, RE::Actor* a_aggressor)
	{
		if (a_target && a_target == a_aggressor) {
			a_aggressor = nullptr;  //Fix issue caused when aggressor is the same actor as target
		}

		func(a_target, a_staggerMult, a_aggressor);
	}

}
