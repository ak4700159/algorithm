#include "huffman_code.h"

/*
1. sample.txt 파일에서 사용된 문자와 각 문자의 출현빈도(frequency)를 출력하시오. (예, a: 30, b: 15, ...)
2. 1에서 추출한 값을 사용하여 huffman code를 완성하시오.
3. 완성된 huffman code를 사용하여 sample.txt 파일을 encode 하시오. (sample.enc)
4. 3번에서 enc된 파일을 원래 sample 파일로 decode 하시오. (sample.dec)
5. 디코드된 sample.dec 파일과 원본인 sample.txt 파일이 일치하는지 확인하시오.
6. 압축전과 후의 비트수를 계싼하여 압축률(%)을 계산하시오.
*/

// int main()
// {
//     HuffmanCode code = HuffmanCode();
//     code.printFreq();
//     return 0;
// }

int main() {
    Heap heap(10);
    heap.insert(Node('a', 10));
    heap.insert(Node('b', 5));
    heap.insert(Node('c', 8));
    heap.insert(Node('d', 2));
    heap.insert(Node('e', 12));
    heap.insert(Node('f', 13));
    heap.insert(Node('f', 3));

    heap.printHeap(); // 힙 내용 출력

    Node n1 = heap.remove();
    std::cout << "Removed node1: ";
    n1.printNode();

    Node n2 = heap.remove();
    std::cout << "Removed node2: ";
    n2.printNode();

    Node n3 = heap.remove();
    std::cout << "Removed node3: ";
    n3.printNode();


    heap.printHeap(); // 다시 출력
    return 0;
}