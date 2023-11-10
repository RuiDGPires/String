#include <iostream>
#include <String>

using namespace std;
using namespace rui;

int main(int argc, const char *argv[]) {
    String s = "abcde 书⼈ яшвфд δβΩω";
    
    /* Indexes are */
    size_t index = 3; // default
                      
    if (argc >= 2)
        index = atol(argv[1]); // I don't really care about type sizes 

    s.mod(std::make_shared<WordColorer>(index, Color::BLUE)); 

    cout << s << "\n";

    return 0;
}

