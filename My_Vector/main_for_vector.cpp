//
// Created by Александр on 07.01.2021.
//

#include "my_vector.hpp"

using std::cout;

int main()
{
    cout << "Testing constructor:\n";
    Vector<int> vec1;
    vec1.print();
    Vector<int> vec2(40);
    vec2.print();

    cout << "\nTesting is_empty() method:\n";
    Vector<int> vec3;
    vec3.print();
    if (vec3.is_empty())
    {
        cout << "Empty.\n";
    }
    else
    {
        cout << "Is not empty.\n";
    }
    vec3.push(2);
    vec3.print();
    if (vec3.is_empty())
    {
        cout << "Empty.\n";
    }
    else
    {
        cout << "Is not empty.\n";
    }

    cout << "\nTesting resize() method:\n";
    Vector<int> vec4(2);
    vec4.print();
    vec4.push(4);
    vec4.push(4);
    vec4.push(4);
    vec4.push(4);
    cout << "After resizing:\n";
    vec4.print();
    
    cout << "\nTesting at() method:\n";
    Vector<int> vec5(2);
    vec5.push(4);
    vec5.push(4);
    vec5.push(4);
    vec5.push(4);
    vec5.print();
    cout << "Correctness index:\n";
    cout << "vec5[3] = " << vec5.at(3) << '\n';
    cout << "Uncorrectness index:\n";
    vec5.insert(6, 4);
    vec5.print();
    cout << "vec5[5](generate exception) = ";
    try
    {
        cout << vec5.at(5) << '\n';
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what();
    }
    cout << "vec5[500](generate exception) = ";
    try
    {
        cout << vec5.at(500) << '\n';
    }
    catch (const std::out_of_range& err)
    {
        std::cerr << err.what();
    }

    cout << "\nTesting push() method:\n";
    Vector<int> vec6(2);
    vec6.push(4);
    vec6.push(4);
    vec6.push(4);
    vec6.push(4);
    vec6.insert(6, 4);
    vec6.print();
    cout << "\nContinue pushing:\n";
    vec6.push(4);
    vec6.print();
    vec6.push(4);
    vec6.print();
    vec6.push(4);
    vec6.print();
    vec6.push(4);
    vec6.print();
    vec6.push(4);
    vec6.print();

    cout << "\nTesting insert() method:\n";
    Vector<int> vec7(2);
    vec7.push(4);
    vec7.push(4);
    vec7.push(4);
    vec7.push(4);
    vec7.insert(6, 4);
    vec7.print();
    cout << "\nContinue inserting (6, 4):\n";
    vec7.insert(6, 4);
    vec7.print();
    vec7.insert(6, 4);
    vec7.print();
    vec7.insert(6, 4);
    vec7.print();
    vec7.insert(6, 4);
    vec7.print();
    cout << "\nInserting (1, 2):\n";
    vec7.insert(1, 2);
    vec7.print();
    cout << "\nContinue inserting (1, 2):\n";
    vec7.insert(1, 2);
    vec7.print();
    vec7.insert(1, 2);
    vec7.print();
    vec7.insert(1, 2);
    vec7.print();
    vec7.insert(1, 2);
    vec7.print();
    vec7.insert(1, 2);
    vec7.print();
    
    cout << "\nInserting (15, 7):\n";
    vec7.insert(15, 7);
    vec7.print();
    vec7.insert(15, 7);
    vec7.print();
    vec7.insert(15, 7);
    vec7.print();
    vec7.insert(15, 7);
    vec7.print();

    cout << "\nTesting pop() method:\n";
    Vector<int> vec8(2);
    vec8.push(4);
    vec8.push(4);
    vec8.push(4);
    vec8.push(4);
    vec8.insert(6, 4);
    vec8.print();
    cout << "Begin pop():\n";
    try {
        vec8.pop();
        vec8.pop();
        vec8.pop();
        vec8.pop();
        vec8.pop();
        vec8.pop();
        vec8.pop();
        vec8.pop();
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what();
        cout << "Stop pop(). vec8 contain: ";
        vec8.print();
    }

    cout << "\nTesting deleteByIndex() method:\n";
    Vector<int> vec9(2);
    vec9.push(4);
    vec9.push(4);
    vec9.push(4);
    vec9.push(4);
    vec9.insert(6, 4);
    vec9.print();
    cout << "Begin deleteByIndex():\n";
    cout << "Delete correctness index [6]:\n";
    vec9.deleteByIndex(6);
    cout << "vec9 after deleting : ";
    vec9.print();
    cout << "Delete correctness index [1]:\n";
    vec9.deleteByIndex(1);
    cout << "vec9 after deleting : ";
    vec9.print();
    cout << "Try delete [500] element: ";
    try
    {
        vec9.deleteByIndex(500);
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what();
    }
    cout << "Try delete [5] element: ";
    try
    {
        vec9.deleteByIndex(5);
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what();
    }
    cout << "Push after removing:";
    vec9.push(9);
    vec9.push(9);
    vec9.push(9);
    vec9.print();

    cout << "\nTesting removeByKey() method:\n";
    Vector<int> vec10(2);
    vec10.push(1);
    vec10.push(2);
    vec10.push(2);
    vec10.push(3);
    vec10.print();
    cout << "Removing key 1: ";
    vec10.removeByKey(1);
    vec10.print();
    cout << "Removing key 2: ";
    vec10.removeByKey(2);
    vec10.print();
    cout << "Removing key 50: ";
    vec10.removeByKey(50);
    vec10.print();
    cout << "Push after removing";
    vec10.push(9);
    vec10.push(9);
    vec10.push(9);
    vec10.push(9);
    vec10.print();


    cout << "\nTesting find() method:\n";
    Vector<int> vec11(2);
    vec11.push(1);
    vec11.push(2);
    vec11.push(2);
    vec11.push(3);
    vec11.print();
    cout << "Correctness find of 2(expected index[1]): ";
    cout << "index = " << vec11.find(2);
    cout << "\nCorrectness find of 3(expected index[3]): ";
    cout << "index = " << vec11.find(3);
    cout << "\nUncorrectness find of 5(expected error): ";
    cout << "index = ";
    try 
    {
        vec11.find(5);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what();
    }

    cout << "\nTesting copy constructor:\n";
    Vector<int> vec12(vec5);
    cout << "vec5:  ";
    vec5.print();
    cout << "vec12: ";
    vec12.print();

    cout << "\nTesting move constructor and size() capacity() methods:\n";
    Vector<int> vec13(std::move(vec5));
    cout << "vec5:  ";
    vec5.print();
    cout << "vec5 size = " << vec5.size();
    cout << "\nvec5 capacity = " << vec5.capacity();
    cout << "\nvec13:  ";
    vec13.print();
    cout << "vec13 size = " << vec13.size();
    cout << "\nvec13 capacity = " << vec13.capacity();

    cout << "\nTesting copy assignment:\n";
    Vector<int> vec14;
    cout << "vec14: ";
    vec14.print();
    vec14 = vec6;
    cout << "vec6:  ";
    vec6.print();
    cout << "vec14: ";
    vec14.print();


    cout << "\nTesting move assignment and size() capacity() methods:\n";
    Vector<int> vec15;
    cout << "vec15:  ";
    vec15.print();
    vec15 = std::move(vec6);
    cout << "vec6:  ";
    vec6.print();
    cout << "vec6 size = " << vec6.size();
    cout << "\nvec6 capacity = " << vec6.capacity();
    cout << "vec15:  ";
    vec15.print();
    cout << "vec15 size = " << vec15.size();
    cout << "\nvec15 capacity = " << vec15.capacity();

    return 0;
}