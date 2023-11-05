#ifndef ANGLEDIFF
#define ANGLEDIFF

template <typename T>
T mod(T a, T b) {
	return a - static_cast<int>(a / b) * b;
}

template <typename T>
T angleDiff(T angle1, T angle2) { // returns the signed difference between 2 angles
	constexpr float PI = 3.14159265;
	return mod(angle1 - angle2 + PI, PI * 2) - PI;
}

#endif