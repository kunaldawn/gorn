#ifndef __gorn__MaterialManager__
#define __gorn__MaterialManager__

#include <map>
#include <memory>
#include <gorn/gl/MaterialDefinition.hpp>
#include <gorn/base/DefinitionManager.hpp>
#include <glm/glm.hpp>

namespace gorn
{
    class ProgramManager;
    class TextureManager;
    class Material;

    class MaterialManager
    {
    public:
        typedef MaterialDefinition Definition;
        typedef DefinitionManager<MaterialDefinition> Definitions;
    private:
        std::map<std::string, std::shared_ptr<Material>> _materials;
        ProgramManager& _programs;
        TextureManager& _textures;
        Definitions _definitions;

    public:

        MaterialManager(ProgramManager& programs, TextureManager& textures);

        const ProgramManager& getPrograms() const;
        ProgramManager& getPrograms();

        const TextureManager& getTextures() const;
        TextureManager& getTextures();

        const Definitions& getDefinitions() const;
        Definitions& getDefinitions();

        bool validate(const std::string& name) const;
        std::shared_ptr<Material> load(const std::string& name);
        glm::vec2 loadSize(const std::string& name);
        void preload(const std::string& name, std::shared_ptr<Material> material);
    };

}

#endif
