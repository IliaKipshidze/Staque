#pragma once
// სტეკისათვის განვსაზღვროთ დამხმარე კლასი mNode შაბლონის მეშვეობით
class Node {
public:
	int data;  // შესანახი მონაცემის ტიპი
	Node* next;    // მიმთითებელი შემდეგ ელემენტზე
	Node* prev;    // მიმთითებელი წინა ელემენტზე 

   // კლასის კონსტრუქტორი
	Node(int value, Node* _prev = nullptr, Node* _next = nullptr) :
		data(value),
		prev(_prev),
		next(_next)
	{}
};