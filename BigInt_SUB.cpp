#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>

#define DIGITS 4

typedef long long int li;

using namespace std;

struct LL { li data; li size; li noz; bool startZero; LL *next, *prev; } *h1, *h2;

LL* create(string s) {
	
	li i = 0, x = s.length(), d = 0;
	LL *head = NULL, *tail = NULL;
	while(i < x) {

		LL *node = new LL();
		
		if(x-i < DIGITS) { d = x-i; } else { d = DIGITS; }
		string temp = s.substr(i, d);
		reverse(temp.begin(), temp.end());

		node->data = stoll(temp);
		string tempData = to_string(node->data);
		if(temp.length() != tempData.length()) { node->startZero = true; } else { node->startZero = false; }
		node->noz = temp.length() - tempData.length();
		node->size = tempData.length();
		node->next = node->prev = NULL;
		
		if(head == NULL) { head = node; tail = node; } else {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}

		i += d;
	}
	return head; 
}

void printLL(LL *head)
{
	for(auto trav = head; trav != NULL; trav = trav->next) {
		printf("\nData = %4lld Size = %lld NOZ = %lld\n", trav->data, trav->size, trav->noz);
	}
}

string remove_start_zeroes(string s)
{
	li i = 0, j = 0;
	string c = "";
	for (i = 0; i < s.length(); ++i) {
		if(s[i] != '0') { break; }
	}
	for (li j = i; j < s.length(); ++j) {
		c = s[j] + c;
	}
	return c;
}

bool set_Greater_to_H1(string a, string b)
{
	LL *temp = NULL;
	if(a.length() < b.length()) { temp = h1; h1 = h2; h2 = temp; return true; } else if(a.length() == b.length()) {
		LL *trav1, *trav2, *trav3, *trav4;
		for(trav1 = h1; trav1->next != NULL; trav1 = trav1->next);
		for(trav2 = h2; trav2->next != NULL; trav2 = trav2->next);
		for(trav3 = trav1, trav4 = trav2; trav3 != NULL, trav4 != NULL; trav3 = trav3->prev, trav4 = trav4->prev)
		{
			if(trav3->size < trav4->size) {
				temp = h1; h1 = h2; h2 = temp; return true;
			} else if(trav3->size == trav4->size) {
				if(trav3->data < trav4->data) {
					temp = h1; h1 = h2; h2 = temp; return true;
				} else if(trav3->data == trav4->data) {
					continue;
				} else { return false; }
			} else { return false; }
		}
	}
	return false;
}

li sub_with_borrow(li x, li y) { return -1*(pow(10, DIGITS) - (y - x)); }

string substract()
{
	if(h1 == NULL) { cout <<"\nError: LL is empty"<< endl; return ""; }
	
	LL *trav1 = h1, *trav2 = h2;
	bool borrowed = false;
	string c = "", temp2 = "";
	li r, temp, t, y;
	while(trav1 != NULL && trav2 != NULL) {
		temp = trav1->data;
		if(borrowed) {
			if(temp == 0) { temp = pow(10, DIGITS) - 1; } else { --temp; borrowed = false; }
		}
		if(temp < trav2->data) {
			r = sub_with_borrow(temp, trav2->data);
			if(r < 0) { borrowed = true; r *= -1; }
			temp2 = to_string(r);
			c = temp2 + c;
			if(temp2.length() < DIGITS) {
				t = temp2.length();
				while(t < DIGITS) { c = "0" + c; t++; }
			}
		} else {
			r = temp - trav2->data;
			string tr = to_string(r), tq = to_string(temp);
			c = tr + c;
			if(tr.length() < DIGITS) {
				y = tr.length();
				while(y < DIGITS) { c = "0" + c; y++; }
			}
		}
		trav1 = trav1->next;
		trav2 = trav2->next;
	}
	while(trav1 != NULL) {
		temp = trav1->data;
		if(borrowed) {
			if(temp == 0) { temp = pow(10, DIGITS) - 1; } else { --temp; borrowed = false; }
		}
		temp2 = to_string(temp);
		c = temp2 + c;
		if(temp2.length() < DIGITS) {
			t = temp2.length();
			while(t < DIGITS) { c = "0" + c; t++; }
		}
		trav1 = trav1->next;
	}
	return c;
}

int main()
{
	string a, b;
	cout <<"\nEnter two numbers"<< endl;
	cout <<"\n-> 1st number: "; cin >> a;
	cout <<"\n-> 2nd number: "; cin >> b;

	//if(stoll(a) == 0 && stoll(b) == 0) { cout <<"\nResult is: 0\n"<< endl; return 0; }

	a = remove_start_zeroes(a); b = remove_start_zeroes(b);
	//reverse(a.begin(), a.end()); reverse(b.begin(), b.end());

	h1 = create(a); h2 = create(b);

	if(set_Greater_to_H1(a, b)) {
		string temp = a;
		a = b; b = temp;
	}

	cout <<"\nThe LL1"<< endl; printLL(h1); cout << endl;
	cout <<"\nThe LL2"<< endl; printLL(h2); cout << endl;

	string r = substract();

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	r = remove_start_zeroes(r); reverse(r.begin(), r.end());

	li da = 0;
	li db = a.length() - b.length();
	li dc = a.length() - r.length();
	if(dc <= 0) { dc = 0; }
	cout <<"\nThe Output"<< endl;
	printf("\n x   =  "); for(int i = 0; i < da; ++i) { printf(" "); } cout << a << endl;
	printf("\n y   =  "); for(int i = 0; i < db; ++i) { printf(" "); } cout << b << endl;
	cout <<"\n x-y =  "; for(int i = 0; i < dc; ++i) { printf(" "); } cout << r << endl;
	cout <<"\n y-x = -"; for(int i = 0; i < dc; ++i) { printf(" "); } cout << r << endl;

	cout << endl;
	return 0;
}