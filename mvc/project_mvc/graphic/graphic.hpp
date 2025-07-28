#pragma once

struct RGB {
    int R;
    int G;
    int B;
};

class IGraphic {

public:
    virtual void drawOval(int x, int y, int R) = 0;

    virtual void drawRect(int x, int y, int Height, int Width) = 0;

    virtual void fillRect(int x, int y, int Height, int Width) = 0;
};

class GraphicSimple : public IGraphic
{

    virtual void drawOval(int x, int y, int R) {}

    virtual void drawRect(int x, int y, int Height, int Width) {}

    virtual void fillRect(int x, int y, int Height, int Width) {}
};
