#include "util.hpp"
#include <array>

#define LAYER_WIDTH 25
#define LAYER_HEIGHT 6
#define LAYER_SIZE (LAYER_WIDTH * LAYER_HEIGHT)

typedef std::array<int, LAYER_SIZE> Layer;
typedef std::vector<Layer> Image;

void printLayer(const Layer &layer)
{
    for (size_t y = 0; y < LAYER_HEIGHT; y++) {
        for (size_t x = 0; x < LAYER_WIDTH; x++) {
            const auto pixel = layer[y * LAYER_WIDTH + x];
            if (pixel == 0)
                printf("\033[40m%c", ' ');
            else if (pixel == 1)
                printf("\033[47m%c", ' ');
            else
                printf("\033[49m%d", pixel);
        }
        printf("\033[49m\n");
    }
}

uint32_t countDigits(const Layer &l, const int d)
{
    uint32_t c = 0;
    for (const auto &ld : l)
        if (ld == d) c++;
    return c;
}

size_t findLeastCorruptedIndex(const Image &ls)
{
    uint32_t index = 0;
    uint32_t c = UINT32_MAX;
    for (size_t i = 0; i < ls.size(); i++) {
        const auto digitCount = countDigits(ls[i], 0);
        if (digitCount < c) {
            c = digitCount;
            index = i;
        }
    }
    return index;
}

Layer mergeLayers(const Image &ls)
{
    Layer result = ls.back();
    for (int i = ls.size() - 2; i >= 0; i--) {
        for (size_t pi = 0; pi < LAYER_SIZE; pi++) {
            const auto pixel = ls[i][pi];
            if (pixel == 2) continue;
            result[pi] = pixel;
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 8\n");

    const auto input = readFile(argv[1])[0];
    const auto layerCount = input.size() / LAYER_SIZE;
    
    Image image(layerCount);
    for (size_t i = 0; i < layerCount; i++) {
        for (size_t y = 0; y < LAYER_HEIGHT; y++) {
            for (size_t x = 0; x < LAYER_WIDTH; x++) {
                const auto pos = (y * LAYER_WIDTH + x);
                image[i][pos] = input[i * LAYER_SIZE + pos] - '0';
            }
        }
    }

    const auto leastCorruptedIndex = findLeastCorruptedIndex(image);
    const auto &leastCorruptedLayer = image[leastCorruptedIndex];
    printf("Part 1: %d\n", countDigits(leastCorruptedLayer, 1) * countDigits(leastCorruptedLayer, 2));
    printf("Part two:\n");
    printLayer(mergeLayers(image));
}