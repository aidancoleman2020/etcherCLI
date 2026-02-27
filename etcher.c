#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main() {
    char img_path[256];
    char dev_path[256];
    FILE *img, *dev;
    size_t bytes;
    char buffer[BUFFER_SIZE];

    printf("Enter path to image file: ");
    scanf("%255s", img_path);

    printf("Enter target device path (e.g., /dev/sdb): ");
    scanf("%255s", dev_path);

    img = fopen(img_path, "rb");
    if (!img) {
        perror("Error opening image file");
        return 1;
    }

    dev = fopen(dev_path, "wb");
    if (!dev) {
        perror("Error opening device");
        fclose(img);
        return 1;
    }

    printf("Flashing image...\n");
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, img)) > 0) {
        if (fwrite(buffer, 1, bytes, dev) != bytes) {
            perror("Write error");
            break;
        }
    }

    printf("Done!\n");
    fclose(img);
    fclose(dev);

    return 0;
}