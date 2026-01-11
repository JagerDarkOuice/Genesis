#include "material.h"
#include "stb_image.h"

Material::Material(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(
        filename,
        &width,
        &height,
        &channels,
        STBI_rgb_alpha
    );

    //make texture
    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    //upload texture data
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data);

    //free data
    stbi_image_free(data);

    //configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

Material::~Material() {
    glDeleteTextures(1, &textureId);
}

void Material::use(int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureId);
}
