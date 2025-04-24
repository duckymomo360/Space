#include "ParticleEmitter.h"
#include "Nodes/Node.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>

#include <random>

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

void ParticleEmitterComponent::Emit(Vector2 velocity) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(-0.3f, 0.3f);

	Particle particle;
	particle.position = node->globalPosition;
	particle.velocity = Vector2::FromAngle(node->globalRotation + dist(gen) * M_PI) * 50.0f;
	particle.color = Color3(255, 165, 0);

	particles.push_back(particle);
}

void ParticleEmitterComponent::Emit() {
	Emit(Vector2::Zero);
}

void ParticleEmitterComponent::Emit(uint32_t count) {
	for (int i = 0; i < count; i++) {
		Emit();
	}
}

