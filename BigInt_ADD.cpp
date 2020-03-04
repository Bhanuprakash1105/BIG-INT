#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#define DIGITS 18

typedef long long int li;

using namespace std;

struct LL { li data; bool startZero; li size; li noz; LL *next; } *h1, *h2;

LL* appendToLL(LL *node, LL *head) {
	if(head == NULL) {
		head = node;
	} else {
		LL *trav;
		for (trav = head; trav->next != NULL; trav = trav->next);
		trav->next = node;
	}
	return head;
}

void printLL(LL *head)
{
	for(auto trav = head; trav != NULL; trav = trav->next)
	{
		//cout <<"\nData = "<< trav->data <<" Size = "<< trav->size <<" NOZ = "<< trav->noz << endl;
		printf("\nData = %8lld Size = %lld NOZ = %lld\n", trav->data, trav->size, trav->noz);
	}
}

LL* createLL(string a, LL *head) {
	li i = 0, x = a.length(), d = 0;
	while(i < x)
	{
		LL *node = new LL();
		
		if(x-i < DIGITS) { d = x-i; } else { d = DIGITS; }
		
		string temp1 = a.substr(i, d);
		reverse(temp1.begin(), temp1.end());
		string temp2 = to_string(stoll(temp1));

		if(temp1.length() != temp2.length()) {
			node->startZero = true;
		} else {
			node->startZero = false;
		}
		
		node->data = stoll(temp1);
		node->noz = temp1.length() - temp2.length();
		node->size = d - (node->noz);
		head = appendToLL(node, head);

		i += d;
	}
	return head;
}

string add(LL *h1, LL *h2)
{
	auto trav1 = h1, trav2 = h2;
	string c = "";
	li carry = 0;
	while(trav1 != NULL && trav2 != NULL)
	{
		li x = trav1->data, y = trav2->data, z;
		if(!(trav1->startZero) && !(trav2->startZero)) {
			z = x + y + carry;
			string temp = to_string(z);
			if(temp.length() > max(trav1->size, trav2->size)) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else { carry = 0; c = temp + c; }
		} else if(trav1->startZero || trav2->startZero) {
			z = x + y + carry;
			string temp = to_string(z);
			if(temp.length() > max(trav1->noz, trav2->noz) + min(trav1->size, trav2->size)) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else {
				carry = 0;
				c = temp + c;
				li diff = max(trav1->noz, trav2->noz) + min(trav1->size, trav2->size) - temp.length();
				while(diff > 0) { c = "0" + c; --diff; }
			}
		}
		trav1 = trav1->next, trav2 = trav2->next;
	}
	while(trav1 != NULL) {
		if(!(trav1->startZero)) {
			li data = trav1->data + carry;
			string temp = to_string(data);
			if(temp.length() > trav1->size) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else {
				c = temp + c;
			}
		} else {
			li data = trav1->data + carry;
			string temp = to_string(data);
			if(temp.length() > trav1->size + trav1->noz) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else {
				carry = 0;
				c = temp + c;
				li zc = trav1->noz;
				while(zc > 0) { c = "0" + c; zc--; }
			}
		}
		trav1 = trav1->next;
	}
	while(trav2 != NULL) {
		if(!(trav2->startZero)) {
			li data = trav2->data + carry;
			string temp = to_string(data);
			if(temp.length() > trav2->size) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else {
				c = temp + c;
			}
		} else {
			li data = trav2->data + carry;
			string temp = to_string(data);
			if(temp.length() > trav2->size + trav2->noz) {
				carry = temp[0] - '0';
				c = temp.substr(1) + c;
			} else {
				carry = 0;
				c = temp + c;
				li zc = trav2->noz;
				while(zc > 0) { c = "0" + c; zc--; }
			}
		}
		trav2 = trav2->next;
	}
	if(carry != 0) { c = to_string(carry) + c; }
	return c;
}

int main()
{
	string a, b;
	cout <<"\nEnter 1st number: "; cin >> a;
	cout <<"\nEnter 2nd number: "; cin >> b;

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	h1 = createLL(a, h1); h2 = createLL(b, h2);

	cout <<"\nThe LL1" << endl;
	printLL(h1);
	cout << endl;

	cout <<"\nThe LL2" << endl;
	printLL(h2);
	cout << endl;

	string r = add(h1, h2);

	//cout <<"\nThe result obtained is: "<< r << endl;

	char x[a.length()+1], y[b.length()+1], z[r.length()+1];

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	strcpy(x, a.c_str());
	strcpy(y, b.c_str());
	strcpy(z, r.c_str());

	cout <<"\nThe Output"<< endl;
	printf("\n x = "); for(int i = 0; i < r.length() - a.length(); ++i) { printf(" "); } printf("%s\n", x);
	printf("\n y = "); for(int i = 0; i < r.length() - b.length(); ++i) { printf(" "); } printf("%s\n", y);
	printf("\n z = %s\n", z);

	cout << endl;
	return 0;
}