#include<iostream>
#include<vector>
#include<string>

using namespace std;


bool resIsNegative = false;

vector<int> *mul(vector<int> *a, vector<int> *b) {
	vector<int> *res = new vector<int>(a->size() + b->size());
	for(size_t ax = 0; ax < a->size(); ax++) {
		for (size_t bx = 0; bx < b->size(); bx++) {
			(*res)[ax + bx] += (*a)[ax] * (*b)[bx];
		}
	}
	
	for (size_t i = 0; i < (res->size() - 1); i++) {
		(*res)[i + 1] += (*res)[i] / 10;
		(*res)[i] %= 10;
	}

	while((res->back() == 0) && (res->size() > 1)) {
		res->pop_back();
	}
	return res;
}

bool isFirstNumGreater(vector<int> *a, vector<int> *b) {
	if (a->size() > b->size()) {
		return true;
	}
	else if (a->size() < b->size()) {
		return false;
	}
	size_t i = a->size();
	while (1) {
		i--;
		if ((*b)[i] >= (*a)[i]) {
			return false;
		}
		if (i == 0) {
			break;
		}
	}
	return true;
}


vector<int> *add(vector<int> *a, vector<int> *b) {
	size_t res_size = (a->size() >= b->size()) ? a->size() : b->size();
	res_size++;
	vector<int> *res = new vector<int>(res_size);
	
	for (size_t i = 0; i < (res_size - 1); i++) {
		if (i < a->size() && i < b->size()) {
			(*res)[i] += (*a)[i] + (*b)[i];
		}
		else if (i >= a->size()) {
			(*res)[i] += (*b)[i];
		}
		else if (i >= b->size()) {
			(*res)[i] += (*a)[i];
		}
		(*res)[i + 1] += (*res)[i] / 10;
		(*res)[i] %= 10;
	}

	while ((res->back() == 0) && (res->size() > 1)) {
		res->pop_back();
	}

	return res;
}


vector<int> *subEncapsulated(vector<int> *a, vector<int> *b) {
	size_t res_size = (a->size() >= b->size()) ? a->size() : b->size();
	vector<int> *res = new vector<int>(res_size);
	bool carry = false;
	size_t i = 0;
	for (i; i <= (b->size() - 1); i++) {
		if (carry) {
			(*res)[i]--;
		}
		if ((*a)[i] > (*b)[i]) {
			(*res)[i] += (*a)[i] - (*b)[i];
			carry = false;
		}
		else {
			(*res)[i] += 10 + (*a)[i] - (*b)[i];
			(*res)[i] %= 10;
			carry = ((*a)[i] < (*b)[i]) ? true : carry;
		}
	}
	for (i; i <= (a->size() - 1); i++) {
		if (carry) {
			if (((*a)[i] - 1) >= 0) {
				(*res)[i] += (*a)[i] - 1;
				carry = false;
			}
			else {
				(*res)[i] += 10 + (*a)[i] - 1;
				(*res)[i] %= 10;
			}
		}
		else {
			(*res)[i] = (*a)[i];
		}
	}

	while ((res->back() == 0) && (res->size() > 1)) {
		res->pop_back();
	}
	return res;
}

vector<int> *sub(vector<int> *a, vector<int> *b) {
	vector<int> *res;
	if (isFirstNumGreater(a, b)) {
		res = subEncapsulated(a, b);
		resIsNegative = false;
	}
	else {
		res = subEncapsulated(b, a);
		resIsNegative = true;
	}
	return res;
}

vector<int> *getNum(const string &str) {
	vector<int> *res = new vector<int>();
	size_t i = str.length();
	while (1) {
		i--;
		if (isdigit(str[i])) {
			res->push_back((char)str[i] & ~0x30);
			if (i == 0) {
				break;
			}
		}
		else {
			return nullptr;
		}
	}
	return res;
}

void printNum(vector<int> *num) {
	cout << "Result: ";
	if (resIsNegative) {
		cout << "-";
	}
	size_t i = num->size();
	while (1) {
		i--;
		cout << (*num)[i];
		if (i == 0) {
			break;
		}
	}
	resIsNegative = false;
	cout << endl;
}

int main() {
	vector<int> *a = nullptr;
	vector<int> *b = nullptr;
	vector<int> *res = nullptr;
	string a_str;
	string b_str;
	char op;
	while (1) {
		try {
			cout << "Expression: ";
			cin >> a_str;
			if (a_str == "q") {
				break;
			}
			a = getNum(a_str);
			cin >> op;
			cin >> b_str;
			b = getNum(b_str);
			if ((a == nullptr) || (b == nullptr)) {
				throw("Incorrect input");
			}
			switch (op) {
				case '*':
					res = mul(a, b);
					printNum(res);
					break;
				case '+':
					res = add(a, b);
					printNum(res);
					break;
				case '-':
					res = sub(a, b);
					printNum(res);
					break;
				default:
					throw("Incorrect input");
					break;
				}
		}
		catch (const char *err_msg) {
			cout << err_msg << endl;
			getline(cin, a_str);
		}
	}
	delete res;
	delete a;
	delete b;

	return 0;
}
