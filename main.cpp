#include <iostream>
#include <String>

using namespace std;
using namespace rui;

int main(int argc, const char *argv[]) {
    String s = "abcde 书⼈ яшвфд δβΩω";
    
    /* Indexes are 1-based */
    size_t index = 3; // default
                      
    if (argc >= 2)
        index = atol(argv[1]); // I don't really care about type sizes 
                               //
    auto colorer = std::make_shared<WordColorer>(index, Color::BLUE);
    s.mod(colorer); 

    cout << s << "\n";
    s += " доброе!";
    cout << s << "\n";
    colorer->set_index(colorer->get_index() - 1);
    cout << s << "\n";

    return 0;
}

