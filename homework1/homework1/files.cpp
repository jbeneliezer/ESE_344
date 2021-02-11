#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>

constexpr size_t SET_SIZE = 10;

using namespace std;

int main() {

	ifstream fin;
	ofstream fout;
	vector<float> nums;

	fin.open("inputfile.txt");    // file name specified in source code
	fout.open("outputfile.txt");

	if (!fin) {
		cerr << "cannot open " << "inputfile.txt" << endl;
		exit(1);
	}
	if (!fout) {
		cerr << "cannot open " << "outputfile.txt" << endl;
		exit(1);
	}

	float input;
	size_t count = 0;

	while (fin >> input && count < SET_SIZE) {
		nums.push_back(input);
		++count;
	}

	float min = *min_element(nums.begin(), nums.end());
	float max = *max_element(nums.begin(), nums.end());
	float mean = accumulate(nums.begin(), nums.end(), 0.0) / nums.size();

	float var = 0;
	for (auto& i : nums) {
		var += ((i - mean) * (i - mean)) / nums.size();
	}

	float std_dev = sqrt(var);

	fout << "min: " << min << endl;
	fout << "max: " << max << endl;
	fout << "mean: " << mean << endl;
	fout << "standard deviation: " << std_dev << endl;

	fin.close();
	fout.close();
	return 0;
}
