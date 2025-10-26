#include <iostream>
#include <cassert>
#include "lista.h"

using namespace std;

void testInsertAtBeginning() {
    cout << "Testing insertAtBeginning..." << endl;
    LinkedList list;
    
    list.insertAtBeginning(10);
    assert(list.getSize() == 1);
    
    list.insertAtBeginning(20);
    assert(list.getSize() == 2);
    
    list.insertAtBeginning(30);
    assert(list.getSize() == 3);
    
    cout << "insertAtBeginning tests passed!" << endl;
}

void testInsertAtEnd() {
    cout << "Testing insertAtEnd..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    assert(list.getSize() == 1);
    
    list.insertAtEnd(20);
    assert(list.getSize() == 2);
    
    list.insertAtEnd(30);
    assert(list.getSize() == 3);
    
    cout << "insertAtEnd tests passed!" << endl;
}

void testInsertAtPosition() {
    cout << "Testing insertAtPosition..." << endl;
    LinkedList list;
    
    // Insert at position 0 (empty list)
    list.insertAtPosition(10, 0);
    assert(list.getSize() == 1);
    
    // Insert at end
    list.insertAtPosition(30, 1);
    assert(list.getSize() == 2);
    
    // Insert in middle
    list.insertAtPosition(20, 1);
    assert(list.getSize() == 3);
    
    // Insert at beginning
    list.insertAtPosition(5, 0);
    assert(list.getSize() == 4);
    
    cout << "insertAtPosition tests passed!" << endl;
}

void testDeleteAtBeginning() {
    cout << "Testing deleteAtBeginning..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    list.deleteAtBeginning();
    assert(list.getSize() == 2);
    
    list.deleteAtBeginning();
    assert(list.getSize() == 1);
    
    list.deleteAtBeginning();
    assert(list.getSize() == 0);
    
    // Delete from empty list (should handle gracefully)
    list.deleteAtBeginning();
    assert(list.getSize() == 0);
    
    cout << "deleteAtBeginning tests passed!" << endl;
}

void testDeleteAtEnd() {
    cout << "Testing deleteAtEnd..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    list.deleteAtEnd();
    assert(list.getSize() == 2);
    
    list.deleteAtEnd();
    assert(list.getSize() == 1);
    
    list.deleteAtEnd();
    assert(list.getSize() == 0);
    
    // Delete from empty list
    list.deleteAtEnd();
    assert(list.getSize() == 0);
    
    cout << "deleteAtEnd tests passed!" << endl;
}

void testDeleteAtPosition() {
    cout << "Testing deleteAtPosition..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    
    // Delete from middle
    list.deleteAtPosition(1);
    assert(list.getSize() == 3);
    
    // Delete from beginning
    list.deleteAtPosition(0);
    assert(list.getSize() == 2);
    
    // Delete from end
    list.deleteAtPosition(1);
    assert(list.getSize() == 1);
    
    // Delete last element
    list.deleteAtPosition(0);
    assert(list.getSize() == 0);
    
    cout << "deleteAtPosition tests passed!" << endl;
}

void testSearch() {
    cout << "Testing search..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    assert(list.search(10) == true);
    assert(list.search(20) == true);
    assert(list.search(30) == true);
    assert(list.search(40) == false);
    assert(list.search(5) == false);
    
    cout << "search tests passed!" << endl;
}

void testReverse() {
    cout << "Testing reverse..." << endl;
    LinkedList list;
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    list.reverse();
    // After reverse: 30 -> 20 -> 10
    assert(list.getSize() == 3);
    
    cout << "reverse tests passed!" << endl;
}

void testEmptyList() {
    cout << "Testing empty list operations..." << endl;
    LinkedList list;
    
    assert(list.getSize() == 0);
    assert(list.search(10) == false);
    
    list.deleteAtBeginning();  // Should not crash
    list.deleteAtEnd();         // Should not crash
    list.deleteAtPosition(0);   // Should not crash
    list.reverse();             // Should not crash
    
    cout << "empty list tests passed!" << endl;
}

void testSingleElement() {
    cout << "Testing single element operations..." << endl;
    LinkedList list;
    
    list.insertAtEnd(42);
    assert(list.getSize() == 1);
    assert(list.search(42) == true);
    
    list.reverse();
    assert(list.getSize() == 1);
    
    list.deleteAtBeginning();
    assert(list.getSize() == 0);
    
    cout << "single element tests passed!" << endl;
}

void testDisplay() {
    cout << "Testing display (visual check)..." << endl;
    LinkedList list;
    
    cout << "Empty list: ";
    list.display();
    
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    
    cout << "List with 3 elements: ";
    list.display();
    
    cout << "display tests completed (check output visually)" << endl;
}

int main() {
    cout << "=== Running LinkedList Test Suite ===" << endl << endl;
    
    testInsertAtBeginning();
    testInsertAtEnd();
    testInsertAtPosition();
    testDeleteAtBeginning();
    testDeleteAtEnd();
    testDeleteAtPosition();
    testSearch();
    testReverse();
    testEmptyList();
    testSingleElement();
    testDisplay();
    
    cout << endl << "=== All tests passed! ===" << endl;
    
    return 0;
}