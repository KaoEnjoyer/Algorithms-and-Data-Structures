#include <iostream>
#include <vector>
using namespace std;

size_t Partition(vector<int> &t, int l, int r) {
	int pivot = t[l];
	while (1) {
		while (t[l] < pivot) {
			l++;
		}
		while (t[r] > pivot)
			r--;

		if (l < r) {
			int temp = t[r];
			t[r] = t[l];
			t[l] = temp;
		} else
			return r;
		l++;
		r--;
	}
	return r;
}

void QS(vector<int> &t, int l, int r) {
	if (l < r) {
		int p = Partition(t, l, r);
		QS(t, l, p);
		QS(t, p + 1, l);
	}
	return;
}

int main() {
	vector<int> t = {6, 5, 7, 1, 3, 9, 3, 44, 56};
	QS(t, 0, t.size() - 1);
	for (auto el : t) {
		std::cout << el << " ";
	}
}
