#include "ParticleEmitter.h"
#include "Nodes/Node.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>

void ParticleEmitterComponent::Update(float dt) {
	for (auto& particle : particles) {
		particle.position += particle.velocity * dt;
	}
}

void ParticleEmitterComponent::Draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (auto& particle : particles) {
		SDL_RenderPoint(renderer,
			node->globalPosition.x + particle.position.x,
			node->globalPosition.y + particle.position.y);
	}
}

void ParticleEmitterComponent::Emit() {
	Particle particle;
	particle.position = Vector2::Zero;
	particle.velocity = Vector2::One * 1.0f;

	particles.push_back(particle);
}

void ParticleEmitterComponent::Emit(uint32_t count) {
	for (int i = 0; i < count; i++) {
		Emit();
	}
}

