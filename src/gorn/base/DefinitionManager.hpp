#ifndef __gorn__DefinitionManager__
#define __gorn__DefinitionManager__

#include <map>
#include <memory>
#include <functional>
#include <gorn/base/String.hpp>

namespace gorn
{
    template<typename D>
    class DefinitionManager
    {
    public:
        typedef D Definition;
        typedef std::function<Definition(const std::string&)> Builder;
    private:
        std::map<std::string, Definition> _definitions;
        std::map<std::string, Builder> _builders;

    public:
        DefinitionManager();

        Definition& get(const std::string& name);
        const Definition& get(const std::string& name) const;
        void set(const Builder& builder);
        void set(const std::string& tag, const Builder& builder);

    };

    template<typename D>
    DefinitionManager<D>::DefinitionManager()
    {
    } 

    template<typename D>
    typename DefinitionManager<D>::Definition& DefinitionManager<D>::get(
        const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            auto parts = String::splitTag(name);
            auto bitr = _builders.find(parts.first);
            if(bitr == _builders.end())
            {
                bitr = _builders.find(String::kDefaultTag);
            }
            if(bitr != _builders.end())
            {
                auto def = bitr->second(name);
                itr = _definitions.insert(itr, {name, def});
            }
            else
            {
                itr = _definitions.insert(itr, {name, Definition()});
            }
        }
        return itr->second;
    }

    template<typename D>
    const typename DefinitionManager<D>::Definition& DefinitionManager<D>::get(
        const std::string& name) const
    {
        return _definitions.at(name);
    }

    template<typename D>
    void DefinitionManager<D>::set(const Builder& builder)
    {
        set(String::kDefaultTag, builder);
    }

    template<typename D>
    void DefinitionManager<D>::set(const std::string& prefix,
        const Builder& builder)
    {
        _builders[prefix] = builder;
    }

}

#endif