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

class A {
public:
    std::vector<std::shared_ptr<int>> values;
    void add(int x){ 
        std::shared_ptr<int> value_pointer(new int(x));
        values.push_back(value_pointer); 
    }
};
