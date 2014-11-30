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

		//vector<int> input{ 4, 80, 70, 23, 9, 60, 68, 27, 66, 78, 12, 40, 52, 53, 44, 8, 49, 28, 18, 46, 21, 39, 51, 7, 87, 99, 69, 62, 84, 6, 79, 67, 14, 98, 83, 0, 96, 5, 82, 10, 26, 48, 3, 2, 15, 92, 11, 55, 63, 97, 43, 45, 81, 42, 95, 20, 25, 74, 24, 72, 91, 35, 86, 19, 75, 58, 71, 47, 76, 59, 64, 93, 17, 50, 56, 94, 90, 89, 32, 37, 34, 65, 1, 73, 41, 36, 57, 77, 30, 22, 13, 29, 38, 16, 88, 61, 31, 85, 33, 54 };
		//vector<int> input{ 2, 1, 0, 5 };
		int temp;
		vector<int> input;

		while (integers>>temp)//returns 0 when EOF is encountered
		{
			input.push_back(temp);
		}

		unsigned long *noInvs = new unsigned long(0);

		vector<int> output = MergeSort(input, noInvs);

		/*for (vector<int>::iterator i = output.begin();
			i != output.end();
			++i)
		{
			std::cout << *i << " ";
		}*/

		std::cout << *noInvs;
		delete noInvs;

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