/**
 * UVa122
 * 树的层次遍历
 */

#include <iostream>
#include <string>
#include <map>

int main()
{
    using namespace std;
    map<string, string> nodes; string node;
    while(cin >> node) {
        if(node == "()") {
            //
            nodes.clear();
        } else {
            const size_t p = node.find(',');
            nodes[node.substr(p+1, node.length()-p-2)] = node.substr(1, p-1);
        }
    }
    return 0;
}