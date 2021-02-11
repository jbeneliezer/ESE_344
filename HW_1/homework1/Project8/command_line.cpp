#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>

constexpr size_t SET_SIZE = 10;

using namespace std;

int main(int argc, char** argv) {

	vector<float> nums;

	if (argc < 2) {
		cout << "Usage: ./command_line {elements}" << endl;
		exit(1);
	}

	for (size_t i = 1; i < argc; ++i) {
		nums.push_back(atof(argv[i]));
	}

	float min = *min_element(nums.begin(), nums.end());
	float max = *max_element(nums.begin(), nums.end());
	float mean = accumulate(nums.begin(), nums.end(), 0.0) / nums.size();

	float var = 0;
	for (auto& i : nums) {
		var += ((i - mean) * (i - mean)) / nums.size();
		cout << i << " ";
	}

	float std_dev = sqrt(var);

	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	cout << "mean: " << mean << endl;
	cout << "standard deviation: " << std_dev << endl;

	return 0;
}
