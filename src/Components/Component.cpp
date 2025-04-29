#include "Component.h"

#include "Nodes/Node.h"

void Component::Detach()
{
	node->DetachComponent(this);
}
