#include <bits/stdc++.h>
#define ll long long
#define pi 3.141592
#define latitude_x 12.9611159
#define longitude_y 77.6362214
#define earth_radius 6371.000000
#define max_distance 50.000000

using namespace std;

ifstream customers_list("customers.json");

struct node {
  double dist;
  std::string name, id;
};

bool comp(node a, node b){
  return a.dist < b.dist;
}

double radian(double deg){
  return ((deg*pi)/180);
}

double check(double x, double y){

	double xx = radian(latitude_x);
	double yy = radian(longitude_y);

	double delta = (yy-y);
	double angle = acos (sin(x)*sin(xx) + cos(x)*cos(xx)*cos(delta));

	return ((angle*earth_radius));
}

void get_list() {

	std::vector<node> v;
	std::string temp = "";

	if (customers_list.is_open()) {

		while (getline(customers_list, temp)) {

			int x = 0;
			std::string id, name;
			double latitude, longitude;

			for (size_t i = 0; temp[i]; i++) {

				if(temp[i] == '"')
				++x;

				if (x == 3) {

					int j = i+1;
					std::string hold;

					while (temp[j] != '"') {
						hold += temp[j];
						++j;
					}
					i = j-1;
					latitude = stod(hold);		// to convert string into double
					latitude = radian(latitude);	// to convert degree to radian
				}

				else if (x == 6) {

					int j = i+3;

					while (temp[j] != ',') {
						id += temp[j];
						++j;
					}
					i = j+1;
					++x;
				}

				else if(x == 10){

					int j = i+1;

					while (temp[j] != '"') {
						name += temp[j];
						++j;
					}
					i = j-1;
				}

				else if (x == 14) {

					int j = i+1;
					std::string hold;

					while (temp[j] != '"') {
						hold += temp[j];
						++j;
					}
					i = j-1;
					longitude = stod(hold);
					longitude = radian(longitude);
				}
			}
			if (check(latitude, longitude) <= max_distance) {
				node hold;
				hold.dist = check(latitude, longitude);
				hold.name = name;
				hold.id = id;
				v.push_back(hold);
			}
		}

		sort(v.begin(), v.end(), comp);
		std::cout << '\n';

		std::cout << "Driver name\t"<<"Driver Id\t"<<"Cab distance from your location(in Km)" << '\n';
		std::cout << "-----------------------------------------------------------------------" << '\n';

		for (size_t i = 0; i < v.size(); i++) {
			std::cout << v[i].name<<'\t'<<'\t'<<v[i].id<<'\t'<<'\t'<<v[i].dist << '\n';
		}
		v.clear();
	} else {
		std::cout << "Unable to open 'customers.json' file." << '\n';
	}
}

int main(int argc, char const *argv[]) {

	get_list();

  return 0;
}
