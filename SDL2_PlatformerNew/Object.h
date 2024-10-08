#pragma once
#include "common.h"
#include "Picture.h"
#include "Circle.h"

class Object {
public:
    Object() = delete;
    Object(Vec4f box, const std::string& path, int characterWidth);
    Object(const Object& rhs) = delete;
    Object(Object&& rhs) = delete;
    virtual ~Object() = default;
    void operator=(const Object& rhs) = delete;
    void operator=(Object&& rhs) = delete;

    void Render();
    enum eIndex : int {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    Vec4f GetBox() const;

    int GetSpriteWidth() const;
    int GetCurrentSprite() const;
    void ChangeSprite();

    static bool Collision(const Object& object, const Circle& circle);

    bool isAlive = true;
protected:

    Vec4f box;//s
    SDL_Rect srcBox;

    bool isDestroyble = false;

    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, DeleteTexture };

    int currentSprite = 0;//s
private:
    int sprites = 0;
};