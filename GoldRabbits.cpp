//Hagop Tanashian
//CECS 282-05
//GoldRabbits Program #5
//4/27/2021

//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <string>


using namespace std;

int result = 0;

class BigInt {
private:
    vector<char> value;
public:
    BigInt(); //default constructor
    explicit BigInt(const string&); //overloaded constructor #1
    BigInt(int); //overloaded constructor #2
    BigInt(const BigInt&); //copy constructor
    friend ostream & operator<<(ostream&, const BigInt&);
    void print();
    BigInt operator+(const BigInt&);
    BigInt operator-(int); //subtraction only supported when right operand is less than 10
    BigInt operator+(int);
    BigInt operator++(int);
    BigInt & operator=(const BigInt&);
    bool operator==(int) const;
    bool operator!=(int) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator<=(int) const;
    friend bool operator<(int, const BigInt&);
    [[nodiscard]] int parseInt() const;
    [[nodiscard]] vector<char> getValue() const;
    void setValue(int, char); //position and element
    void insertBefore(int, char); //position and element
};

void pause() {
    cout << "Press Enter to continue..."; getchar();
}

int goldRabbits(int n) {
    if(result < 0) {
        throw string("Integer Overflow at goldRabbits(46)");
    }
    if(n == 0 || n == 1) {
        return 1;
    }
    else {
        result = goldRabbits(n - 1) + goldRabbits(n - 2);
        return result;
    }
}

BigInt goldRabbits(BigInt n) {
    static map<BigInt, BigInt> memo;
    if (n == 0 || n == 1) {
        return BigInt(1);
    }
    auto it = memo.find(n);
    if(it != memo.end()) {
        return memo[n];
    }
    memo.insert({n, goldRabbits(n - 1) + goldRabbits(n - 2)});
    return memo[n];
}

int main() {
    cout << goldRabbits(BigInt(3000))<<endl;
    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT_MAX);
    cout << "B1:"<<B1<<"\nB2:"<<B2<<"\nMAX:"<<MAX<<endl;
    pause();
    cout << "\nB1:";
    B1.print();
    cout << endl;
    pause();
    int j = 0;
    for(BigInt i = 0; i <= 3000; i++)// uncomment this
    //for(int i=0; i<=3000; i++)// comment this out{
    {
        if(j <= 7 || (j >= 56 && j <= 66) || j >= 2994) {
            cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
        }
        j++;
    }
    cout << endl;
    pause();
    cout<< "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 =  goldRabbits(BigInt(3000));
    gR3000.print();
    cout << endl;
    pause();
    int n = 500;
    try {
        cout << "The value of goldRabbits(500) is:" <<goldRabbits(n)<<endl;
    }
    catch(string & error){
        cout << error << endl;
        cout << "Transitioning to BigInt\n";
        cout << goldRabbits(BigInt(n));
    }
    cout << endl;
    pause();
    return 0;
}

BigInt::BigInt() {
    value.push_back('0');
}

BigInt::BigInt(int n) {
    string str = to_string(n);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        value.push_back(arr[i]);
    }
}

BigInt::BigInt(const string& n) {
    char arr[n.length() + 1];
    strcpy(arr, n.c_str());
    for(int i = 0; i < n.length(); i++) {
        value.push_back(arr[i]);
    }
}

BigInt::BigInt(const BigInt &BI) {
    for(int i = 0; i < BI.getValue().size(); i++) {
        value.push_back(BI.getValue().at(i));
    }
}

ostream& operator<<(ostream& out, const BigInt &BI) {
    if(BI.getValue().size() >= 12) {
        for(int i = 0; i < 12; i++) {
            if(i == 0) {
                out << BI.getValue().at(i) << ".";
            }
            else {
                out << BI.getValue().at(i);
            }
        }
        out << "e" << BI.getValue().size() - 1;
    }
    else {
        for(int i = 0; i < BI.getValue().size(); i++) {
            out << BI.getValue().at(i);
        }
    }
    return out;
}

void BigInt::print() {
    for(int i = 0; i < value.size(); i++) {
        cout << value.at(i);
    }
}

BigInt BigInt::operator+(const BigInt& BI) {
    int carry = 0;
    bool doJ = true;
    int sum;
    if(value.size() >= BI.getValue().size()) { //if left operand is larger
        BigInt result = *this;
        int j = (int)BI.getValue().size() - 1;
        for(int i = (int)value.size() - 1; i >= 0 ; i--) {
            int top = value.at(i) - 48;
            if(doJ) {
                int bottom = BI.getValue().at(j) - 48;
                sum = carry + top + bottom;
            }
            else {
                sum = carry + top;
            }
            carry = 0;
            if(sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            result.setValue(i, (char)sum + 48);
            j--;
            if(j == -1) {
                doJ = false;
            }
        }
        if(carry == 1) {
            result.insertBefore(0, (char)carry + 48);
        }
        return result;
    }
    else { //if right operand is larger
        BigInt result = BI;
        int j = (int)value.size() - 1;
        for(int i = (int)BI.getValue().size() - 1; i >= 0 ; i--) {
            int top = BI.getValue().at(i) - 48;
            if(doJ) {
                int bottom = value.at(j) - 48;
                sum = carry + top + bottom;
            }
            else {
                sum = carry + top;
            }
            carry = 0;
            if(sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            result.setValue(i, (char)sum + 48);
            j--;
            if(j == -1) {
                doJ = false;
            }
        }
        if(carry == 1) {
            result.insertBefore(0, (char)carry + 48);
        }
        return result;
    }
}

BigInt BigInt::operator+(int n) {
    BigInt BI;
    vector<char> temp;
    string str = to_string(n);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        BI.setValue(i, arr[i]);
    }
    return *this + BI;
}

BigInt BigInt::operator++(int n) {
    (*this) = (*this) + 1;
    return *this;
}

BigInt BigInt::operator-(int n) { //only necessary for the numbers 1 and 2
    /*BigInt BI = *this;
    int x = value.at(value.size() - 1) - 48;
    if (x >= n) {
        int result = x - n;
        BI.setValue((int) value.size() - 1, (char) result + 48);
    }
    else {
        x += 10;
        int result = x - n;
        int y = value.at(value.size() - 2) - 48;
        y--;
        BI.setValue((int) value.size() - 1, (char) result + 48);
        BI.setValue((int) value.size() - 2, (char) y + 48);
    }
    return BI;*/
    BigInt BI = *this;
    BigInt BI2;
    int x = BI.parseInt();
    int result = x - n;
    string str = to_string(result);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        BI2.setValue(i, arr[i]);
    }
    return BI2;
}

bool BigInt::operator==(int n) const {
    vector<char> temp;
    string str = to_string(n);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        temp.push_back(arr[i]);
    }
    if(temp.size() != value.size()) {
        return false;
    }
    for(int i = 0; i < temp.size(); i++) {
        if(temp.at(i) - 48 != value.at(i) - 48) {
            return false;
        }
    }
    return true;
}

BigInt & BigInt::operator=(const BigInt &BI) {
    for(int i = 0; i < BI.getValue().size(); i++) {
        setValue(i, BI.getValue().at(i));
    }
    return *this;
}

bool BigInt::operator!=(int n) const {
    vector<char> temp;
    string str = to_string(n);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        temp.push_back(arr[i]);
    }
    if(temp.size() != value.size()) {
        return true;
    }
    for(int i = 0; i < temp.size(); i++) {
        if(temp.at(i) - 48 != value.at(i) - 48) {
            return true;
        }
    }
    return false;
}

bool BigInt::operator!=(const BigInt &BI) const {
    if(value.size() == BI.getValue().size()) {
        for(int i = 0; i < value.size(); i++) {
            if(value.at(i) - 48 != BI.getValue().at(i) - 48) {
                return true;
            }
        }
    }
    return false;
}

bool BigInt::operator<(const BigInt &BI) const {
    if(value.size() == BI.getValue().size()) {
        for(int i = 0; i < value.size(); i++) {
            if(value.at(i) - 48 < BI.getValue().at(i) - 48) {
                return true;
            }
            else if(value.at(i) - 48 > BI.getValue().at(i) - 48) {
                return false;
            }
        }
    }
    else if(value.size() < BI.getValue().size()) {
        return true;
    }
    return false;
}

bool BigInt::operator<=(const BigInt &BI) const {
    if(value.size() == BI.getValue().size()) {
        for(int i = 0; i < value.size(); i++) {
            if(value.at(i) - 48 <= BI.getValue().at(i) - 48) {
                return true;
            }
            else if(value.at(i) - 48 > BI.getValue().at(i) - 48) {
                return false;
            }
        }
    }
    else if(value.size() <= BI.getValue().size()) {
        return true;
    }
    return false;
}

bool BigInt::operator<=(int n) const {
    int x = this->parseInt();
    if(x <= n) {
        return true;
    }
    return false;
}

bool operator<(int n, const BigInt &BI) {
    vector<char> temp;
    string str = to_string(n);
    char arr[str.length() + 1];
    strcpy(arr, str.c_str());
    for(int i = 0; i < str.length(); i++) {
        temp.push_back(arr[i]);
    }
    if(temp.size() == BI.getValue().size()) {
        for(int i = 0; i < temp.size(); i++) {
            if(temp.at(i) - 48 < BI.getValue().at(i) - 48) {
                return true;
            }
            else if(temp.at(i) - 48 > BI.getValue().at(i) - 48) {
                return false;
            }
        }
    }
    else if(temp.size() < BI.getValue().size()) {
        return true;
    }
    return false;
}

int BigInt::parseInt() const {
    int sum = 0;
    int base = 1;
    for(int i = (int)getValue().size() - 1; i >= 0; i--) {
        int intValue = getValue().at(i) - 48;
        sum += intValue * base;
        base *= 10;
    }
    return sum;
}

vector<char> BigInt::getValue() const {
    return value;
}

void BigInt::setValue(int i, char c) {
    if(i + 1 <= value.size()) {
        value.at(i) = c;
    }
    else {
        value.push_back(c);
    }
}

void BigInt::insertBefore(int i, char c) {
    value.insert(value.begin() + i, c);
}