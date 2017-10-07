#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

#include "ImportExport.h"
#include "Component.h"
#include "Camera.h"
#include "Input.h"
#include "Time.h"

class LQN_API CameraMovement : public Component {
public:
	CameraMovement(Graphics* graphics,Camera* rcamera, Input* rinput) : Component(graphics) {
		camera = rcamera;
		input = rinput;
	}

	void Update() {

		input->GetMouseLocation(mouseX, mouseY);

		float mouseSens = 0.05;
		//First Person Rotation
		if (mouseX != lastMouseX) {
			camera->Yaw((mouseX - lastMouseX)*mouseSens * Time::deltaTime);
		}

		if (mouseY != lastMouseY) {
			camera->Pitch((mouseY - lastMouseY) * mouseSens * Time::deltaTime);
		}

		lastMouseX = mouseX;
		lastMouseY = mouseY;
		camera->SetRightVectorYCoord(0);
		if (input->GetKey(KeyCode::Y)) {
			camera->Roll(5 * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::H)) {
			camera->Roll(-5 * Time::deltaTime);
		}


		//First Person Movement
		if (input->GetKey(KeyCode::W)) {
			camera->MoveForward(5 * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::S)) {
			camera->MoveForward(-5 * Time::deltaTime);
		}
		if (input->GetKey(KeyCode::D)) {
			camera->MoveRight(5 * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::A)) {
			camera->MoveRight(-5 * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::Q)) {
			camera->MoveUp(5 * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::E)) {
			camera->MoveUp(-5 * Time::deltaTime);
		}

		Component::Update();
	}

private:
	Camera * camera;
	Input * input;
	int mouseX;
	int mouseY;
	int lastMouseX;
	int lastMouseY;
};


#endif