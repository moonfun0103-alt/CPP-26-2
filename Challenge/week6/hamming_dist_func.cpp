#include <iostream> // 입출력을 위한 헤더 파일을 포함합니다[cite: 6].
#include <string>   // 문자열(string)을 사용하기 위한 헤더 파일을 포함합니다[cite: 6].
using namespace std; // std 네임스페이스를 사용하여 std::를 생략하게 해줍니다[cite: 6].

// 입력받은 문자열을 모두 소문자로 변환하여 반환하는 함수입니다[cite: 6].
string toLowerStr(string str) { //[cite: 6]
    string newStr = str; // 원본 문자열을 복사합니다[cite: 6].
    // 범위 기반 for 루프(Range-based for loop)를 사용합니다.
    // char& c 로 참조(reference)를 사용하여 newStr 내부의 실제 문자를 직접 수정합니다[cite: 6].
    for (char& c : newStr) { //[cite: 6]
        c = tolower(c); // tolower() 함수를 통해 문자를 소문자로 변환합니다[cite: 6].
    } //[cite: 6]
    return newStr; // 소문자로 변환된 새로운 문자열을 반환합니다[cite: 6].
} //[cite: 6]

// 입력받은 문자열을 모두 대문자로 변환하여 반환하는 함수입니다 (현재 프로그램 로직에서는 사용되지 않지만 정의되어 있습니다)[cite: 6].
string toUpperStr(string str) { //[cite: 6]
    string newStr = str; //[cite: 6]
    for (char& c : newStr) { //[cite: 6]
        c = toupper(c); // toupper() 함수를 통해 문자를 대문자로 변환합니다[cite: 6].
    } //[cite: 6]
    return newStr; //[cite: 6]
} //[cite: 6]

// 두 DNA 문자열 간의 '해밍 거리(Hamming Distance)'를 계산하는 함수입니다[cite: 6].
// 해밍 거리는 길이가 같은 두 문자열에서 같은 위치에 있는 문자가 서로 다른 개수를 의미합니다.
int calcHammingDist(string s1, string s2) { //[cite: 6]
    // 대소문자 차이로 인한 오류를 방지하기 위해 두 문자열을 모두 소문자로 변환합니다[cite: 6].
    s1 = toLowerStr(s1); //[cite: 6]
    s2 = toLowerStr(s2); //[cite: 6]
    
    int count = 0; // 다른 문자의 개수를 저장할 변수를 0으로 초기화합니다[cite: 6].
    
    // 문자열의 길이만큼 반복하면서 각 위치의 문자를 비교합니다[cite: 6].
    for (int i = 0; i < s1.length(); i++) { //[cite: 6]
        if (s1[i] != s2[i]) // 같은 위치(i)의 문자가 서로 다르다면[cite: 6]
            count += 1; // count를 1 증가시킵니다[cite: 6].
    } //[cite: 6]
    
    return count; // 최종적으로 계산된 해밍 거리를 반환합니다[cite: 6].
} //[cite: 6]

int main() { //[cite: 6]
    string s1, s2; // 입력받을 두 개의 DNA 문자열 변수를 선언합니다[cite: 6].

    while (1) { // 무한 루프를 돌면서 올바른 입력이 들어올 때까지 반복합니다[cite: 6].
        cout << "DNA1: "; //[cite: 6]
        cin >> s1; // 첫 번째 DNA 문자열을 입력받습니다[cite: 6].
        cout << "DNA2: "; //[cite: 6]
        cin >> s2; // 두 번째 DNA 문자열을 입력받습니다[cite: 6].

        // 두 문자열의 길이가 다르면 해밍 거리를 계산할 수 없으므로 오류를 출력합니다[cite: 6].
        if (s1.length() != s2.length()) { //[cite: 6]
            cout << "오류: 길이가 다름" << endl; //[cite: 6]
            continue; // 다시 처음으로 돌아가서 문자열을 재입력받습니다[cite: 6].
        } //[cite: 6]
        else { // 두 문자열의 길이가 같다면[cite: 6]
            // calcHammingDist 함수를 호출하여 해밍 거리를 계산하고 count 변수에 저장합니다[cite: 6].
            int count = calcHammingDist(s1, s2); //[cite: 6]
            // 결과를 출력합니다[cite: 6].
            cout << "해밍 거리는 " << count << endl; //[cite: 6]
            break; // 올바르게 계산이 끝났으므로 무한 루프를 탈출합니다[cite: 6].
        } //[cite: 6]
    } //[cite: 6]

    return 0; // 프로그램이 정상적으로 종료되었음을 운영체제에 알립니다[cite: 6].
} //[cite: 6]