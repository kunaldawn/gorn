#include <gorn/gl/AttributeTransformation.hpp>
#include <gorn/gl/VertexAttributeDefinition.hpp>
#include <buffer.hpp>

namespace gorn
{
	void AttributeTransformation::position(const Definition& def, buffer& elms, const glm::mat4& trans)
	{
		auto n = elms.size() / def.getElementSize();
		if (def.getBasicType() == BasicType::Float)
		{
			if (def.getCount() == 3)
			{
				auto array = reinterpret_cast<glm::vec3*>(elms.data());
				for (size_t i = 0; i < n; i++)
				{
					auto& elm = array[i];
					elm = glm::vec3(trans*glm::vec4(elm, 1.0f));
				}
				return;
			}
			if (def.getCount() == 2)
			{
				auto array = reinterpret_cast<glm::vec2*>(elms.data());
				for (size_t i = 0; i < n; i++)
				{
					auto& elm = array[i];
					elm = glm::vec2(trans*glm::vec4(elm, 0.0f, 1.0f));
				}
				return;
			}
		}
	}

	void AttributeTransformation::normal(const Definition& def, buffer& elms, const glm::mat4& trans)
	{
		auto n = elms.size() / def.getElementSize();
		if (def.getBasicType() == BasicType::Float)
		{
			if (def.getCount() == 3)
			{
				auto array = reinterpret_cast<glm::vec3*>(elms.data());
				auto normal = glm::transpose(glm::inverse(glm::mat3(trans)));
				for (size_t i = 0; i < n; i++)
				{
					auto& elm = array[i];
					elm = normal*elm;
				}
				return;
			}
		}
	}

	AttributeTransformation::Function AttributeTransformation::create(Type type)
	{
		if(type == AttributeType::Position)
		{
			return position;
		}
		if (type == AttributeType::Normal)
		{
			return normal;
		}
		return nullptr;
	}

}
