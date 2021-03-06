#include "SoundReaderWriter.h"

namespace urchin
{

	SoundReaderWriter::SoundReaderWriter()
	{

	}

	SoundReaderWriter::~SoundReaderWriter()
	{

	}

	Sound *SoundReaderWriter::loadFrom(std::shared_ptr<XmlChunk> soundChunk, const XmlParser &xmlParser) const
	{
		Sound *sound = buildSoundFrom(soundChunk, xmlParser);

		loadPropertiesOn(sound, soundChunk, xmlParser);

		return sound;
	}

	void SoundReaderWriter::writeOn(std::shared_ptr<XmlChunk> soundChunk, const Sound *sound, XmlWriter &xmlWriter) const
	{
		buildChunkFrom(soundChunk, sound, xmlWriter);

		writePropertiesOn(soundChunk, sound, xmlWriter);
	}

	Sound *SoundReaderWriter::buildSoundFrom(std::shared_ptr<XmlChunk> soundChunk, const XmlParser &xmlParser) const
	{
		std::shared_ptr<XmlChunk> filenameChunk = xmlParser.getUniqueChunk(true, FILENAME_TAG, XmlAttribute(), soundChunk);
		std::string filename = filenameChunk->getStringValue();

		std::string soundType = soundChunk->getAttributeValue(TYPE_ATTR);
		if(soundType.compare(POINT_VALUE)==0)
		{
			std::shared_ptr<XmlChunk> positionChunk = xmlParser.getUniqueChunk(true, POSITION_TAG, XmlAttribute(), soundChunk);
			PointSound *pointSound = new PointSound(filename, positionChunk->getPoint3Value());

			std::shared_ptr<XmlChunk> inaudibleDistanceChunk = xmlParser.getUniqueChunk(true, INAUDIBLE_DISTANCE_TAG, XmlAttribute(), soundChunk);
			pointSound->setInaudibleDistance(inaudibleDistanceChunk->getFloatValue());

			return pointSound;
		}else if(soundType.compare(AMBIENT_VALUE)==0)
		{
			return new AmbientSound(filename);
		}

		throw std::invalid_argument("Unknown sound type read from map: " + soundType);
	}

	void SoundReaderWriter::buildChunkFrom(std::shared_ptr<XmlChunk> soundChunk, const Sound *sound, XmlWriter &xmlWriter) const
	{
		std::shared_ptr<XmlChunk> filenameChunk = xmlWriter.createChunk(FILENAME_TAG, XmlAttribute(), soundChunk);
		filenameChunk->setStringValue(sound->getFilename());

		if(sound->getSoundType()==Sound::POINT)
		{
			const PointSound *pointSound = static_cast<const PointSound *>(sound);
			soundChunk->setAttribute(XmlAttribute(TYPE_ATTR, POINT_VALUE));

			std::shared_ptr<XmlChunk> positionChunk = xmlWriter.createChunk(POSITION_TAG, XmlAttribute(), soundChunk);
			positionChunk->setPoint3Value(pointSound->getPosition());

			std::shared_ptr<XmlChunk> inaudibleDistanceChunk = xmlWriter.createChunk(INAUDIBLE_DISTANCE_TAG, XmlAttribute(), soundChunk);
			inaudibleDistanceChunk->setFloatValue(pointSound->getInaudibleDistance());
		}else if(sound->getSoundType()==Sound::AMBIENT)
		{
			soundChunk->setAttribute(XmlAttribute(TYPE_ATTR, AMBIENT_VALUE));
		}else
		{
			throw std::invalid_argument("Unknown sound type to write in map: " + sound->getSoundType());
		}
	}

	void SoundReaderWriter::loadPropertiesOn(Sound *sound, std::shared_ptr<XmlChunk> soundChunk, const XmlParser &xmlParser) const
	{
		std::shared_ptr<XmlChunk> volumeChunk = xmlParser.getUniqueChunk(true, VOLUME_TAG, XmlAttribute(), soundChunk);
		sound->setVolume(volumeChunk->getFloatValue());
	}

	void SoundReaderWriter::writePropertiesOn(std::shared_ptr<XmlChunk> soundChunk, const Sound *sound, XmlWriter &xmlWriter) const
	{
		std::shared_ptr<XmlChunk> volumeChunk = xmlWriter.createChunk(VOLUME_TAG, XmlAttribute(), soundChunk);
		volumeChunk->setFloatValue(sound->getVolume());
	}

}
