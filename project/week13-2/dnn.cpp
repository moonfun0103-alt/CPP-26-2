#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// 1. 벡터 출력 함수
void printVector(const vector<double>& values)
{
    cout << "[ ";
    for (double value : values)
    {
        cout << value << " ";
    }
    cout << "]" << endl;
}

// ============================================================
// 2. 두 벡터의 내적(dot product)을 계산하는 함수
// ============================================================
//
// a = [a1, a2, a3]
// b = [b1, b2, b3]
//
// dotProduct(a, b)
// = a1*b1 + a2*b2 + a3*b3
//
// ============================================================
double dotProduct(const vector<double>& a, const vector<double>& b) {
    // [TODO] 두 벡터의 크기가 다르면 내적을 구할 수 없으므로 에러 메시지 출력
    if (a.size() != b.size())
    {
        cout << "[Error] dotProduct: 두 벡터의 크기가 다릅니다. ("
             << a.size() << " vs " << b.size() << ")" << endl;
        return 0.0;
    }

    // [TODO] 같은 위치의 원소끼리 곱해서 모두 더한다
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

// ============================================================
// 3. Layer 추상 클래스
// ============================================================
//
// Dense, ReLU, Sigmoid 등
// 모든 Layer가 공통적으로 가져야 하는 기능을 정의
//
// ============================================================
class Layer
{
public:
    // 입력 벡터를 받아 출력 벡터를 반환
    virtual vector<double> forward(const vector<double>& input) = 0;

    // Layer 이름 반환
    virtual string getName() const = 0;

    // 부모 포인터를 이용해서 자식 객체를 삭제하기 위해 가상 소멸자 선언
    virtual ~Layer() { }
};

// 4. Dense Layer
// output = W * input + bias
// 하나의 뉴런:  y = w1*x1 + w2*x2 + ... + bias
// 즉: y = dotProduct(weight, input) + bias
class Dense : public Layer {
private:
    vector<vector<double>> weights; // 여러 뉴런의 가중치
    vector<double> bias;            // 각 뉴런의 bias
public:
    // 생성자
    Dense(const vector<vector<double>>& weights, const vector<double>& bias) {
        this->weights = weights;
        this->bias = bias;
    }

    // Forward Propagation
    vector<double> forward(const vector<double>& input) override {
        vector<double> output;

        // 출력 뉴런 개수만큼 반복
        // [TODO] 각 뉴런마다 dotProduct(weight, input) + bias 계산 후 저장
        for (size_t i = 0; i < weights.size(); i++)
        {
            double value = dotProduct(weights[i], input) + bias[i];
            output.push_back(value);
        }

        return output;
    }

    // Layer 이름 반환
    string getName() const override {
        return "Dense";
    }
};

// 5. ReLU Layer
// x > 0  → x,  x <= 0 → 0
class ReLU : public Layer {
public:
    vector<double> forward(const vector<double>& input) override {
        vector<double> output;

        // [TODO] 음수(0 이하)는 0으로, 양수는 그대로 통과
        for (double value : input)
        {
            if (value > 0)
            {
                output.push_back(value);
            }
            else
            {
                output.push_back(0.0);
            }
        }

        return output;
    }

    string getName() const override {
        return "ReLU";
    }
};

// 6. Sigmoid Layer
//             1
// y = -----------------
//        1 + e^(-x)
// 출력 범위: 0 ~ 1
class Sigmoid : public Layer {
public:
    vector<double> forward(const vector<double>& input) override {
        vector<double> output;
        for (double value : input) {
            double result = 1.0 / (1.0 + exp(-value));
            output.push_back(result);
        }
        return output;
    }
    string getName() const override {
        return "Sigmoid";
    }
};

int main()
{
    cout << "==============================" << endl;
    cout << "       Simple C++ DNN" << endl;
    cout << "==============================" << endl;

    // 1. 입력 데이터
    vector<double> input = {1.0, 0.5};

    cout << endl;
    cout << "Input" << endl;
    printVector(input);

    // 2. 첫 번째 Dense Layer
    // Input Node  : 2개, Output Node : 3개,  따라서 Weight Matrix는 3 x 2
    vector<vector<double>> weights1 =
    {
        { 0.5, -0.2 },
        {-0.3,  0.8 },
        { 0.7,  0.1 }
    };
    vector<double> bias1 = {0.1, -0.1, 0.05};

    // 3. 두 번째 Dense Layer
    // Input Node  : 3개, Output Node : 1개, 따라서 Weight Matrix는 1 x 3
    vector<vector<double>> weights2 =
    {
        { 0.6, -0.4, 0.9 }
    };

    vector<double> bias2 = {-0.2};

    // 4. Neural Network 생성
    // Input(2) → Dense(2 → 3) → ReLU → Dense(3 → 1) → Sigmoid
    vector<Layer*> network;

    // 첫 번째 Dense Layer
    network.push_back(new Dense(weights1, bias1));

    // ReLU Layer
    network.push_back(new ReLU());

    // 두 번째 Dense Layer
    network.push_back(new Dense(weights2, bias2));

    // Sigmoid Layer
    network.push_back(new Sigmoid());

    // 5. Forward Propagation
    vector<double> output = input;

    cout << endl;
    cout << "================================" << endl;
    cout << "     Forward Propagation" << endl;
    cout << "================================" << endl;

    // Layer* 하나를 이용하여 서로 다른 객체(Dense/ReLU/Sigmoid)의 forward()를 호출한다.
    // <다형성>
    for (Layer* layer : network)
    {
        output = layer->forward(output);
        cout << endl;
        cout << layer->getName() << endl;
        printVector(output);
    }

    // 6. 최종 출력
    cout << endl;
    cout << "================================" << endl;
    cout << "          Final Result" << endl;
    cout << "================================" << endl;

    cout << "Output : ";
    printVector(output);

    // Sigmoid 결과값을 이용하여 간단하게 이진 분류
    // 0.5 이상 → Class 1
    // 0.5 미만 → Class 0

    if (output[0] >= 0.5)
    {
        cout << "Prediction : Class 1" << endl;
    }
    else
    {
        cout << "Prediction : Class 0" << endl;
    }

    // 7. 동적 객체 메모리 해제
    for (Layer* layer : network)
    {
        delete layer;
    }

    return 0;
}