#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

class BadInput{};

std::vector<char> slice(std::vector<char> vec, int start, int step, int stop){
    int size = vec.size();
    if(start < 0 || start >= size|| stop < 0 || stop > size || step <= 0 ){
        throw BadInput();
    }

    std::vector<char> sliced_vector;
    if(start >= stop){
        return sliced_vector;
    }
    std::vector<char>::iterator it;
    int length = 0;
    for(int i = start; i < stop; i+= step){
        length++;
        sliced_vector.resize(length);
        it = sliced_vector.begin();
        for(int j = 0; j < length; j++){
            it++;
        }
        sliced_vector.insert(it, vec[i]);
    }
    return sliced_vector;
}


void printVector(std::vector<char> vec){
    for (unsigned int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << ' ';
    }
}


class A {
public:
    std::vector<std::shared_ptr<int>> values;

    void add(int x){ 
        std::shared_ptr<int> ptr(new int(x));
        values.push_back(ptr); 
    }
};

// a = 0 1 2 3 4 5<valarray>
// sliced =  1 2 3 4 5

int main() {
    A a, sliced;
    a.add(0); a.add(1); a.add(2); a.add(3); a.add(4); a.add(5);
//    sliced.values = slice(a.values, 1, 1, 4);
    sliced.values = a.values;
    *(sliced.values[0]) = 800;
    std::cout << *(a.values[0]) << std::endl;
    return 0;
}

//add_executable(ex3 provided/test_partB.cpp festival.cpp event_container.cpp open_event.cpp base_event.cpp closed_event.cpp date_wrap.cpp date/date.c)

/* int main(){
    // this syntax initializes a vector with values a,b,c,d,e
    std::vector<char> vec1 {'a', 'b', 'c', 'd', 'e'};
    // returns vector with values a,c
    std::vector<char> vec_sliced = slice(vec1, 0, 2, 4);
    printVector(vec_sliced);
    //std::vector<char> vec1 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z'};

    // returns vector with values b,c,d,e
    //std::vector<char> 
    vec_sliced = slice(vec1, 1, 1, 5);
    return 0;
} */


