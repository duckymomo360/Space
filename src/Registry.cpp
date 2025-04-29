#include "Registry.h"

#include "Components/Component.h"
#include "Components/VectorRenderer.h"
#include "Components/ParticleEmitter.h"
#include "Components/Editor.h"
#include "Components/SoundPlayer.h"

#include "Nodes/Node.h"
#include "Nodes/Spaceship.h"

#include <unordered_map>
#include <typeinfo>

#include <SDL3/SDL_log.h>

#define REGISTER(Class) \
	Register(typeid(Class), #Class)

namespace Registry
{

inline std::unordered_map<std::type_index, RegistryEntry> registry;

uint16_t idIndex = 0;

/**
 * Adds a class to the registry
 */
inline void Register(std::type_index typeIndex, const char* className)
{
	registry.emplace(typeIndex, RegistryEntry{
		typeIndex,
		className,
		idIndex++,
		});
}

/**
 * Registers the default engine Components to the registry
 */
inline void InitializeComponents()
{
	REGISTER(Component);
	REGISTER(VectorRendererComponent);
	REGISTER(ParticleEmitterComponent);
	REGISTER(EditorComponent);
	REGISTER(SoundPlayerComponent);
}

/**
 * Registers the default engine Nodes to the registry
 */
inline void InitializeNodes()
{
	REGISTER(Node);
	REGISTER(Spaceship);
}

void Initialize()
{
	InitializeComponents();
	InitializeNodes();

	SDL_Log("Registry Initialized");
}

} // namespace Registry
