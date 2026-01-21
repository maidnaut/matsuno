#pragma once

// SDL helper function
SDL_Texture* MatsunoGraphics::loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (!texture) {
        SDL_Log("Failed to load texture %s: %s", path, SDL_GetError());
        return nullptr;
    }
    return texture;
}

// Draw sprite
void MatsunoGraphics::drawSprite(SDL_Texture* image, float x, float y, float width, float height, float fade) {
    SDL_FRect dest = { x - width / 2.0f, y - height / 2.0f, width, height };
    SDL_FPoint center = { width / 2.0f, height / 2.0f };

    SDL_SetTextureAlphaMod(image, static_cast<Uint8>(fade * 255));
    SDL_RenderTextureRotated(renderer, image, nullptr, &dest, 0.0, &center, SDL_FLIP_NONE);
}

// Text Renderer
void MatsunoGraphics::drawText(const char *str, int x, int y, SDL_Color color, tAlign hAlign, tAlign vAlign) {
    if (!gfx.font || !str) return;

    int textWidth = 0, textHeight = 0;
    if (!TTF_GetStringSize(gfx.font, str, strlen(str), &textWidth, &textHeight)) {
        return;
    }

    if (hAlign == hLeft)   x += gfx.padding;
    if (hAlign == hCenter) x = (gfx.windowWidth - textWidth) / 2;
    if (hAlign == hRight)  x = gfx.windowWidth - textWidth - gfx.padding;

    if (vAlign == vTop)    y += gfx.padding;
    if (vAlign == vMiddle) y = (gfx.windowHeight - textHeight) / 2;
    if (vAlign == vBottom) y = gfx.windowHeight - textHeight - gfx.padding;

    SDL_Surface *surface = TTF_RenderText_Blended(gfx.font, str, strlen(str), color);
    if (!surface) return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) return;

    SDL_FRect dstRect = {
        (float)x,
        (float)y,
        (float)textWidth,
        (float)textHeight
    };

    SDL_RenderTexture(gfx.renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}

void MatsunoGraphics::drawSquares() {
    int width = 9;
    int height = 9;
    int size = 64;

    float startX = float(gfx.centerX - (size * width / 2));
    float startY = float(gfx.centerY - (size * height / 2));

    for (int x = 0; x < width; x++) {
        float currentX = startX + x * size;
        float currentY = startY;

        for (int y = 0; y < height; y++) {
            int random = (rand() % 8) + 1;
            SDL_Color color = colors.white;

            switch (random) {
                case 2: color = colors.yellow; break;
                case 3: color = colors.pink; break;
                case 4: color = colors.red; break;
                case 5: color = colors.green; break;
                case 6: color = colors.skyblue; break;
                case 7: color = colors.purple; break;
                case 8: color = colors.brown; break;
            }

            SDL_SetRenderDrawColor(gfx.renderer, color.r, color.g, color.b, color.a);

            SDL_FRect rect = { currentX, currentY, float(size), float(size) };
            SDL_RenderRect(gfx.renderer, &rect); // SDL3 correct function

            currentY += size;
        }
    }
}

// void MatsunoGraphics::drawTextbox(const char *str, textboxPosition textboxPosition, tAlign hAlign, tAlign vAlign, bool typewriter) {
    
//     // Formatting
//     int textboxWidth = gfx.windowWidth - (gfx.padding * 2);
//     int textboxHeight = 200;
//     int textboxX = gfx.padding;
//     int textboxY = gfx.windowHeight - textboxHeight - gfx.padding;
//     int textX = textboxX + gfx.padding;
//     int textY = textboxY + gfx.padding;
//     int textWidth = textboxWidth - (gfx.padding * 2);
//     int textHeight = textboxHeight - (gfx.padding * 2);
// }

// void MatsunoGraphics::drawRectangleTextured(Texture2D image, Rectangle dest, Vector2 origin, float rotation, float alpha) {
//     Rectangle source = { 0, 0, (float)image.width, (float)image.height };
//     Color tint = (Color){ 255, 255, 255, (unsigned char)(alpha * 255) };
//     DrawTexturePro(image, source, dest, origin, rotation, tint);
// }