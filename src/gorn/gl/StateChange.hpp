#ifndef __gorn__StateChange__
#define __gorn__StateChange__

#include <gorn/gl/Enums.hpp>
#include <glm/glm.hpp>
#include <unordered_map>

namespace gorn
{
    class StateChange
    {
    public:
        typedef std::unordered_map<TestType, bool> TestChanges;
        typedef std::unordered_map<MaskType, bool> MaskChanges;
    private:
        TestChanges _tests;
        MaskChanges _masks;
    public:
        StateChange();

        StateChange& withEnable(TestType type);
        StateChange& withDisable(TestType type);
        StateChange& withEnable(MaskType type);
        StateChange& withDisable(MaskType type);

        bool operator==(const StateChange& other) const;
        bool operator!=(const StateChange& other) const;
        
        void apply();
		void apply(const StateChange& old);
    };

}

#endif
