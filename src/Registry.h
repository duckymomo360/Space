#pragma once

#include <typeindex>
#include <cstdint>

namespace Registry
{

struct RegistryEntry
{
	const std::type_index typeIndex;

	const char* className;

	const uint16_t serializationId;
};

/**
 * Initializes the registry
 */
void Initialize();

} // namespace Registry
