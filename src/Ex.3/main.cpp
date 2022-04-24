#include <iostream>
#include <vector>
#include <list>


bool removeFrontSpaces(char c){
    if(c != ' ') return true;
    return false;
}

template <class ForwardIterator, class UnaryPredicate>
ForwardIterator cutHead(ForwardIterator first, ForwardIterator last,
                           UnaryPredicate pred)
{
    ForwardIterator result = first;
    while (first!=last) {
        std::cout << *first << '\n';
        if (pred(*first)) {
            return first;
        }
        ++first;
    }
    return result;
}

template < template < class ... > class Container, class ... Args , class UnaryPredicate >
Container<Args...> removeFromFrontUntil(Container< Args...> container, UnaryPredicate pred)
{
    return Container<Args...>(cutHead(container.begin(), container.end(), pred), container.end());
}

int main(){

    std::vector<char> vectorStr = {' ', ' ', ' ', ' ','a','l','a',' '};
    std::vector updated = removeFromFrontUntil(vectorStr, removeFrontSpaces);

    std::string stringBefore = "        ala ";
    std::string stringAfter = removeFromFrontUntil(stringBefore, removeFrontSpaces);

    std::list listBefore = {' ', ' ', ' ', ' ','a','l','a',' '};
    std::list listAfter = removeFromFrontUntil(listBefore, removeFrontSpaces);

    vectorStr.assign(10,'j');
    for( auto c : vectorStr ) std::cout << c;
    std::cout <<'\n';
    for( auto c : updated ) std::cout << c;
    std::cout <<'\n';
    for( auto c : stringAfter ) std::cout << c;
    std::cout <<'\n';
    for( auto c : listAfter ) std::cout << c;
    std::cout <<'\n';
    return 0;
}
