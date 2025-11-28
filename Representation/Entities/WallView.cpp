//
// Created by toroe on 27/11/2025.
//

#include "../AssetManager.h"
#include "../Window.h"
#include "WallView.h"


WallView::WallView(const std::shared_ptr<logic::WallModel> &model, const std::shared_ptr<Camera> &camera, const char type) : EntityView(model, camera) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    int rectLeft, rectTop;

    switch (type) {
        case 't':
            rectLeft = 1;
            rectTop = 6; break;
        case 'b':
            rectLeft = 1;
            rectTop = 8; break;
        case 'l':
            rectLeft = 0;
            rectTop = 7; break;
        case 'r':
            rectLeft = 2;
            rectTop = 7; break;
        case 'm':
            rectLeft = 3;
            rectTop = 7; break;
        case 'e':
            rectLeft = 4;
            rectTop = 6; break;
        case 'f':
            rectLeft = 4;
            rectTop = 7; break;
        case 'h':
            rectLeft = 5;
            rectTop = 8; break;
        case 'j':
            rectLeft = 5;
            rectTop = 6; break;
        case 'k':
            rectLeft = 5;
            rectTop = 7; break;
        case 'u':
            rectLeft = 6;
            rectTop = 7; break;
        case 'i':
            rectLeft = 6;
            rectTop = 6; break;
        case 'o':
            rectLeft = 6;
            rectTop = 8; break;
        case 'p':
            rectLeft = 4;
            rectTop = 8; break;
        case '1':
            rectLeft = 0;
            rectTop = 6; break;
        case '2':
            rectLeft = 2;
            rectTop = 6; break;
        case '3':
            rectLeft = 2;
            rectTop = 8; break;
        case '4':
            rectLeft = 0;
            rectTop = 8; break;
        case '5':
            rectLeft = 3;
            rectTop = 6; break;
        case '6':
            rectLeft = 3;
            rectTop = 8; break;

        default: throw std::runtime_error("Invalid wall type");
    }

    sprite.setTextureRect(sf::IntRect(sf::IntRect(rectLeft * 16, rectTop * 16, 16, 16)));
}
