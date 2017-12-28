#include <iostream>
#include <vector>
#include <AvlTree.h>
#include <fstream>
#include <sstream>
//
// Created by ivi on 12/27/2017.
//

using namespace std;

int main(int argc, const char *argv[]) {

    auto treeToPng = [](AvlTree *tree) {
        ofstream myfile;
        myfile.open("tree.dot");
        myfile << *tree;
        myfile.close();
        //GraphViz not installed
        //system("dot -Tpng tree.dot -o tree.png");
    };
    int val;
    AvlTree *tree = new AvlTree();
    for (int i = 1; i < argc; i++) {
        std::istringstream iss(argv[i]);
        iss >> val;
        tree->insert(val);
    }
    char action = '\0';
    treeToPng(tree);
    while (action != 'q') {
        switch (action) {
            case '\0': // dummy
                break;
            case 's':
                cout << "Search: ";
                cin >> val;
                cout << (tree->search(val) ? "" : "not ") << "found" << endl;
                break;
            case 'd':
                cout << "Delete: ";
                cin >> val;
                tree->remove(val);
                break;
            case 'i':
                cout << "Insert: ";
                cin >> val;
                tree->insert(val);
                break;
            default:
                cout << "Unknown command: " << action << endl;
                break;
        }
        if (action == 'i' || action == 'd')
            treeToPng(tree);
        cout << "(s)earch, (d)elete, (i)nsert, (t)raverse, (q)uit: ";
        cin >> action;
    }
    cout << "Cheerio!" << endl;
    return 0;

}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "[";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "]";
    return out;
}