#include <importer/asset_manager.h>

Importer::AssetManager& Importer::AssetManager::GetInstance()
{
    static AssetManager instance;
    return instance;
}

Model* Importer::AssetManager::LoadModel(const std::string& path)
{
    auto it = models.find(Util::GetFileNameFromPath(path));
    
    if(it != models.end())
        return it->second.get();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "[ASSETMANAGER ERROR] " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::unique_ptr<Model> model = std::make_unique<Model>();
    Model* rawModel = model.get();

    std::string name = Util::GetFileNameFromPath(path);

    model->name = name;
    model->path = Util::GetDirectoryFromPath(path);
    model->id   = modelID++;

    ProcessNode(scene->mRootNode, scene, rawModel);

    models.insert({name, std::move(model)});

    return rawModel;
}

Texture* Importer::AssetManager::LoadTexture(const std::string& path)
{
    auto it = textures.find(Util::GetFileNameFromPath(path));
    
    if(it != textures.end())
        return it->second.get();

    std::unique_ptr<Texture> texture = std::make_unique<Texture>();

    stbi_set_flip_vertically_on_load(true);
    texture->data = stbi_load(path.c_str(), &texture->width, &texture->height, &texture->channels, 0);
    
    if(!texture->data)
    {
        std::cerr << "[ASSETMANAGER ERROR] Error on loading image" << std::endl;
        return nullptr;
    }

    texture->id = textureID++;

    Texture* rawTexture = texture.get();

    textures.insert({Util::GetFileNameFromPath(path), std::move(texture)});

    return rawTexture;
}

void Importer::AssetManager::ProcessNode(aiNode* node, const aiScene* scene, Model* model)
{
    for(int i=0; i<node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene, model);
    }

    for(int i=0; i<node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, model);
    }
}

void Importer::AssetManager::ProcessMesh(aiMesh* mesh, const aiScene* scene, Model* model)
{
    Mesh m;
    Vertex v;
    Material mat = {0};

    for(int i=0; i<mesh->mNumVertices; i++)
    {
        v.position.x = mesh->mVertices[i].x;
        v.position.y = mesh->mVertices[i].y;
        v.position.z = mesh->mVertices[i].z;

        if(mesh->HasNormals())
        {
            v.normal.x = mesh->mNormals[i].x;
            v.normal.y = mesh->mNormals[i].y;
            v.normal.z = mesh->mNormals[i].z;
        }

        if(mesh->mTextureCoords[0])
        {
            v.textureCoordinates.x = mesh->mTextureCoords[0][i].x;
            v.textureCoordinates.y = mesh->mTextureCoords[0][i].y;
        
            v.tangent.x            = mesh->mTangents[i].x;
            v.tangent.y            = mesh->mTangents[i].y;
            v.tangent.z            = mesh->mTangents[i].z;
        
            v.bitangent.x          = mesh->mBitangents[i].x;
            v.bitangent.y          = mesh->mBitangents[i].y;
            v.bitangent.z          = mesh->mBitangents[i].z;
        }else
        {
            v.textureCoordinates  = glm::vec2(0.0f);
        }

        m.vertices.push_back(v);
    }

    if(mesh->HasFaces())
    {
        for(int i=0; i<mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(int j=0; j<face.mNumIndices; j++)
            {
                m.indices.push_back(face.mIndices[j]);
            }
        }

    }

    ProcessMaterial(mesh, scene, model, mat);

    m.material = mat;
    m.id       = meshID++;

    model->meshes.push_back(m);
}

void Importer::AssetManager::ProcessMaterial(aiMesh* mesh, const aiScene* scene, Model* model, Material& material)
{
    if(mesh->mMaterialIndex < 0)
        return;

    aiMaterial* m = scene->mMaterials[mesh->mMaterialIndex];
    aiString name;

    int diffuseCount = m->GetTextureCount(aiTextureType_DIFFUSE);
    if(diffuseCount > 0)
    {
        m->GetTexture(aiTextureType_DIFFUSE, 0, &name);
        material.albedo = LoadTexture(model->path + name.C_Str());
    }

    int specularCount = m->GetTextureCount(aiTextureType_SPECULAR);
    if(specularCount > 0)
    {
        m->GetTexture(aiTextureType_SPECULAR, 0, &name);
        material.specular = LoadTexture(model->path + name.C_Str());
    }

    int heightCount = m->GetTextureCount(aiTextureType_HEIGHT);
    if(heightCount > 0)
    {
        m->GetTexture(aiTextureType_HEIGHT, 0, &name);
        material.normal = LoadTexture(model->path + name.C_Str());
    }

}

Model* Importer::AssetManager::GetModel(const std::string& name)
{
    auto it = models.find(name);
    
    if(it != models.end())
        return it->second.get();

    std::cerr << "[ASSETMANAGER ERROR] Could not find model with name " <<  name << std::endl;

    return nullptr;
}

Texture* Importer::AssetManager::GetTexture(const std::string& name)
{
    auto it = textures.find(name);
    
    if(it != textures.end())
        return it->second.get();

    std::cerr << "[ASSETMANAGER ERROR] Could not find texture with name " <<  name << std::endl;

    return nullptr;

}