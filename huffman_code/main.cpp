#include "huffman_code.h"

/*
1. sample.txt 파일에서 사용된 문자와 각 문자의 출현빈도(frequency)를 출력하시오. (예, a: 30, b: 15, ...)
2. 1에서 추출한 값을 사용하여 huffman code를 완성하시오.
3. 완성된 huffman code를 사용하여 sample.txt 파일을 encode 하시오. (sample.enc)
4. 3번에서 enc된 파일을 원래 sample 파일로 decode 하시오. (sample.dec)
5. 디코드된 sample.dec 파일과 원본인 sample.txt 파일이 일치하는지 확인하시오.
6. 압축전과 후의 비트수를 계싼하여 압축률(%)을 계산하시오.
*/

/*
                                [---- 정리 ----]
WindowsOS에서 개행문자(\r\n)로 인해 원본 파일과 비교해 용량 차이가 존재(개행문자를 \n로 처리하기 때문)
Linux, MacOS에서 sample.txt 파일을 생성해 인코딩, 디코딩을 실행해야됨
encoded file format : [file length][serialized tree][encoded content]
*/


int main()
{
    HuffmanCode code = HuffmanCode();
    code.encode();
    cout << "[INFO] compression rate" << code.getCompressionRate("sample.txt", "sample.enc") << "%" << endl;
    code.decode();
    if (code.compareFile())
    {
        cout << "[INFO] decoding success!" << endl;
    }
    return 0;
}