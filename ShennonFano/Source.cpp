#include<iostream>
#include<iomanip>
#include"Pair.h"
#include"List.h"
#include"Map.h"
#include"Shennon_Fano.h"
#include<string>
using namespace std;

int main() 
{
	string str;//обрабатываемая строка
	string coding_str;//закодируемая строка
	setlocale(LC_ALL, "RU");
	getline(cin, str);
	Shennon_Fano* shennon_fano_tree=new Shennon_Fano(str);
	Map<char, string>* shennon =shennon_fano_tree->fill_tree_with_code();
	int counter = 0;
	List<Pair<char,int>>*list_symbol=shennon_fano_tree->get_list_symbol();

	for (int i = 0; i < list_symbol->get_size(); i++)//выведем все символы и их встречаемость в тексте
		cout << " " << list_symbol->at(i).first << " | " << setw(4) << list_symbol->at(i).second << " | "  << shennon->find(list_symbol->at(i).first) << endl << "---|------|----------" << endl;
	cout << "Старая строка: " << str << endl;
	cout << "Новая строка: ";

	for (int i = 0; i < str.size(); i++) {
		coding_str+= shennon->find(str[i]);
		cout << shennon->find(str[i]);
		counter += shennon->find(str[i]).size();
	}
	cout << endl << "Кол-во символов: " << counter<<endl;

	string decoding_str=shennon_fano_tree->Decoding_shennon_tree(coding_str);
	cout << "Коэффициент сжатия: " << (((double)(decoding_str.size() * 8) / (coding_str.size())));
	return 0;
}