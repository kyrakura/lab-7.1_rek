#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 7.1-a.rek/lab 7.1-a.rek.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
    public:
        TEST_METHOD(TestApplyFunction)
        {
            int matrix[ROWS][COLS];
            int min = -17;
            int max = 14;
            srand(time(nullptr));
            Generate(matrix, min, max);
            int originalMatrix[ROWS][COLS];
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    originalMatrix[i][j] = matrix[i][j];
                }
            }

            int count = 0;
            int sum = 0;
            Apply(matrix, count, sum);
            bool matrixChanged = false;
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (originalMatrix[i][j] != matrix[i][j]) {
                        matrixChanged = true;
                        break;
                    }
                }
                if (matrixChanged) {
                    break;
                }
            }
            int expectedCount = 0;
            int expectedSum = 0;
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (originalMatrix[i][j] < 0 && originalMatrix[i][j] % 4 != 0) {
                        expectedCount++;
                        expectedSum += originalMatrix[i][j];
                    }
                }
            }

            Assert::IsTrue(matrixChanged);
            Assert::AreEqual(expectedCount, count);
            Assert::AreEqual(expectedSum, sum);
        }
    };
}
