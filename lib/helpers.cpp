// Text Renderer
void Matsuno::drawText(const char *str, int x, int y, int size, Color color, tAlign hAlign, tAlign vAlign) {

    int textWidth = MeasureText(str, size);
    int textHeight = size;

    // Horizontal alignment
    if (hAlign == hLeft) x = x + matsuno.padding;
    if (hAlign == hCenter) x = (matsuno.windowWidth - textWidth) / 2;
    if (hAlign == hRight) x = matsuno.windowWidth - textWidth - matsuno.padding;

    // Vertical alignment
    if (vAlign == vTop) y = y + matsuno.padding;
    if (vAlign == vMiddle) y = (matsuno.windowHeight - textHeight) / 2;
    if (vAlign == vBottom) y = matsuno.windowHeight - textHeight - matsuno.padding;

    // Draw the text
    DrawText(str, x, y, size, color);
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

void drawRectangleTextured(Texture2D image, Rectangle dest, Vector2 origin, float rotation, float alpha) {
    Rectangle source = { 0, 0, (float)image.width, (float)image.height };
    Color tint = (Color){ 255, 255, 255, (unsigned char)(alpha * 255) };
    DrawTexturePro(image, source, dest, origin, rotation, tint);
}

void drawSquares() {
    int width = 9;
    int height = 9;
    int size = 64;

    int startX = matsuno.centerX - (size * width / 2);
    int startY = matsuno.centerY - (size * height / 2);

    for (int x = 0; x < width; x++) {
            
        int currentY = startY;
        int currentX = startX + x * size;
        
        for (int y = 0; y < height; y++) {

            int random = (rand() % 8) + 1;
            Color color = WHITE;

            if (random == 1) color = WHITE;
            if (random == 2) color = YELLOW;
            if (random == 3) color = PINK;
            if (random == 4) color = RED;
            if (random == 5) color = GREEN;
            if (random == 6) color = SKYBLUE;
            if (random == 7) color = PURPLE;
            if (random == 8) color = BROWN;

            DrawRectangleLines(
                currentX,
                currentY,
                size,
                size,
                color
            );
            currentY += size;
        }
    }
}