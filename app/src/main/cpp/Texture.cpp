/* [includeTextureDefinition] */
#include "Texture.h"

#include <GLES2/gl2ext.h>

unsigned char * textureData;
GLuint textureId;

char filePaths[numTextures][100]= {
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/1.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/2.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/3.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/4.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/5.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/6.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/7.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/8.raw",
        "/data/user/0/com.arm.malideveloper.openglessdk.textureanimation/files/9.raw",
};


bool readTextureFile(char* filePath, unsigned char* data) {
    FILE *file;
    file = fopen(filePath, "rb");
    if (file == NULL) {
        return 1;
    }
    fread(data, textureChannels, textureWidth * textureHeight, file);
    fclose(file);
    return 0;
}


bool readTextureFiles() {
    textureData = (unsigned char *) malloc(textureDataSize * numTextures);
    for (int textureIndex = 0; textureIndex < numTextures; ++textureIndex){
        char* filePath = filePaths[textureIndex];
        unsigned char *data = textureData + textureDataSize * textureIndex;
        readTextureFile(filePath, data);
    }
    return true;
}


bool loadTextureFromData(int width, int height, int textureIndex, int textureUnitIndex, bool update) {
    unsigned char *data = textureData + textureDataSize * textureIndex;

    /* Texture Object Handle. */
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (!update) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}


bool loadTexturesFromData() {
    for (int i = 0; i < numTextures; ++i) {
        loadTextureFromData( 256 , 256 , i, i, false) ; // Load first texture
    }

    return true;
}

