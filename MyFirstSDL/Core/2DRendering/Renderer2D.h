#pragma once
#include <vector>
#include <unordered_map>

class Renderer2D
{
public:
	Renderer2D(class Game* game);
	~Renderer2D();

	void PreRender(struct FColor color);
	void Render();
	void PostRender();

	void AddRenderComponent(class RenderComponent2D* sprite);
	bool RemoveRenderComponent(class RenderComponent2D* sprite);
	bool UpdateSpriteDrawOrder(class RenderComponent2D* sprite);

	struct SDL_Renderer* GetRenderer(){ return m_Renderer; }



private:
	class Game* m_Game = nullptr;
	struct SDL_Renderer* m_Renderer = nullptr;
	std::vector<class RenderComponent2D*> m_RenderComponents;
};

