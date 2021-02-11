#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>

constexpr size_t SET_SIZE = 10;

using namespace std;

int main() {

	vector<float> nums;
	cout << "Enter numbers: ";

	size_t count = 0;
	float input;
	
	while (cin >> input && count < SET_SIZE) {
		nums.push_back(input);
		++count;
	}

	float min = *min_element(nums.begin(), nums.end());
	float max = *max_element(nums.begin(), nums.end());
	float mean = accumulate(nums.begin(), nums.end(), 0.0)/ nums.size();
	
	float var = 0;
	for (auto& i : nums) {
		var += ((i - mean) * (i - mean))/ nums.size();
	}

	float std_dev = sqrt(var);

	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	cout << "mean: " << mean << endl;
	cout << "standard deviation: " << std_dev << endl;
	
	return 0;
}
