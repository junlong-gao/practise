#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include <exception>
#include <unordered_map>
#include "sptr.h"

namespace sptr{
	using namespace std;
	class Wiget{
		public:
			Wiget(){;}
	};

	class Investment{
	protected:
		string name;
	public:
		Investment(){
			cout << "inv constructed" << endl;
		}
		virtual void buy(){
			cout << name << " bought" << endl;
		}
		virtual void sell(){
			cout << name << " sold" << endl;
		}
		virtual void bad_boy(){
			throw runtime_error("bad boy happens");
		}
		virtual ~Investment(){
			cout << "inv destoryed" << endl;
		}
	};

	class Stock:public Investment{
	public:
		Stock(int price, string name){
			Investment::name = name;
			cout << "constructing stock ";
			cout << "with price: " << price;
			cout << " and name: " << name;
			cout << endl;
		}
		~Stock(){
			cout << "stock " <<  name << " destoryed" << endl;
		}
	};

	class Bond:public Investment{
	public:
		Bond(int price, string name){
			Investment::name = name;
			cout << "constructing bond ";
			cout << "with price: " << price;
			cout << " and name: " << name;
			cout << endl;
		}
		~Bond(){
			cout << "bond " << name << " destoryed" << endl;
		}
	};

	class RealEstate:public Investment{
	public:
		RealEstate(int price, string location){
			Investment::name = location;
			cout << "constructing real estate ";
			cout << "with price: " << price;
			cout << " and location: " << location;
			cout << endl;
		}
		~RealEstate(){
			cout << "real estate at " << name << " destoryed" << endl;
		}
	};

	auto delInvmt = [](Investment* ptr){ //stateless lambda
		cout << "stateless lambda is called ";
		cout << "in the unique pointer before deletion" << endl;
		delete ptr;
	};
	using del_t = decltype(delInvmt);
	//factory function for investment:
	template<typename... Ts>
	auto //c++14 otherwise write unqiue_ptr<Investment, decltype(delInvmt)>
	makeInvestment(string type, Ts&&... params){
	// reference collasping and
	// perfect forwarding
		std::unique_ptr<Investment, decltype(delInvmt)>
			pInv(nullptr, delInvmt);
		if(type == "stock"){
			pInv.reset(new Stock(std::forward<Ts>(params)...));
		}else if(type == "bond"){
			pInv.reset(new Bond(std::forward<Ts>(params)...));
		}else if(type == "real estate"){
			pInv.reset(new RealEstate(std::forward<Ts>(params)...));
		}else{
			assert(0);
		}
		return pInv;
	}

	void fooInvmt(std::shared_ptr<Investment> inv_ptr, int value){ //this adds the ref count
		cout << "foo with value: " << value << endl;
		inv_ptr->buy();
		inv_ptr->sell();
	}//ref count decrease

	int bad_boy(){
		throw runtime_error("wish I am not in parameter, because I am throwing");
	}

	struct Fooing{
		shared_ptr<Fooing> strong_other;
		weak_ptr<Fooing> weak_other;
		string name;
		Fooing(string name_):name(std::move(name_)){;}
		~Fooing(){
			cout << "destoryed " << name << endl;
		}
	};

	void demo(){
		using namespace std;
		cout << " --- sptr demo --- " << endl;

		/*
		 * unique pointer
		 */
		{
			auto inv_ptr = makeInvestment("bond", 100, "china bond");
			cout << "size of it: " << sizeof(inv_ptr) << endl;
			inv_ptr->buy();
			try{
				inv_ptr->bad_boy();
			}catch(exception& e){
				cout << e.what() << endl;
				cout << "and I forget to reclaim the resource" << endl;
			}
			cout << "out of scope, reclaim automatically" << endl;
		}

		/*
		 * owner ship transfer
		 */
		unique_ptr<Investment, decltype(delInvmt)> dangle(nullptr, delInvmt);
		{
			auto inv_ptr = makeInvestment("stock", 100, "china stock");
			//dangle = inv_ptr; // won't compile
			dangle.reset(inv_ptr.release());
		}
		dangle = nullptr;


		cout << endl << endl << endl;

		/*
		 * shared pointer, make share
		 */
		auto to_share = makeInvestment("real estate", 100, "shanghai");

		std::shared_ptr<Investment> //no need for template of lambda
						ptr = move(to_share);

		{
			auto another_shared(make_shared<Bond>(0, "another bond"));
			ptr = another_shared;
			cout << "exiting local scope" << endl;
			//here to shanghai is destoryed but another bound will not
		}

		/*
		 * RAII style of pointer passing,
		 * compare to new Bond passing
		 */
		try{
			fooInvmt(make_shared<Bond>(0, "bond in para"), bad_boy());
		}catch(exception& e){
			cout << e.what() << endl;
		}

		//an example of working around the make share initlize list
		//limitation
		auto initList = {10, 20, 30};
		auto spv = std::make_unique<std::vector<int>>(initList);
		for(auto num : *spv){
			cout << num << " ";
		}
		cout << endl;
		cout << endl;
		cout << endl;

		/*
		 * weak pointers does not add
		 * count reference
		 */
		unordered_map<string, shared_ptr<Investment>> jar;
		jar["test1"] = std::make_unique<Bond>(1, "test 1");
		jar["test2"] = std::make_unique<Bond>(2, "test 2");
		{
			vector<std::weak_ptr<Investment>> observers;
			observers.emplace_back(jar["test1"]);
			observers.emplace_back(jar["test2"]);
			//non of them will be destructed, but can be observed
			if(auto ptr = observers.back().lock()){
				ptr->buy();
			}
		}

		/*
		 * use weak ptr to solve
		 * circular dependency
		 */
		cout << "---" << endl;
		{
			auto foo1 = make_shared<Fooing>("foo1");
			auto foo2 = make_shared<Fooing>("foo2");
			foo1->strong_other= foo2;
			foo2->strong_other = foo1;
			//bad, leaking resource
		}
		cout << "nobody is destoryed here" << endl;
		cout << "---" << endl;
		{
			auto foo3 = make_shared<Fooing>("foo3");
			auto foo4 = make_shared<Fooing>("foo4");
			foo3->weak_other = foo4;
			foo4->strong_other = foo3;
			//good leaking resource
		}
		cout << "---" << endl;



		cout << endl << endl << endl <<" --- sptr demo --- " << endl << endl << endl;
		//here the ptr points to another bond destoryed
		return;
	}
}
