#include "Staque.cpp"
#include "Node.h"
#include <iostream>
using namespace std;
int main()
{
	//ვამოწმებთ Insert() ფუნქციის, უპარამეტრო კონსტრუქტორის, კოპი-კონსტრუქტორის და ბეჭდვის ფუნქცის მუშაობას.
	Staque A;
	A.Insert(2);
	A.Insert(7);
	A.Insert(4);
	A.Insert(0);
	A.Insert(-4);
	cout << "A =>  "<<A;
	Staque B(A);
	cout <<"B =>  "<< B;
	//ვამოწმებთ EraseOdds(), EraseEvens() და getSize() ფუნქციების მუშაობას.
	A.EraseOdds(2);
	A.EraseOdds(1);
	B.EraseEvens(3);
	cout << "A =>  " << A << "B =>  " << B;
	cout << "A.size = " << A.getSize() << "  B.size = " << B.getSize() << endl;
	B = A;
	cout << "A =>  " << A << "B =>  " << B;
	//ვამოწმებთ მინიჭების ოპერატორის  (=) მუშაობას.
	Staque C;
	A = C; //ვამოწმებთ რომ მინიჭების ოპერატორი სწორად მუშაობს მაშინაც თუ მას ცარიელ ობიექტს გადავცემთ.
	cout << "A =>  " << A;
	cout << "C =>  " << C;
	A = B;
	cout << "A =>  " << A;
	Staque D;
	D = C; // ცარიელისთვის ცარიელის მინიჭებაშიც სწორად მუშაობს.
	cout << "D =>  " << D;
	A.Insert(7);
	D = A; //სწორად მუშაობს ცარიელისთვის მინიჭების შემთხვევაშიც.
	cout << "D =>  " << D;
	B = A = C; //სწორად მუშაობს მინიჭების ოპერატორის მრავალჯერადი გამოყენებაც.
	cout << "A =>  " << A;
	cout << "B =>  " << B;
	cout << "C =>  " << C;
	//რამოდენიმე შემთხვევისთვის ვამოწმებთ: ხომ სწორად ვითვლით ლუწ-კენტ მონაცემებს და ხომ სწორად აბრუნებს ფუნქციაც.
	cout << "A.odds = " << A.getOdds() << "  A.evens = " << A.getEvens() << endl;
	cout << "B.odds = " << B.getOdds() << "  B.evens = " << B.getEvens() << endl;
	C.Insert(9);
	C.Insert(200);
	C.Insert(0);
	C.Insert(2);
	C.Insert(376);
	C.Insert(99);
	C.EraseOdds(1); //წაშლის 99-ს.
	D = A = B = C;
	cout << "C =>  " << C;
	cout << "C.odds = " << C.getOdds() << "  C.evens = " << C.getEvens() << endl;
	cout << "A =>  " << A;
	cout << "B =>  " << B;
	cout << "D =>  " << D;
	cout << "A.odds = " << A.getOdds() << "  A.evens = " << A.getEvens() << endl;
	cout << "B.odds = " << B.getOdds() << "  B.evens = " << B.getEvens() << endl;
	cout << "D.odds = " << D.getOdds() << "  D.evens = " << D.getEvens() << endl;
}