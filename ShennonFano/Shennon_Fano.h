#pragma once
#include"Map.h"
#include"List.h"
#include"Pair.h"
#include"string"
class Shennon_Fano
{
	class Node {
	public:
		Node(Pair<char, int> value = Pair<char, int>(), Node* left = NULL, Node* right = NULL) :value(value), left(left), right(right) {}
		Pair<char, int> value;
		Node* left;
		Node* right;
	};
public:
	Shennon_Fano(string str) {
		Map<char, int>* map_symbol = new Map<char, int>();
		list_symbol = new List<Pair<char, int>>();
		for (int i = 0; i < str.size(); i++) 
		{
			if (!map_symbol->find_is(str[i])) //if the symbol is not in the list, then add the value to the symbol map, otherwise increase the number
				map_symbol->insert(str[i], 1);
			else
				map_symbol->increment_value(str[i]);
		}
		List<Pair<char, int>>* list_of_pairs = map_symbol->get_pairs();
		map_symbol->clear(); //no longer needed only takes up memory now
		list_of_pairs->sort(); //sorting to further wrapping		
		build_tree(Root, list_of_pairs); //building the encoding tree
	}
	List<Pair<char, int>>* get_list_symbol() 
	{
		return list_symbol;
	}
	Map<char, string>*& fill_tree_with_code() 
	{
		Map<char, string>* shennon = new Map<char, string>();
		string cur;
		fill_tree(shennon, Root, cur);
		return shennon;
	}
	string Decoding_shennon_tree(string& coding_str) 
	{
		string decoding_str;
		int pos = 0;
		Decoding(Root, coding_str, decoding_str, pos);
		return decoding_str;
	}
private:
	void Decoding(Node* root, string& coding_str, string& decoding_str, int& position) 
	{
		if (coding_str.size() > position) 
		{
			while (root->right != NULL && root->left != NULL) 
			{
				if (coding_str[position] == '0')
					root = root->left;
				else
					root = root->right;
				position++;
			}
			decoding_str += root->value.first;
			if (Root->left == NULL && Root->right == NULL)
				position++;
			Decoding(Root, coding_str, decoding_str, position);
		}
	}
	Node* build_tree(Node*& root, List<Pair<char, int>>*& list) //building the tree itself
	{
		if (list->get_size() >= 1) 
		{			
			if (list->get_size() == 1) 
			{
				list_symbol->push_back(list->at(0));
				root = new Node(list->at(0));
			}
			else 
			{
				root = new Node();
				if (list->get_size() > 1) 
				{
					List<Pair<char, int>>* list1 = list;
					List<Pair<char, int>>* list2 = new List<Pair<char, int>>();
					absolute_cut(list1, list2);
					if (list->isEmpty()) 
					{
						root->left = build_tree(root->left, list1);
						root->right = build_tree(root->right, list2);
					}
				}
			}
			return root;
		}
	}
	void fill_tree(Map<char, string>* shennon, Node* root, string cur) //filling in the code tree
	{
		if (Root->left != NULL && Root->right != NULL) 
		{
			if (root->left != NULL && root->right != NULL) 
			{
				fill_tree(shennon, root->left, cur + '0');
				fill_tree(shennon, root->right, cur + '1');
			}
			else
			{
				shennon->insert(root->value.first, cur);
			}
		}
		else {
			shennon->insert(root->value.first, cur+'0');
		}

	}
	void absolute_cut(List<Pair<char, int>>*& list1, List<Pair<char, int>>*& list2) //split into two lists
	{
		int cost = 0;
		for (int i = 0; i < list1->get_size(); ++i) 
		{
			cost += list1->at(i).second;
		}
		list1->sort();
		list1->reverse();
		int cost_list1 = cost;
		int cost_list2 = 0;

		for (int i = 0; i < list1->get_size() && list1->isEmpty(); ++i) 
		{
			if (list1->at(i).second + cost_list2 <= cost / 2) 
			{
				cost_list2 += list1->at(i).second;
				list2->push_back(list1->at(i));
				list1->remove(i);
			}
		}
		cost_list1 = cost_list1 - cost_list2;
		if (list1->get_size() == 0 || cost_list2 == cost / 2)
			for (int i = 0; i < list1->get_size() && list1->isEmpty(); ++i) 
			{
				for (int j = 0; j < list2->get_size() && list2->isEmpty(); ++j) 
				{
					if ((cost_list2 - list2->at(j).second + list1->at(i).second > cost_list2) && (cost_list2 - list2->at(j).second + list1->at(i).second) <= cost / 2) 
					{
						cost_list2 = cost_list2 - list2->at(j).second + list1->at(i).second;
						cost_list1 = cost_list1 + list2->at(j).second - list1->at(i).second;
						Pair<char, int > cur1 = list1->at(i);
						Pair<char, int > cur2 = list2->at(j);
						list1->set(i, cur1);
						list2->set(j, cur2);
					}
				}
				if (cost_list2 == cost / 2)
					break;
			}
	}
	Node* Root;
	List<Pair<char, int>>* list_symbol;
};
