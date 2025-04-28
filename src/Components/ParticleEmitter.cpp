#include "ParticleEmitter.h"
#include "Nodes/Node.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>

#include <random>

void ParticleEmitterComponent::OnUpdate(float dt) {
	if (emissionRate > 0 && emissionTimer.Elapsed() >= 1.0 / (double)emissionRate) {
		emissionTimer.Reset();
		Emit();
	}

	for (uint32_t i = 0; i < particles.size(); i++) {
		if (particles[i].lifeTimer.Elapsed() > lifetime)
		{
			particles.erase(particles.begin() + i);
			i--;
			continue;
		}

		particles[i].position += particles[i].velocity * dt;
	}
}

void ParticleEmitterComponent::OnDraw(SDL_Renderer* renderer) {
	for (auto& particle : particles) {
		particle.color.SetRenderDrawColor(renderer);

		SDL_RenderPoint(renderer,
			particle.position.x,
			particle.position.y);
	}
}

void ParticleEmitterComponent::Emit() {
	Particle particle;
	particle.position = node->globalPosition;
	particle.velocity = velocity;
	particle.color = Color3(255, 165, 0);

	particles.push_back(particle);
}

void ParticleEmitterComponent::Emit(uint32_t count) {
	for (int i = 0; i < count; i++) {
		Emit();
	}
}
