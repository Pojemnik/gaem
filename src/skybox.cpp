#include "skybox.h"

Skybox::Skybox(std::vector<std::string> paths)
{
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

    for (unsigned int i = 0; i < paths.size(); i++)
    {
        std::vector<unsigned char> image;
        unsigned int width, height;
        unsigned int error = lodepng::decode(image, width, height, paths[i]);
        if (!error)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data()
            );
        }
        else
        {
            std::cout << "Skybox loading error. File: " << paths[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), _vertices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Skybox::draw(const Camera& camera, const Shader& shader)
{
    glDepthFunc(GL_LEQUAL);
    shader.use();
    mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
    shader.setUniformMatrix("P", camera.getPerspectiveMatrix());
    shader.setUniformMatrix("V", view);
    glBindVertexArray(_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
