#include <importer/asset_manager.h>

Importer::AssetManager& Importer::AssetManager::GetInstance()
{
    static AssetManager instance;
    return instance;
}

void Importer::AssetManager::LoadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "[ASSIMP ERROR] " << importer.GetErrorString() << std::endl;
        return;
    }

    model.name.clear();
    model.path.clear();
    model.meshes.clear();

    std::string name = Util::GetFileNameFromPath(path);

    model.name = name;
    model.path = Util::GetDirectoryFromPath(path);

    ProcessNode(scene->mRootNode, scene);

    models.insert({name, std::make_unique<Model>(model)});
}

Texture* Importer::AssetManager::LoadTexture(const std::string& path)
{
    auto it = textures.find(Util::GetFileNameFromPath(path));
    
    if(it != textures.end())
        return it->second.get();

    std::unique_ptr<Texture> texture = std::make_unique<Texture>();

    texture->data = stbi_load(path.c_str(), &texture->width, &texture->height, &texture->channels, 0);

    if(!texture->data)
    {
        std::cerr << "[STB ERROR] Error on loading image" << std::endl;
    }

    Texture* result = texture.get();

    textures.insert({Util::GetFileNameFromPath(path), std::move(texture)});

    return result;
}

void Importer::AssetManager::ProcessNode(aiNode* node, const aiScene* scene)
{
    for(int i=0; i<node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    for(int i=0; i<node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void Importer::AssetManager::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    Mesh m;
    Vertex v;
    Material mat;

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

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    aiString name;

    material->GetTexture(aiTextureType_DIFFUSE, 0, &name);
    Texture* texture = LoadTexture(model.path + name.C_Str());
    mat.texture = texture;
    m.material = mat;

    model.meshes.push_back(m);
}