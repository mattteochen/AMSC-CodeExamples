// An example of use of decltype and decleval (and also of some type traits...
#include <iostream>
#include <type_traits> // for is_constructible
#include <utility> // for declval
#include <typeinfo> // for typeid
//! A class without default constructor
class NotDefaultConstructible
{
public:
  NotDefaultConstructible(int i):i(i){}
  int get_i() const {return this->i;}
private:
  int i;
};
//! Another class 
class DefaultConstructible
{
public:
  DefaultConstructible()=default;
  DefaultConstructible(double i):i(i){}
  double get_i() const {return this->i;}
  void set_i(double x){this->i=x;}
private:
  double i;
};
// A template function where I want to interrogate the type of get_i(). 
template<class T>
void fun(T const & a)
{
  std::cout<<std::boolalpha;
  std::cout<<" The argument is:"<<std::endl;
  std::cout<<" Default constructible?     "<<std::is_default_constructible<T>::value<<std::endl;
  std::cout<<" Constructible from an int? "<<std::is_constructible<T, int>::value<<std::endl;
  // To interrogate the return get I do not need to create an object of type T!
  decltype(std::declval<T>().get_i()) b;
  // Which tye is a?, now to write it out I need typeid
  std::cout<<"get_i() returns a "<<typeid(b).name()<<std::endl;
}

int main()
{
  NotDefaultConstructible nd{5};
  DefaultConstructible d(5);
  std::cout<<"calling fun(NotDefaultConstructible) "<<std::endl;
  fun(nd);
  std::cout<<std::endl<<"calling fun(DefaultConstructible) "<<std::endl;
  fun(d);
}
