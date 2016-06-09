#include<iostream>
#include<list>
#include<algorithm>
using namespace std;


class Polynomial {
	public:
		struct Term {
			int exp;
			double coef;

			bool operator<(const Term& t) const{
				return exp<t.exp;
			}
			bool operator>(const Term& t) const{
				return exp>t.exp;
			}
			bool operator==(const Term& t) const{
				return exp==t.exp && coef==t.coef;
			}
		};

		Polynomial() {}
		Polynomial(const Polynomial& p) { m_list = p.m_list; }

		void printList(){
			for(list<Term>::iterator it=m_list.begin();it!=m_list.end();it++)
				cout<<it->exp<<" "<<it->coef<<endl;
			cout<<endl;
		}

		const Polynomial& operator=(const Polynomial& p) {
			m_list = p.m_list; 
			return *this;
		}
		
		void InsertTerm(int exp, double coef);
		void AddTerm(int exp, double coef);

		Polynomial operator+(Polynomial& p);
		Polynomial operator-(Polynomial& p);
		Polynomial operator*(Polynomial& p);

		void Differential();
		void Integral();

		double Evaluate(double x);
		double Horner(double x);
		
	protected:
		double power(double x,int n);

		list<Term> m_list;
};

bool listSort(const Polynomial::Term& t1, const Polynomial::Term& t2){
	return t1.exp>t2.exp;
}

double Polynomial::power(double x,int n){
	if(n==0) return 1;
	if(n==1) return x;
	double half=power(x,n/2);
	if(n%2==0) return half*half;
	else return half*half*x;
}

double Polynomial::Evaluate(double x){
	list<Term>::iterator it=m_list.begin();
	double s=0;
	while(it!=m_list.end()){
		s+=power(x,it->exp)*(it->coef);
		it++;
	}
	return s;
}

//Horner's rule
//x^4+x^2+3 -> (((x+0)x+1)x+0)x+3 로 변형해서 계산
//x^3+x^2+x+3 -> ((x+1)x+1)x+3
double Polynomial::Horner(double x){
	list<Term>::iterator it=m_list.begin();
	list<Term>::iterator itNext=it;
	double sum=0;
	int cnt=0;
	int max;
	itNext++;
	int zeroCnt=0;
	int tmpCnt=0;

	max=it->exp;

	while(cnt<max){
		if(cnt==0){
			sum=it->coef;
			zeroCnt=it->exp-itNext->exp;
		}

		if(itNext==m_list.end()){ //x^3+x^2
			sum*=x;
		}
		else{
			zeroCnt=it->exp-itNext->exp;
			if(zeroCnt-tmpCnt >1){
				sum*=x;
				tmpCnt++;
			}
			else{
				sum*=x;
				sum+=itNext->coef;
			
				tmpCnt=0;
				it++;
				itNext++;
			}
		}

		
		
		
		cnt++;
	}
	return sum;
}

void Polynomial::Differential(){
	list<Term>::iterator it=m_list.begin();
	while(it!=m_list.end()){
		if(it->exp>0){
			it->coef*=it->exp;
			it->exp-=1;
		}
		it++;
	}
}

void Polynomial::Integral(){
	list<Term>::iterator it=m_list.begin();
	while(it!=m_list.end()){
		it->coef/=it->exp+1;
		it->exp+=1;
		it++;
	}
}
Polynomial Polynomial::operator*(Polynomial& p){
	Polynomial s;
	list<Term>::iterator it=m_list.begin();
	list<Term>::iterator it2;
	while(it!=m_list.end()){
		it2=p.m_list.begin();
		while(it2!=p.m_list.end()){
			s.AddTerm(it->exp+it2->exp,it->coef*it2->coef);
			it2++;
		}
		it++;
	}
	return s;
}

Polynomial Polynomial::operator+(Polynomial& p){
	Polynomial s;
	list<Term>::iterator it1=m_list.begin(),it2=p.m_list.begin();

	while(it1!=m_list.end() && it2!=p.m_list.end()){
		if(it1->exp>it2->exp){
			s.AddTerm(it1->exp,it1->coef);
			it1++;
		}
		else if(it1->exp<it2->exp){
			s.AddTerm(it2->exp,it2->coef);
			it2++;
		}
		else{
			if(it1->coef+it2->coef==0){
				it1++;
				it2++;
				continue;
			}
			s.AddTerm(it1->exp,it1->coef+it2->coef);
			it1++;
			it2++;
		}
	}
	while(it1!=m_list.end()){
		s.AddTerm(it1->exp,it1->coef);
		it1++;
	}
	while(it2!=p.m_list.end()){
		s.AddTerm(it2->exp,it2->coef);
		it2++;
	}
	return s;
}

Polynomial Polynomial::operator-(Polynomial& p){
	Polynomial s;
	list<Term>::iterator it1=m_list.begin(),it2=p.m_list.begin();

	while(it1!=m_list.end() && it2!=p.m_list.end()){
		if(it1->exp>it2->exp){
			s.AddTerm(it1->exp,it1->coef);
			it1++;
		}
		else if(it1->exp<it2->exp){
			s.AddTerm(it2->exp,-it2->coef);
			it2++;
		}
		else{
			if(it1->coef-it2->coef==0){
				it1++;
				it2++;
				continue;
			}
			s.AddTerm(it1->exp,it1->coef-it2->coef);
			it1++;
			it2++;
		}
	}
	while(it1!=m_list.end()){
		s.AddTerm(it1->exp,it1->coef);
		it1++;
	}
	while(it2!=p.m_list.end()){
		s.AddTerm(it2->exp,-it2->coef);
		it2++;
	}
	return s;

}

void Polynomial::AddTerm(int exp,double coef){
	Term term={exp,coef};
	m_list.sort(listSort);
	
	for(list<Term>::iterator it=m_list.begin();it!=m_list.end();it++)
		if(it->exp==term.exp){
			it->coef+=term.coef;
			if(it->coef==0.0) m_list.erase(it);
			return;
		}
	m_list.push_back(term);
	m_list.sort(listSort);
}

void Polynomial::InsertTerm(int exp,double coef){
	Term term={exp,coef};
	m_list.sort(listSort);
	
	for(list<Term>::iterator it=m_list.begin();it!=m_list.end();it++)
		if(it->exp==term.exp){
			it->coef=term.coef;
			return;
		}
	m_list.push_back(term);
	m_list.sort(listSort);
}

int main(){
	Polynomial pl,pl2;
	pl.AddTerm(4,2);
	pl.AddTerm(5,2);
	pl.AddTerm(3,1);
	pl.AddTerm(2,3);
	pl.AddTerm(1,3);
	pl.AddTerm(0,3);

	pl.printList();
	cout<<pl.Evaluate(3)<<endl;
	cout<<pl.Horner(3)<<endl;
	
	pl2.AddTerm(5,1);
	pl2.AddTerm(3,1);
	pl2.AddTerm(2,1);
	pl2.AddTerm(6,1);
	pl2.AddTerm(7,1);
	//pl2.AddTerm(7,1);
	//pl2.AddTerm(7,1);

	pl2.printList();
	cout<<pl2.Evaluate(2)<<endl;
	cout<<pl2.Horner(2)<<endl;


	Polynomial s=pl+pl2;
	s.printList();

	s=pl-pl2;
	s.printList();

	s=pl*pl2;
	s.printList();

	s.Differential();
	s.printList();

	s.Integral();
	s.printList();
	return 0;
}