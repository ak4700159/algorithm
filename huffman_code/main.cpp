#include "huffman_code.h"

/*
1. sample.txt 파일에서 사용된 문자와 각 문자의 출현빈도(frequency)를 출력하시오. (예, a: 30, b: 15, ...)
2. 1에서 추출한 값을 사용하여 huffman code를 완성하시오.
3. 완성된 huffman code를 사용하여 sample.txt 파일을 encode 하시오. (sample.enc)
4. 3번에서 enc된 파일을 원래 sample 파일로 decode 하시오. (sample.dec)
5. 디코드된 sample.dec 파일과 원본인 sample.txt 파일이 일치하는지 확인하시오.
6. 압축전과 후의 비트수를 계싼하여 압축률(%)을 계산하시오.
*/

int main()
{
    HuffmanCode code = HuffmanCode();
    code.printFreq();
    return 0;
}