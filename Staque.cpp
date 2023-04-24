#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

class Staque {
	Node* top = nullptr;
	Node* bottom = nullptr;
	int odds = 0; //კენტი რიცხვების მთვლელი
	int evens = 0; //ლუწი რიცხვების მთვლელი
	int size = 0;
public:
	Staque() {}
	Staque(const Staque& obj) { //ეს არის კოპი კონსტრუქტორი
		if (obj.Empty()) { //თუ obj ცარიელია მაშინ არანაირი დამატებითი მოქმედება არ გვჭირდება
			cout << "kopi-konstruqtoris gamoyenebit sheiqmna axali carieli Staque!\n";
		}
		else {
			Node* evenpt = obj.top, * oddpt = obj.bottom;
			for (int i = 0; i < obj.evens - 1; i++) {
				evenpt = evenpt->next; //გადავა იმ ელემენტზე საიდანაც იწყება კენტები, რომ მერე შევძლოთ insert() ფუნქციის გამოყენება
			}
			for (int i = 0; i < obj.odds - 1; i++) {
				oddpt = oddpt->prev; //ანალოგიურად, გადავა იმ მისამართზე საიდანაც იწყება კენტები
			}
			for (Node* ptr = evenpt; ptr != nullptr; ptr = ptr->prev) {
				Insert(ptr->data); //ახლა მივყვებით და სანამ ლუწები არ ამოიწურება insert() ფუნქციით ჩავსვამთ ჩვენს Staque -ში
			}
			for (Node* ptr = oddpt; ptr != nullptr; ptr = ptr->next) {
				Insert(ptr->data); //ანალოგიურად, ჩავსვამთ კენტებს
			}
		}
	}
	~Staque()
	{
		//დესტრუქტორი, გადაუვლის მთელს Staque-ს და წაშლის ყველა ელემენტს
		Node* ptr;
		while (top != nullptr)
		{
			ptr = top;
			top = top->next;
			delete ptr;
		}
	}
	Staque& operator=(const Staque& obj) {
		if (obj.Empty()) { //ცალკე ვითვალისწინებთ შემთხვევას თუ obj არის ცარიელი და ასეთ შემთხვევაში უბრალოდ ვშლით ყველა ელემენტს 
			//და ზომა, კენ-ლუწების რაოდენობაც გახდება obj-ის შესაბამისი ველების ტოლი, ანუ ნული.
			Node* ptr;
			while (top != nullptr)
			{
				ptr = top;
				top = top->next;
				delete ptr;
			}
			size = obj.size;
			odds = obj.odds;
			evens = obj.evens;
			return *this; //დააბრუნებს Staque-ს რომ შევძლოთ მინიჭების ოპერატორის მრავალჯერადი გამოყენება
		}
		if (this != &obj) { //თუ უკვე ტოლები არ არიან, მაშინ შეასრულებს ქვემოთ მითითებულ ბრძანებებს
			if (this->size <= obj.size) { //თუ გადაცემულ obj-ში უფრო მეტი (ან ტოლი) ელემენტია ვიდრე this-ში
				Node* ptr, * objptr = obj.top;
				//this-ს რა ელემენტებიც აქვს ჯერ მათ data-ს შევცვლით obj-ის შესაბამისად
				for (ptr = top; ptr != nullptr; ptr = ptr->next) {
					ptr->data = objptr->data;
					objptr = objptr->next;
				}
				if (size == 0) { //თუ ცარიელია ზედა ფორში არ შევა და შემოვა აქ, და პირველ ელემენტს ოდნავ განსხვავებულად ჩასვამს
					//ეს იმიტომაა საჭირო რომ როდესაც პოინტერი არის nullptr ჩევენ მისთვის არ შეგვიძლია next ან prev-ზე მიმართვა
					top = bottom = new Node(objptr->data);
					objptr = objptr->next;
				}
				//აქ უკვე data-ს შეცვლა აღარ არის საკმარისი, უნდა შევქმნათ ახალი node-ები რადგან this-ში მეტი ელემენტი აღარ არის
				for (objptr; objptr != nullptr; objptr = objptr->next) {
					ptr = new Node(objptr->data, bottom);
					bottom->next = ptr;
					bottom = ptr;
				}
			}
			else { //თუ this-ში უფრო მეტი ელემენტია
				Node* ptr = top, * objptr = obj.top;
				//obj-ში რამდენი ელემენტიცაა ჯერ იმათ (ანუ იმათ data-ს გადმოვიტანთ this-ში) 
				for (objptr; objptr != nullptr; objptr = objptr->next) {
					ptr->data = objptr->data;
					ptr = ptr->next;
				}
				bottom = ptr->prev; //ptr ერთით ზედმეტად გადავიდოდა მარჯვნივ ვიდრე ჩვენი Bottom უნდა იყოს, ამიტომ გადმოვდივართ უკან
				Node* pt = ptr;
				//და შემდეგ, რახან this-ის ელემენტების რაოდენობა უფრო მეტი იყო, აქ დაგვრჩება ზედმეტი ელემენტები 
				//რომლებიც უნდა წავშალოთ
				for (ptr = ptr->next; ptr != nullptr; ptr = ptr->next) {
					delete pt;
					pt = ptr;
				}
				bottom->next = nullptr;
			}
			//გავუტოლებთ შესაბამის ველებს
			size = obj.size;
			odds = obj.odds;
			evens = obj.evens;
		}
		return *this;
	}
	int getSize()const { //ზომის დაბრუნების ფუნქცია
		return size;
	}
	bool Empty() const { //არკვევს არის თუ არა Staque ცარიელი
		return size == 0;
	}
	int getOdds()const{ //კენტების რაოდენობის დაბრუნების ფუნქცია
		return odds;
	}
	int getEvens()const { //ლუწების რაოდენობის დაბრუნების ფუნქცია
		return evens;
	}
	void Insert(int val) {
		if (val % 2 == 0) { //თუ ჩასამატებელი მონაცემი ლუწია
			Node* ptr = new (nothrow) Node(val);
			if (ptr == nullptr) //გამოიყო თუ არა მეხსიერება, ანუ გვაქვს თუ არა ადგილი
			{
				cout << "RAM is Full\n";
				return;
			}
			if (top == nullptr) //თუ Staque ცარიელია
			{
				top = bottom = ptr; //ჩავსვამთ ელემენტს, თავიც ის იქნება და ბოლოც
				size++; //ვზრდით ზომას
				evens++; //ვზრდით ლუწების რაოდენობას
				return; //გამოვდივართ ფუნქციიდან
			}
			//თუ ცარიელი არ არის მაშინ შემდეგი მოქმედებებით ელემენტს ჩავამატებთ თავში, და გავზრდით ზომასა და ლუწების რაოდენობას
			ptr->next = top;
			top->prev = ptr;
			top = ptr;
			size++;
			evens++;
		}
		else {
			//ყველაფერი ანალოგიურად, ისე როგორც ლუწების დამატებისას
			Node* ptr = new (nothrow) Node(val);
			if (ptr == nullptr)
			{
				cout << "RAM is Full\n";
				return;
			}
			if (bottom == nullptr)
			{
				top = bottom = ptr;
				size++;
				odds++; //ვზრდით კენტების რაოდენობას
				return;
			}
			//ჩავამატებთ კენტ რიცხვს ბოლოში
			ptr->prev = bottom;
			bottom->next = ptr;
			bottom = ptr;
			size++;
			odds++; //ვზრდით კენტების რაოდენობას
		}
	}
	void EraseEvens(int quantity) {
		if (evens < quantity) { //თუ მოთხოვნილი რაოდენობა მეტია რეალურად არსებულზე
			cout << "motxovnili raodenobis luwi ricxvebi (" << quantity << ") staque-shi ar aris da washla ver moxerxda" << endl;
		}
		else {
			Node* ptr;
			//წამოყვება წინიდან (რადგან ლუწები წინ გვაქვს) და წაშლის იმდენს რამდენიც მოვთხოვეთ (quantity)
			for (int i = 0; i < quantity; i++) {
				ptr = top;
				top = top->next;
				delete ptr;
				evens--;
				size--;
			}
			top->prev = nullptr;
		}
	}
	void EraseOdds(int quantity) {
		if (odds < quantity) { //თუ მოთხოვნილი რაოდენობა მეტია რეალურად არსებულზე
			cout << "motxovnili raodenobis kenti ricxvebi (" << quantity << ") staque-shi ar aris da washla ver moxerxda" << endl;
		}
		else {
			//წამოყვება უკნიდან (რადგან კენტები უკან გვაქვს) და წაშლის იმდენს რამდენიც მოვთხოვეთ (quantity)
			Node* ptr;
			for (int i = 0; i < quantity; i++) {
				ptr = bottom;
				bottom = bottom->prev;
				delete ptr;
				odds--;
				size--;
			}
			bottom->next = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Staque& obj) {
		if (obj.Empty()) { //თუ ცარიელია ელემენტებს ვერ დაბეჭდავს
			cout << "staque carielia, monacemta bechdva ver ganxorcieldeba!" << endl;
		}
		else {
			//დაიწყებს top-დან და სანამ nullptr-მდე არ მივა მანამდე დაბეჭდავს ყველა ელემენტს და შემდეგ აბრუნებს out-ს რომ შევძლოთ
			//მისი მრავალჯერადი გამოყენება
			for (Node* ptr = obj.top; ptr != nullptr; ptr = ptr->next) {
				out << ptr->data << "  ";
			}
			cout << endl;
		}
		return out;
	}
};