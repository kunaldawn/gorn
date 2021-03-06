
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/FileLoader.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
#include <gorn/base/String.hpp>
#include <algorithm>

namespace gorn
{
    FileManager::FileManager():
    _files(std::make_shared<Files>())
    {
    }

    void FileManager::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader != nullptr)
        {
            _loaders[tag].push_back(std::move(loader));
        }
    }

    void FileManager::addLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        addLoader(String::kDefaultTag, std::move(loader));
    }

    void FileManager::setAlias(const std::string& name, const std::string& alias) NOEXCEPT
    {
        addFilter([name, alias](std::string& n) {
            return n == name ? alias : n;
        });
    }

    void FileManager::addFilter(const std::string& tag, const NameFilter& filter) NOEXCEPT
    {
        _filters[tag].push_back(filter);
    }

    void FileManager::addFilter(const NameFilter& filter) NOEXCEPT
    {
        addFilter(String::kDefaultTag, filter);
    }

    std::vector<FileManager::NameFilter>
        FileManager::getFilters(const std::pair<std::string, std::string>& parts)
        const NOEXCEPT
    {
        std::vector<NameFilter> filters;
        if(parts.first != String::kDefaultTag)
        {
            auto itr = _filters.find(parts.first);
            if(itr != _filters.end())
            {
                for(auto& filter : itr->second)
                {
                    filters.push_back(filter);
                }
            }
        }
        {
            auto itr = _filters.find(String::kDefaultTag);
            if(itr != _filters.end())
            {
                for(auto& filter : itr->second)
                {
                    filters.push_back(filter);
                }
            }
        }
        return filters;
    }

    std::string FileManager::applyFilters(const std::pair<std::string, std::string>& parts)
        const
    {
        auto name = parts.second;
        auto filters = getFilters(parts);
        for(auto& filter : filters)
        {
            if(filter != nullptr)
            {
                filter(name);
            }
        }
        return parts.first + String::kTagSeparator + name;
    }

    std::vector<std::shared_ptr<FileManager::Loader>> FileManager::getLoaders(
        const std::pair<std::string,std::string>& parts) const NOEXCEPT
    {
        std::vector<std::shared_ptr<Loader>> loaders;
        if(parts.first != String::kDefaultTag)
        {
            auto itr = _loaders.find(parts.first);
            if(itr != _loaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader);
                }
            }
        }
        {
            auto itr = _loaders.find(String::kDefaultTag);
            if(itr != _loaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader);
                }
            }
        }
        return loaders;
    }

    bool FileManager::validate(const std::string& name) const NOEXCEPT
    {
        auto files = _files;
        auto itr = files->find(name);
        if(itr != files->end())
        {
            return true;
        }

        auto parts = String::splitTag(name);
        auto fname = applyFilters(parts);
        if(fname != name)
        {
            return validate(fname);
        }
        auto loaders = getLoaders(parts);
        for(auto& loader : loaders)
        {
            if(loader->validate(parts.second))
            {
                return true;
            }
        }
        return false;
    }

    std::future<buffer> FileManager::load(const std::string& name, bool cache) NOEXCEPT
    {
        auto files = _files;
        auto itr = files->find(name);
        if(itr != files->end())
        {
            std::promise<buffer> p;
            p.set_value(itr->second);
            return p.get_future();
        }

        auto parts = String::splitTag(name);
        auto fname = applyFilters(parts);
        if(fname != name)
        {
            return load(fname, cache);
        }
        auto loaders = getLoaders(parts);
        for(auto& loader : loaders)
        {
            if(loader->validate(parts.second))
            {
                return load(loader, parts.second, cache);
            }
        }

        std::promise<buffer> p;
        p.set_exception(std::make_exception_ptr(
            Exception(std::string("Could not load file '")
            +parts.second+"' with tag '"+parts.first+"'.")));
        return p.get_future();
    }

    bool FileManager::unload(const std::string& name) NOEXCEPT
    {
        auto itr = _files->find(name);
        if(itr != _files->end())
        {
            _files->erase(itr);
            return true;
        }
        return false;
    }

    void FileManager::unloadAll() NOEXCEPT
    {
        _files->clear();
    }

    buffer fileLoadAsync(
      const std::shared_ptr<FileManager::Loader>& loader,
      const std::shared_ptr<FileManager::Files>& files,
      const std::string& name)
    {
        auto buffer = loader->load(name);
        if(files)
        {
            (*files)[name] = buffer;
        }
        return buffer;
    }

    std::future<buffer> FileManager::load(
        const std::shared_ptr<Loader>& loader,
        const std::string& name, bool cache)
    {
        auto files = cache?_files:nullptr;
        return std::async(std::launch::async, &fileLoadAsync,
          loader, files, name);
    }

    void FileManager::preload(const std::string& name, buffer&& data) NOEXCEPT
    {
        (*_files)[name] = std::move(data);
    }

}
