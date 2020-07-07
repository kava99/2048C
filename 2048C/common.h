#ifndef COMMON_H
#define COMMON_H

inline int from_value_to_index(int value) {
	int idx = 0;
	int v = value;
	if (value == 0) return idx;
	while (1) {
		v -= (v / 2);
		idx++;
		if (v < 2)
			return idx;
	}
}

#endif // !COMMON_H
