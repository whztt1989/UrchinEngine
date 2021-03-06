#ifndef ENGINE_SUPPORTPOINTTEST_H
#define ENGINE_SUPPORTPOINTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>

class SupportPointTest : public CppUnit::TestFixture
{
	public:
		static CppUnit::Test *suite();

		void sphereSupportPoint();
		void boxSupportPoint();
		void capsuleSupportPoint();
		void cylinderSupportPoint();
		void convexHullSupportPoint();
};

#endif
