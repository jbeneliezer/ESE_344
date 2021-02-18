#include <iostream>
#include <vector>
#include <string> 

using namespace std;

class Rectangle {
public:
	explicit Rectangle(double l = 0.0, double w = 0.0) : length{l}, width{w} { }

	void setLength(double s = 1.0) {
		length = s;
	}

	void setWidth(double s = 1.0) {
		width = s;
	}

	double getLength() const {
		return length;
	}

	double getWidth() const {
		return width;
	}

	double getArea() const {
		return length * width;
	}

	double getPerimeter() const {
		return 2 * length + 2 * width;
	}

	void print(ostream& out = cout) const {
		out << "(rectangle " << getLength() << " * " << getWidth() << ")";
	}

	bool operator< (const Rectangle& rhs) const {
		return getArea() == rhs.getArea()? getPerimeter() < rhs.getPerimeter(): getArea() < rhs.getArea();
	}

private:
	double length, width;
};


// Define an output operator for Rectangle
ostream& operator<< (ostream& out, const Rectangle& rhs) {
	rhs.print(out);
	return out;
}

/**
* Return the maximum item in array a.
* Assumes a.size( ) > 0.
* Comparable objects must provide operator< and operator=
*/
template <typename Comparable>
const Comparable& findMax(const vector<Comparable>& a) {
	int maxIndex = 0;

	for (int i = 1; i < a.size(); ++i)
		if (a[maxIndex] < a[i])
			maxIndex = i;

	return a[maxIndex];
}

int main() {
	vector<Rectangle> v = { Rectangle{ 3.0, 4.0 }, Rectangle{ 2.0, 6.0 }, Rectangle{ 2.5, 1.5 } };

	cout << "Largest Rectangle: " << findMax(v) << endl;
	char c;
	cout << "Enter any char to continue : ";
	cin >> c;

	vector<Rectangle> u(10);

	for (size_t i = 1; i < u.size(); ++i) {
		u[i].setLength(1.0 * (i + 1.0));
		u[i].setWidth(5.0 * (i + 1.0));
	}

	cout << "Largest Rectangle: " << findMax(u) << endl;

	cout << "Enter any char to exit : ";
	cin >> c;
	return 0;
}
