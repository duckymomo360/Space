#include "ParticleEmitter.h"

#include "Renderer/Renderer.h"
#include "Nodes/Node.h"

#include <random>

void ParticleEmitterComponent::OnUpdate(float dt)
{
	if (emissionRate > 0 && emissionTimer.Elapsed() >= 1.0 / (double)emissionRate)
	{
		emissionTimer.Reset();
		Emit();
	}

	for (uint32_t i = 0; i < particles.size(); i++)
	{
		if (particles[i].lifeTimer.Elapsed() > lifetime)
		{
			particles.erase(particles.begin() + i);
			i--;
			continue;
		}

		particles[i].position += particles[i].velocity * dt;
	}
}

void ParticleEmitterComponent::OnDraw(Renderer* renderer)
{
	for (auto& particle : particles)
	{
		renderer->RenderPoint(particle.position, particle.color);
	}
}

void ParticleEmitterComponent::Emit()
{
	Particle particle;
	particle.position = node->globalPosition;
	particle.velocity = velocity;
	particle.color = Color4(255, 165, 0, 255);

	particles.push_back(particle);
}

void ParticleEmitterComponent::Emit(uint32_t count)
{
	for (int i = 0; i < count; i++) {
		Emit();
	}
}
