#include "pch.h"
#include "CppUnitTest.h"
#include "../ap_12.9/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = nullptr;

			insert(&root, 5);

			Assert::IsNotNull(root);
			Assert::AreEqual(5, root->info);
		}
	};
}
