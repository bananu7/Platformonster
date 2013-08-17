class World {
    std::vector<sf::Color> data;
    int sizeX, sizeY;
    int displaySizeX, displaySizeY;
    float tileSizeX, tileSizeY;
    sf::RenderWindow& window;

    sf::Color& get(int x, int y) { return data[sizeY * x + y]; }

public:
    void drawBlock(float x, float y, sf::Color c){
        sf::RectangleShape rectShape;
        rectShape.setSize(sf::Vector2f(tileSizeX, tileSizeY));
        rectShape.setFillColor(c);

        rectShape.setPosition(sf::Vector2f(x, y));
        window.draw(rectShape);
    }

    void draw(float deltaInWorld) {
        float pixelOffsetX = (deltaInWorld - std::floor(deltaInWorld)) * tileSizeX;
        int tileOffsetX = static_cast<int>(std::floor(deltaInWorld));

        for (int x = 0; x < displaySizeX; ++x){
            for (int y = 0; y < displaySizeY; ++y){
                auto color = get(x + tileOffsetX, y);

                float xPos = (x * tileSizeX) - pixelOffsetX;
                float yPos = (y * tileSizeY);

                drawBlock(xPos, yPos, color);
            }
        }
    }

    World(sf::RenderWindow& win) : sizeX(20), sizeY(5), window(win) {
        int windowSizeX = win.getSize().x, windowSizeY = win.getSize().y;
        tileSizeX = windowSizeX / 10; //fixed 10 tiles in window
        tileSizeY = windowSizeY / sizeY;

        displaySizeX = 10;
        displaySizeY = sizeY;

        data = std::vector<sf::Color>(sizeX * sizeY, sf::Color::Green);

        for (int i = 0; i < std::min(sizeX, sizeY); ++i)
            get(i, i) = sf::Color::Red;
    }
};
