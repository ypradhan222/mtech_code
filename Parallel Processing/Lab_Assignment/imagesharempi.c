#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

int main() {
    MagickWand *wand;
    MagickWandGenesis();

    // Load an image from your local system
    wand = NewMagickWand();
    if (MagickReadImage(wand, "/Image Processing/media/download.jpeg") == MagickFalse) {
        printf("Error: Unable to load the image.\n");
        DestroyMagickWand(wand);
        MagickWandTerminus();
        return 1;
    }

    // Display the image (requires X server, you may need to run this code on a graphical environment)
    MagickDisplayImage(wand, "Display");

    // Clean up
    DestroyMagickWand(wand);
    MagickWandTerminus();

    return 0;
}

