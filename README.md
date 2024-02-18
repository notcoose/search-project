# Search

Search is a search engine built with C++ that allows for complex queries.
The program takes text files formatted with alternating url and text lines to build inverted indexes of cleaned tokens.
The user is able to then search these indexes with compound queries requiring set unions, intersections, and/or differences.

## Installation

To use this project, the two required files are search.h and search_main.cpp
You can also download any of the .txt files to try the project out with them or to view the required formatting 

## Usage

To use the file, you can compile an output file like this:
"g++/gcc search_main.cpp -o ./a.out"

Then run the output like this:
"./a.out"

Then enter a filename into the terminal

When prompted you can query following these guidelines:
1) Plain words will return all pages containing these terms
2) Multiple plain words will return all pages containing at least one of the words
3) Words with a '+' prefix will require that returned pages contain that word
4) Words with a '-' prefix will take out pages containing that word

NOTE: These queries follow an order of operations such that pages may be removed due to a '-' operation and then be added back later

## Sample Output

User input is denoted with **enboldened**

**cplusplus.txt**
Stand by while building index...
Indexed 86 pages containing 1498 unique terms

Enter query sentence (press enter to quit):  **vector**

Found 8 matching pages
https://www.cplusplus.com/reference/array/array/
https://www.cplusplus.com/reference/bitset/bitset/
https://www.cplusplus.com/reference/forward_list/forward_list/
https://www.cplusplus.com/reference/list/list/
https://www.cplusplus.com/reference/queue/priority_queue/
https://www.cplusplus.com/reference/stack/stack/
https://www.cplusplus.com/reference/vector/vector-bool/
https://www.cplusplus.com/reference/vector/vector/

Enter query sentence (press enter to quit): **vector +container**

Found 7 matching pages
https://www.cplusplus.com/reference/array/array/
https://www.cplusplus.com/reference/forward_list/forward_list/
https://www.cplusplus.com/reference/list/list/
https://www.cplusplus.com/reference/queue/priority_queue/
https://www.cplusplus.com/reference/stack/stack/
https://www.cplusplus.com/reference/vector/vector-bool/
https://www.cplusplus.com/reference/vector/vector/

Enter query sentence (press enter to quit): **vector +container +pointer**

Found 1 matching pages
https://www.cplusplus.com/reference/vector/vector-bool/

Enter query sentence (press enter to quit): **vector +container -pointer**

Found 6 matching pages
https://www.cplusplus.com/reference/array/array/
https://www.cplusplus.com/reference/forward_list/forward_list/
https://www.cplusplus.com/reference/list/list/
https://www.cplusplus.com/reference/queue/priority_queue/
https://www.cplusplus.com/reference/stack/stack/
https://www.cplusplus.com/reference/vector/vector/

Enter query sentence (press enter to quit): **vector bool ratio**

Found 24 matching pages
https://www.cplusplus.com/is_fundamental
https://www.cplusplus.com/reference/array/array/
https://www.cplusplus.com/reference/bitset/bitset/
https://www.cplusplus.com/reference/chrono/duration/
https://www.cplusplus.com/reference/exception/exception_ptr/
https://www.cplusplus.com/reference/forward_list/forward_list/
https://www.cplusplus.com/reference/functional/binary_negate/
https://www.cplusplus.com/reference/functional/unary_negate/
https://www.cplusplus.com/reference/list/list/
https://www.cplusplus.com/reference/queue/priority_queue/
https://www.cplusplus.com/reference/ratio/ratio/
https://www.cplusplus.com/reference/ratio/ratio_add/
https://www.cplusplus.com/reference/ratio/ratio_divide/
https://www.cplusplus.com/reference/ratio/ratio_greater/
https://www.cplusplus.com/reference/ratio/ratio_greater_equal/
https://www.cplusplus.com/reference/ratio/ratio_less/
https://www.cplusplus.com/reference/ratio/ratio_less_equal/
https://www.cplusplus.com/reference/ratio/ratio_multiply/
https://www.cplusplus.com/reference/ratio/ratio_not_equal/
https://www.cplusplus.com/reference/ratio/ratio_subtract/
https://www.cplusplus.com/reference/regex/sub_match/
https://www.cplusplus.com/reference/stack/stack/
https://www.cplusplus.com/reference/vector/vector-bool/
https://www.cplusplus.com/reference/vector/vector/

Enter query sentence (press enter to quit): **L +ratio**

Found 0 matching pages

Enter query sentence (press enter to quit): 
Thank you for searching!
