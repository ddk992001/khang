#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Examinee {
	string id;
	float math, literature, physic, chemistry, biology, history, geography, civic_education, natural_science, social_science, foreign_language;
};

vector<string> split(string haystack, string separator) {
	vector<string> tokens;
	int start = 0;
	while (true) {
		size_t pos = haystack.find(separator, start);
		if (pos != string::npos) {
			string res = haystack.substr(start, pos - start);
			tokens.push_back(res);
			start = pos + separator.size();
		}
		else {
			string res = haystack.substr(start, haystack.size() - start);
			tokens.push_back(res);
			break;
		}
	}
	return tokens;
}

Examinee readExaminee(string line_info) {
	Examinee res;
	vector<string> tokens = split(line_info, ",");
	res.id = tokens[0];
	if (tokens[2] != "")
		res.math = stof(tokens[2]);
	else
		res.math = 0;
	if (tokens[3] != "")
		res.literature = stof(tokens[3]);
	else
		res.literature = 0;
	if (tokens[4] != "")
		res.physic = stof(tokens[4]);
	else
		res.physic = 0;
	if (tokens[5] != "")
		res.chemistry = stof(tokens[5]);
	else
		res.chemistry = 0;
	if (tokens[6] != "")
		res.biology = stof(tokens[6]);
	else
		res.biology = 0;
	if (tokens[7] != "")
		res.history = stof(tokens[7]);
	else
		res.history = 0;
	if (tokens[8] != "")
		res.geography = stof(tokens[8]);
	else
		res.geography = 0;
	if (tokens[9] != "")
		res.civic_education = stof(tokens[9]);
	else
		res.civic_education = 0;
	if (tokens[10] != "")
		res.natural_science = stof(tokens[10]);
	else
		res.natural_science = 0;
	if (tokens[11] != "")
		res.social_science = stof(tokens[11]);
	else
		res.social_science = 0;
	if (tokens[12] != "")
		res.foreign_language = stof(tokens[12]);
	else
		res.foreign_language = 0;
	return res;
}

vector<Examinee> readExamineeList(string file_name) {
	vector<Examinee> res;
	ifstream fin;
	fin.open(file_name.c_str());
	string line;
	getline(fin, line);
	while (true) {
		getline(fin, line);
		if (line.size() == 0)
			break;
		Examinee temp = readExaminee(line);
		res.push_back(temp);
	}
	fin.close();
	return res;
}

void writeTotal(vector<Examinee> examinee_list, string out_file_name) {
	ofstream fout;
	fout.open(out_file_name.c_str());
	for (int i = 0; i < examinee_list.size(); i++) {
		float total = examinee_list[i].physic + examinee_list[i].chemistry + examinee_list[i].biology + examinee_list[i].history + examinee_list[i].civic_education + examinee_list[i].geography + examinee_list[i].math + examinee_list[i].literature + examinee_list[i].foreign_language;
		fout << examinee_list[i].id << " " << total << endl;
	}
	fout.close();
}

int main() {
	vector<Examinee> res = readExamineeList("E:\\HK1-Year 2\\DSAA\\Lab 1\\data.txt");
	writeTotal(res, "E:\\HK1-Year 2\\DSAA\\Lab 1\\output.txt");
	return 0;
}