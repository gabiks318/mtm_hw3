#include <vector>

class BadInput{};

template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop){
    int size = vec.size();
    if(start < 0 || start >= size|| stop < 0 || stop > size || step <= 0 ){
        throw BadInput();
    }

    std::vector<T> new_vector();
    if(start >= stop){
        return new_vector;
    }
    int length = 0;
    for(int i = start; i < stop; i+= step){
        length++;
        new_vector.resize(length);
        new_vector[length - 1] = vec[i];
    }
}

template <class T>
void printVector(std::vector<T> vec){
    for (std::vector<T>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << ' ';
}

int main(){
    // this syntax initializes a vector with values a,b,c,d,e
    std::vector<char> vec1 {'a', 'b', 'c', 'd', 'e'};
    // returns vector with values a,c
    std::vector<char> vec_sliced = slice(vec1, 0, 2, 4);
    // returns vector with values b,c,d,e
    std::vector<char> vec_sliced = slice(vec1, 1, 1, 5);
}
