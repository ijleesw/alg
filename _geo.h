int cross(pii a, pii b, pii c) {
	b -= a; c -= a;
    return b.first * c.second - b.second * c.first;
}

int area(Tri a) {
	return abs(cross(points[a[0]],points[a[1]],points[a[2]]));
}

bool inside(piii a, int b) {
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        swap(a[i], b);
        sum += area(a);
        swap(a[i], b);
    }
    sum -= area(a);
    assert(sum >= 0);
    return sum == 0;
}
