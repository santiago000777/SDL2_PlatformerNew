#pragma once
#include "MovableObject.h"

class Bubble : public MovableObject {
public:
	Bubble() = delete;
	Bubble(Vec4f box, const std::string& path, int characterWidth);
	Bubble(const Bubble& rhs) = delete;
	Bubble(Bubble&& rhs) = delete;
	~Bubble() override;
	void operator=(const Bubble& rhs) = delete;
	void operator=(Bubble&& rhs) = delete;

	void Update();
private:

};