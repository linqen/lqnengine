#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

#include "ImportExport.h"
#include "Component.h"
#include "Camera.h"
#include "Input.h"
#include "Time.h"

class LQN_API CameraMovement : public Component {
public:
	CameraMovement(Graphics* graphics,Camera* rcamera, Input* rinput, float rkeyMovementSpeed) : Component(graphics) {
		camera = rcamera;
		input = rinput;
		keyMovementSpeed = rkeyMovementSpeed;
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
			camera->Roll(keyMovementSpeed * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::H)) {
			camera->Roll(-keyMovementSpeed * Time::deltaTime);
		}


		//First Person Movement
		if (input->GetKey(KeyCode::W)) {
			camera->MoveForward(keyMovementSpeed * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::S)) {
			camera->MoveForward(-keyMovementSpeed * Time::deltaTime);
		}
		if (input->GetKey(KeyCode::D)) {
			camera->MoveRight(keyMovementSpeed * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::A)) {
			camera->MoveRight(-keyMovementSpeed * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::Q)) {
			camera->MoveUp(keyMovementSpeed * Time::deltaTime);
		}

		if (input->GetKey(KeyCode::E)) {
			camera->MoveUp(-keyMovementSpeed * Time::deltaTime);
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
	float keyMovementSpeed;
};


#endif