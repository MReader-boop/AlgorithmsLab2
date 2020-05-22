#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"../List.h"
#include"../Map.h"
#include"../Pair.h"
#include"../Shennon_Fano.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestShennonFano
{
	TEST_CLASS(UnitTestShennonFano)
	{
	public:
		
		TEST_METHOD(TestCodingShennonFanoDifferentSymbolWords)
		{
			string str = "word";
			string coding_str;
			Shennon_Fano* Shennon_Fano_tree = new Shennon_Fano(str);
			Map<char, string>* Shennon_Fano = Shennon_Fano_tree->fill_tree_with_code();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = Shennon_Fano_tree->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += Shennon_Fano->find(str[i]);
			Assert::AreEqual(coding_str, string("10110001"));
		}
		TEST_METHOD(TestCodingShennonFanoSameSymbolWords) {
			string str = "gggg";
			string coding_str;
			Shennon_Fano* Shennon_Fano_tree = new Shennon_Fano(str);
			Map<char, string>* Shennon_Fano = Shennon_Fano_tree->fill_tree_with_code();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = Shennon_Fano_tree->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += Shennon_Fano->find(str[i]);
			Assert::AreEqual(coding_str, string("0000"));
		}
		TEST_METHOD(TestCodingShennonFanoText) {
			string str = "sentence of several words";
			string coding_str;
			Shennon_Fano* Shennon_Fano_tree = new Shennon_Fano(str);
			Map<char, string>* Shennon_Fano = Shennon_Fano_tree->fill_tree_with_code();
			int counter = 0;
			List<Pair<char, int>>* list_symbol = Shennon_Fano_tree->get_list_symbol();
			for (int i = 0; i < str.size(); i++)
				coding_str += Shennon_Fano->find(str[i]);
			Assert::AreEqual(coding_str, string("00000101000100101010000011001001100101100011000001000111010111110100010111010001011110110000"));
		}

	};
}
