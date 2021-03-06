#ifndef ENGINE_ISLANDCONTAINERTEST_H
#define ENGINE_ISLANDCONTAINERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>
#include <vector>

#include "UrchinPhysicsEngine.h"

class IslandContainerTest : public CppUnit::TestFixture
{
	public:
		static CppUnit::Test *suite();

		void cascadeMergeIslands();
		void mergeAllIslands();
		void createTwoSeparateIslands();
};

class TestBody : public urchin::IslandElement
{
	public:
		void setIslandElementId(unsigned int id)
		{
			this->id = id;
		}

		unsigned int getIslandElementId() const
		{
			return id;
		}

	private:
		unsigned int id;
};

#endif
