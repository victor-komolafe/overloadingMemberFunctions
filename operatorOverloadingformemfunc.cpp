/**
 * Overloading operators as memeber methods
 * C++ allows us to overload operators as member methods or global non method functions
 * Here we'll use member methods;
 * 
 * We can overload Unary operator as member methods(++, --,-,!)
  * it uses pass by value
 * and its parameter is always mostly empty because it refers to the this pointer
 * 
 * The disadvantage of overloading operators as memebers fucntions is that the obect on the lhs must be an object of the class you are using
 * Its syntax is;
 * ReturnType Type::operatorOp();
 * 
 *  We can also overload Binary opertors as member methods(+,-,==,!=,<,>,etc
 * its syntax is;
 * ReturnType Type::operatorOp(const Type &rhs)
 * 
 * To further understand which obj is lhs or rhs especially in binary operators;this obj(i.e lhs) would be the obj that uses the .operator+() 
 * while rhs is the obj inside the parameter of the operator. e.g if we have name1 + name2. this is equivalent to name1.operator+(name2) where name1 is lhs and name2 is rhs
 * hence why in operator overloading for memberfunctions, the lhs must always be a class obj if not an error would occur
 */
#include <iostream>
#include <cstring>
using namespace std;

class MemfuncOp{
    private:
          char *name;
    public:
        MemfuncOp(const char *s);   //overloaded operator
        MemfuncOp(const MemfuncOp &source);//copy constructor
        MemfuncOp operator-()const; //make lowercase
        MemfuncOp operator+(const MemfuncOp &rhs)const; //concatenate strings
        bool operator==(const MemfuncOp &rhs)const;
        ~MemfuncOp(); 
        void display_name()const;
        const char *get_name()const;
        
};
MemfuncOp::MemfuncOp(const char *s) //overloaded constructor
    :name(nullptr){
        if(s==nullptr){
            name = new char[1];
            *name = '\0';
        }else{
            name = new char[std::strlen(s)+1];
            std::strcpy(name,s);
        }
    }
MemfuncOp::MemfuncOp(const MemfuncOp &source)   //copy constructor
    :name{nullptr}{
        name = new char[std::strlen(source.name)+1];
        strcpy(name,source.name);
}
MemfuncOp MemfuncOp::operator+(const MemfuncOp &source)const{ //overloading + operator to be able to concatenate two strings
    char *buff = new char [std::strlen(name) + std::strlen(source.name)+1 ];//allocating storage size for both strings in a pointer
    std::strcpy(buff,name);  //copies name in our this pointer obj to buff.note:  
    std::strcat(buff,source.name);  //now adds name from the source obj
    MemfuncOp temp{buff}; //now storing buff into a new MemfuncOp obj
    delete [] buff; //deleting buff storage now we have copied its value to temp
    return temp;
}
MemfuncOp MemfuncOp::operator-()const{
    char *buff = new char [std::strlen(name)+1];
    std::strcpy(buff,name);
    for(size_t k =0; k<=std::strlen(buff); k++){ 
        buff[k] = std::tolower(name[k]); //uses for loop to convert each of string name's char into lowercase
    }
    MemfuncOp temps{buff};  //now copies buff's value to our new class obj
    delete [] buff;
    return temps;
}
bool MemfuncOp::operator==(const MemfuncOp &rhs)const{
    return (strcmp(name,rhs.name)==0);  //will return true if both values are the same
}
const char *MemfuncOp::get_name()const{
    return name;
}
void MemfuncOp::display_name()const{
   cout<<'\n'<<get_name();
}
MemfuncOp::~MemfuncOp(){
    delete [] name;
}

int main(){
    cout<<boolalpha<<endl;
    MemfuncOp name1{"Daniel"};  //overloaded constructor
    MemfuncOp name2{"JOHN"};
    MemfuncOp name3 = name1 + name2;    //equivalent to name3 = name1.operator+(name2) - where name1 is the lhs(this obj) and name2 is rhs
    name3.display_name();   // prints concatenated name1 and name2 together  "DanielJOHN"   
    MemfuncOp name4 = -name2;   //equivalent to name4 = operator-(name2); would output lowercase name2 which is john... 
    
    MemfuncOp name5 = name4 + "David";  //equivalent to name5 = name4.operator+("David") where name4 is lhs and "David" is rhs
    // MemfuncOp errorname = "David" + name4;  //would give an error due to lhs obj "David" not being a class obj
    MemfuncOp name6{name4};  //copy constructor
    cout<<'\n'<<(name1==name2)<<endl; //equivalent to name1.operator==(name2)false due to string values not being the same
    cout<<(name4==name6)<<endl; //true due to string values being the same
    
return 0;
}
  


    



