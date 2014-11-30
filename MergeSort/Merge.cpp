#include <iostream>
#include <vector>
#include <fstream>

using std::vector;

vector<int> MergeSort(vector<int> input, unsigned long *noInvs);


int main() {
	std::ifstream integers("IntegerArray.txt");

	if (!integers.is_open()) {
		std::cout << "Failed to open file.";
		return 0;
	}
	else {
		// Safely use the file stream

		int temp;
		vector<int> input;

		while (integers>>temp)//returns 0 when EOF is encountered
		{
			input.push_back(temp);
		}

		unsigned long *noInversions = new unsigned long(0);

		vector<int> output = MergeSort(input, noInversions);

		std::cout << *noInversions;
		delete noInversions;
		return 0;
	}

}

vector<int> MergeSort(vector<int> input, unsigned long *noInvs) {
	
	vector<int> output(input.size());

	if (input.size() <= 1) {
		//base case
		return input;
	}
	else {
		//call again
		std::size_t const half_size = input.size() / 2;
		std::vector<int> split_lo(input.begin(), input.begin() + half_size);
		std::vector<int> split_hi(input.begin() + half_size, input.end());

		split_lo = MergeSort(split_lo, noInvs);
		split_hi = MergeSort(split_hi, noInvs);

		int noLoEntries = split_lo.size();

		//merge
		int k = input.size();
		//q tracks split_lo, j tracks split_hi
		int q = 0;
		int j = 0;

		for (int i = 0; i < input.size(); i++) {
			if (j >= split_hi.size()) {
				output[i] = split_lo[q];
				q++;
				noLoEntries--;
			}
			else if (q >= split_lo.size()){
				output[i] = split_hi[j];
				j++;
			}
			else {
				if (split_hi[j] < split_lo[q]){
					output[i] = split_hi[j];
					j++;
					*noInvs += noLoEntries;
				}
				else if (split_hi[j] > split_lo[q]){
					output[i] = split_lo[q];
					q++;
					noLoEntries--;
				}
			}
		}
		return output;
	}
}