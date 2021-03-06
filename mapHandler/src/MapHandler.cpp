#include <stdexcept>

#include "MapHandler.h"

namespace urchin
{

	MapHandler::MapHandler(Renderer3d *renderer3d, PhysicsWorld *physicsWorld, SoundManager *soundManager) :
		map(nullptr)
	{
		if(renderer3d==nullptr)
		{
			throw std::invalid_argument("Renderer 3d cannot be null in map handler");
		}

		if(soundManager==nullptr)
		{
			throw std::invalid_argument("Sound manager cannot be null in map handler");
		}

		map = new Map(renderer3d, physicsWorld, soundManager);
	}

	MapHandler::~MapHandler()
	{
		delete map;
	}

	void MapHandler::loadMapFromFile(const std::string &filename)
	{
		XmlParser xmlParser(filename);

		this->relativeWorkingDirectory = xmlParser.getRootChunk()->getAttributeValue(WORKING_DIR_ATTR);
		map->loadFrom(xmlParser.getRootChunk(), xmlParser);
	}

	void MapHandler::writeMapOnFile(const std::string &filename) const
	{
		XmlWriter xmlWriter(filename);

		std::shared_ptr<XmlChunk> rootChunk = xmlWriter.createChunk(SCENE_TAG, XmlAttribute(WORKING_DIR_ATTR, relativeWorkingDirectory));
		map->writeOn(rootChunk, xmlWriter);

		xmlWriter.saveInFile();
	}

	/**
	 * @param filename Absolute path to file containing map information
	 * @return Working directory relative to the map file
	 */
	std::string MapHandler::getRelativeWorkingDirectory(const std::string &filename)
	{
		XmlParser xmlParser(filename, "");
		return xmlParser.getRootChunk()->getAttributeValue(WORKING_DIR_ATTR);
	}

	/**
	 * @return Working directory relative to the map file
	 */
	std::string MapHandler::getRelativeWorkingDirectory() const
	{
		return relativeWorkingDirectory;
	}

	/**
	 * @param relativeWorkingDirectory Relative working directory to the map file
	 */
	void MapHandler::setRelativeWorkingDirectory(const std::string &relativeWorkingDirectory)
	{
		this->relativeWorkingDirectory = relativeWorkingDirectory;
	}

	void MapHandler::refreshMap()
	{
		map->refreshMap();
	}

	Map *MapHandler::getMap() const
	{
		return map;
	}

}
