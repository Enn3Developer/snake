#ifndef COLORPAIR_H
#define COLORPAIR_H

class ColorPair
{
public:
    short foreground;
    short background;

    ColorPair(short foreground, short background);
    explicit ColorPair(short foreground);
    ColorPair();
    bool operator==(const ColorPair& color_pair) const;
};

#endif
