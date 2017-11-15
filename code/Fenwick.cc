vector<int> t;
int n;

void init (int nn) {
	n = nn;
	t.assign (n, 0);
}

int sum (int r) {
	int result = 0;
	for (; r >= 0; r = (r & (r+1)) - 1)
		result += t[r];
	return result;
}

void inc (int i, int delta) {
	for (; i < n; i = (i | (i+1)))
		t[i] += delta;
}

int sum (int l, int r) {
	return sum (r) - sum (l-1);
}

