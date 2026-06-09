#include <renderer/renderer.h>

Shader* shader;

Renderer& Renderer::GetInstance()
{
    static Renderer instance;
    return instance;
}

void Renderer::Init()
{
    shader = new Shader("/home/flektos/Documents/Slenderer2025/res/shaders/basic1.vs", "/home/flektos/Documents/Slenderer2025/res/shaders/basic1.fs");
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Destroy()
{

}

void Renderer::DrawEntity(Entity* entity, Camera& camera)
{
    if(!entity) return;

    shader->use();
    shader->setMatrix44f("model", entity->transformComponent.toMat4());
    shader->setMatrix44f("view", camera.GetViewMatrix());
    shader->setMatrix44f("projection", glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f));

    for(int i=0; i<entity->model->meshes.size(); i++)
    {
        MeshGPU meshGPU = GetOrUploadMeshGPU(entity->model->meshes[i]);
        TextureGPU textureGPU = GetOrUploadTextureGPU(entity->model->meshes[i].material.albedo);
        glBindVertexArray(meshGPU.VAO);
        glDrawElements(GL_TRIANGLES, entity->model->meshes[i].indices.size(), GL_UNSIGNED_INT, (void*)0);
    }
}


MeshGPU Renderer::GetOrUploadMeshGPU(Mesh& mesh)
{
    auto it = meshesGPU.find(mesh.id);
    if(it != meshesGPU.end()) 
        return it->second;
    
    MeshGPU meshGPU = {0};

    glGenVertexArrays(1, &meshGPU.VAO);
    glGenBuffers(1, &meshGPU.VBO);
    glGenBuffers(1, &meshGPU.EBO);
  
    glBindVertexArray(meshGPU.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshGPU.VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshGPU.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), 
                 &mesh.indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 3)); 
    glEnableVertexAttribArray(1); 
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 5)); 
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 8)); 
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 11)); 
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);

    meshesGPU.insert({mesh.id, meshGPU});

    return meshGPU;
}

TextureGPU Renderer::GetOrUploadTextureGPU(Texture* texture)
{
    auto it = texturesGPU.find(texture->id);
    if(it != texturesGPU.end()) 
        return it->second;

    TextureGPU textureGPU = {0};

    glGenTextures(1, &textureGPU.id);
    glBindTexture(GL_TEXTURE_2D, textureGPU.id);
   
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    texturesGPU.insert({texture->id, textureGPU});

    return textureGPU;
}

void Renderer::ClearColorDepth()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}