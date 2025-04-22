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
	particle.velocity = Vector2::FromAngle(node->globalRotation + ((float)std::rand() / (float)RAND_MAX)) * 50.0f;
	particle.color = Color3(255, 165, 0);

	particles.push_back(particle);
}

void ParticleEmitterComponent::Emit(uint32_t count) {
	for (int i = 0; i < count; i++) {
		Emit();
	}
}

