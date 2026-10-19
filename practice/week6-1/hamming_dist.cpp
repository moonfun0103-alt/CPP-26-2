#include <iostream> // 입출력을 위한 헤더 파일 포함 (cout, cin, endl 사용)
#include <string>   // 문자열 처리를 위한 헤더 파일 포함 (string 타입 사용)
using namespace std; // std 네임스페이스를 사용하여 std::를 생략할 수 있게 함

int main() {
    string s1, s2;   // 두 개의 DNA 문자열을 저장할 변수 선언
    int count = 0;   // 해밍 거리(다름의 개수)를 저장할 변수를 0으로 초기화

    // 첫 번째 DNA 문자열 입력 받기
    cout << "DNA1: ";
    cin >> s1;
    
    // 두 번째 DNA 문자열 입력 받기
    cout << "DNA2: ";
    cin >> s2;

    // 두 문자열의 길이가 다르면 해밍 거리를 계산할 수 없으므로 오류 처리
    if (s1.length() != s2.length())
        cout << "오류: 길이가 다름" << endl;
    else {
        // 두 문자열의 길이가 같을 경우 비교 시작
        // 문자열의 처음(인덱스 0)부터 끝까지 반복
        for (int i = 0; i < s1.length(); i++) {
            // 같은 위치(인덱스 i)의 문자가 서로 다르면
            if (s1[i] != s2[i])
                count += 1; // 카운트(해밍 거리)를 1 증가시킴
        }
        // 계산된 최종 해밍 거리 출력
        cout << "해밍 거리는 " << count << endl;
    }
    
    return 0; // 프로그램 정상 종료
}