
#include "gtest/gtest.h"
#include "../src/ecmWaypoint.h"

#include <vector>
using namespace std;

#define PI 3.14159265358979323846f

namespace ecmTesting
{

	vector<waypoint> testSet = {
			{ 5, 5, 5 },
			{ 5, 5, 5 },
			{ 6, 6, 6 },
			{ 7, 7, 7 }
	};
	waypoint pos = { 6, 6, 5 };
	waypoint pos2 = { 8, 8, 8 };
	TEST(WaypointTests, ClosestTest)
	{
		EXPECT_EQ(2, closest(pos, &testSet));
		EXPECT_EQ(3, closest(pos2, &testSet));
	}

	TEST(WaypointTests, RotationTest)
	{
		EXPECT_EQ(-PI + float(PI / 4), rotationBetween(testSet[1], testSet[2]));
		EXPECT_EQ(float(PI / 4), rotationBetween(testSet[2], testSet[1]));
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}