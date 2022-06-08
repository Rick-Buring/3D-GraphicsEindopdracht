#pragma once
#include "GameObject.hpp"
#include "lightManager.hpp"
#include "InteractableGameObject.hpp"

class Button : public GameObject {
private:
	GameObject* _player;
	InteractableGameObject* _interactableObj;
	bool _interacted;
	double _lastClicked;
	lightInfo _light;

public:
	/// <summary>
	/// Creates button
	/// </summary>
	/// <param name="model">model to display in scene</param>
	/// <param name="player">player refrence</param>
	/// <param name="position">position in the world</param>
	/// <param name="interactableObj">object to interact with</param>
	Button(std::shared_ptr<std::vector<Model3D_t>> model, GameObject* player, glm::vec3 position, InteractableGameObject* interactableObj = nullptr);
	~Button();

	// Inherited via GameObject
	virtual void update(float deltaTime) override;
	virtual void draw() override;
};