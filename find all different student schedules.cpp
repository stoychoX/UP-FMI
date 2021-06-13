#include<iostream>
#include<vector>

const int DAYS_COUNT = 7;
#define _pair std::pair<int, std::string>

void getPairs(_pair* myPair, std::vector<std::vector<_pair>>& mainData, std::vector<_pair> data, int daysLeft = DAYS_COUNT) {
	for (int i = 0; i < 6; i++) {
		if (daysLeft - myPair[i].first >= 0) {
			data.push_back(myPair[i]);
			
			getPairs(myPair,mainData, data, daysLeft - myPair[i].first);
			
			data.pop_back();
		}
		else {
			int areDaysEnough = 0;

			for (auto x : data)
				areDaysEnough += x.first;

			if (data.size() != 0 && std::count(mainData.begin(), mainData.end(), data) == false && areDaysEnough == DAYS_COUNT) {
				mainData.push_back(data);

				for (auto x : data){
					std::cout << x.second << std::endl;
				}

				std::cout << std::endl;
			}
		}

	}
}

int main() {
	_pair collection[7] = {
		{2, "diplom"}, {2, "trip"}, {2, "party"}, {1, "exam"}, {1, "nothing"}, {1, "games"} };

	std::vector<std::vector<_pair>> mainData;
	std::vector<_pair> data;

	getPairs(collection, mainData, data);
	std::cout << "Answer: " << mainData.size();
}