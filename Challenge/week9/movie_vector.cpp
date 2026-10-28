#include <iostream>
#include <vector>
using namespace std;

class Movie {
public:
    string name;
    double rating;

    Movie(string n, double r) {
        name = n;
        rating = r;
    }
};

int main() {
    vector<Movie> movieList;

    movieList.push_back(Movie("titinic", 9.9));
    movieList.push_back(Movie("gone with the wind", 9.6));
    movieList.push_back(Movie("terminator", 9.7));

    for (auto& m: movieList) {
        cout << m.name << ": " << m.rating << endl;
    }

    return 0;
}