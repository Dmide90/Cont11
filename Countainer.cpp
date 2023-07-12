 
#include <iostream>
#include <vector>

using namespase std;

class Container {
public:
    void insert(int item) {
        _list.push_back(item);
    }

    void remove(int index) {
        if (index >= 0 && index < _list.size()) {
            _list.erase(_list.begin() + index);
        } else {
            throw out_of_range("Index out of range");
        }
    }

    int get(int index) {
        if (index >= 0 && index < _list.size()) {
            return _list[index];
        } else {
            throw out_of_range("Index out of range");
        }
    }

private:
    vector<int> _list;
};

int main() {
    Container container;
    container.insert(1);
    container.insert(2);
    container.insert(3);

   cout << container.get(1) << endl;
    container.remove(0);

    cout << container.get(0) << std::endl;

    return 0;
}
