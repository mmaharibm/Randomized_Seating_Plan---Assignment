#include "People.h"

People::People() {
	for (int i = 0; i < 32; i++) {
		arr[i] = "0";
	}
}

int People::randomizeF() {
	int i = rand() % 16;
	while (arr[i] != "0") {
		i = rand() % 16;
	}
	return i;
}

int People::randomizeM() {
	int i = (rand() % (32 - 16)) + 16;
	while (arr[i] != "0") {
		i = (rand() % (32 - 16)) + 16;
	}
	return i;
}

string People::getArr(int i) {
	return arr[i];
}

void People::setArr(int i, string s) {
	arr[i] = s;
}