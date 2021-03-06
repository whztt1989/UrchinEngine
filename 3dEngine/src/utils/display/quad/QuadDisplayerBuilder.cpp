#include <GL/glew.h>
#include <GL/gl.h>

#include "utils/display/quad/QuadDisplayerBuilder.h"

namespace urchin
{

	QuadDisplayerBuilder::QuadDisplayerBuilder() :
		pNumberOfQuad(1),
		pDimension(2), //2D
		pBufferUsage(GL_STATIC_DRAW),
		vertexDataType(GL_INT),
		vertexCoord(nullptr),
		textureDataType(GL_INT),
		textureCoord(nullptr)
	{

	}

	QuadDisplayerBuilder::~QuadDisplayerBuilder()
	{

	}

	QuadDisplayerBuilder *QuadDisplayerBuilder::numberOfQuad(unsigned int numberOfQuad)
	{
		this->pNumberOfQuad = numberOfQuad;
		return this;
	}

	unsigned int QuadDisplayerBuilder::getNumberOfQuad() const
	{
		return pNumberOfQuad;
	}

	QuadDisplayerBuilder *QuadDisplayerBuilder::dimension(unsigned int dimension)
	{
		this->pDimension = dimension;
		return this;
	}

	unsigned int QuadDisplayerBuilder::getDimension() const
	{
		return pDimension;
	}

	QuadDisplayerBuilder *QuadDisplayerBuilder::bufferUsage(unsigned int bufferUsage)
	{
		this->pBufferUsage = bufferUsage;
		return this;
	}

	unsigned int QuadDisplayerBuilder::getBufferUsage() const
	{
		return pBufferUsage;
	}

	QuadDisplayerBuilder *QuadDisplayerBuilder::vertexData(unsigned int vertexDataType, void *vertexCoord)
	{
		this->vertexDataType = vertexDataType;
		this->vertexCoord = vertexCoord;
		return this;
	}

	unsigned int QuadDisplayerBuilder::getVertexDataType() const
	{
		return vertexDataType;
	}

	void *QuadDisplayerBuilder::getVertexCoord() const
	{
		return vertexCoord;
	}

	QuadDisplayerBuilder *QuadDisplayerBuilder::textureData(unsigned int textureDataType, void *textureCoord)
	{
		this->textureDataType = textureDataType;
		this->textureCoord = textureCoord;
		return this;
	}

	unsigned int QuadDisplayerBuilder::getTextureDataType() const
	{
		return textureDataType;
	}

	void *QuadDisplayerBuilder::getTextureCoord() const
	{
		return textureCoord;
	}

	std::shared_ptr<QuadDisplayer> QuadDisplayerBuilder::build()
	{
		if(vertexCoord==nullptr)
		{
			vertexCoord = new int[8]{
					-1, 1,
					1, 1,
					1, -1,
					-1, -1};
		}

		if(textureCoord==nullptr)
		{
			textureCoord = new int[8]{
					0, 1,
					1, 1,
					1, 0,
					0, 0};
		}

		return std::make_shared<QuadDisplayer>(this);
	}

}
