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
    // 두 벡터의 크기가 다르면 내적을 구할 수 없으므로 에러 메시지 출력
    if (a.size() != b.size())
    {
        cout << "[Error] dotProduct: 두 벡터의 크기가 다릅니다. ("
             << a.size() << " vs " << b.size() << ")" << endl;
        return 0.0;
    }

    // 같은 위치의 원소끼리 곱해서 모두 더한다
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
        // 각 뉴런마다 dotProduct(weight, input) + bias 계산 후 저장
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

        // 음수(0 이하)는 0으로, 양수는 그대로 통과
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

// 7. Step Function Layer (Heaviside)
// x >= 0 → 1,  x < 0 → 0
class Step : public Layer {
public:
    vector<double> forward(const vector<double>& input) override {
        vector<double> output;

        // 0 이상이면 1, 음수이면 0
        for (double value : input)
        {
            if (value >= 0)
            {
                output.push_back(1.0);
            }
            else
            {
                output.push_back(0.0);
            }
        }

        return output;
    }

    string getName() const override {
        return "Step";
    }
};

// 8. 기능별 테스트 함수
// 각 함수/Layer가 요구사항대로 동작하는지 하나씩 확인한다
void testFunctions()
{
    cout << endl;
    cout << "================================" << endl;
    cout << "        Function Test" << endl;
    cout << "================================" << endl;

    vector<double> x = {1.0, 0.5};

    // (1) dotProduct : expected 0.6
    vector<double> w = {0.8, -0.4};
    cout << endl;
    cout << "[Test 1] dotProduct" << endl;
    cout << dotProduct(x, w) << endl;

    // (2) dotProduct : 두 벡터의 크기가 다른 경우 → 에러 메시지
    vector<double> w3 = {0.8, -0.4, 0.1};
    cout << endl;
    cout << "[Test 2] dotProduct (size mismatch)" << endl;
    cout << dotProduct(x, w3) << endl;

    // (3) Dense : expected [ 0.7 0.55 -0.1 ]
    vector<vector<double>> testWeights =
    {
        { 0.8, -0.4 },
        { 0.3,  0.9 },
        {-0.5,  0.2 }
    };
    vector<double> testBias = {0.1, -0.2, 0.3};

    Dense dense(testWeights, testBias);
    vector<double> denseOutput = dense.forward(x);
    cout << endl;
    cout << "[Test 3] Dense" << endl;
    printVector(denseOutput);

    // (4) ReLU : 음수는 0, 양수는 그대로
    ReLU relu;
    cout << endl;
    cout << "[Test 4] ReLU" << endl;
    printVector(relu.forward(denseOutput));

    // (5) Sigmoid : 0 ~ 1 사이 값으로 변환
    Sigmoid sigmoid;
    cout << endl;
    cout << "[Test 5] Sigmoid" << endl;
    printVector(sigmoid.forward(denseOutput));

    // (6) Step : 0 이상이면 1, 아니면 0
    Step step;
    cout << endl;
    cout << "[Test 6] Step" << endl;
    printVector(step.forward(denseOutput));
}

// 9. 네트워크 실행 함수
// Input(2) → Dense(2 → 3) → ReLU 또는 Step → Dense(3 → 1) → Sigmoid
// useStep = false → ReLU 사용,  useStep = true → Step 사용
void runNetwork(const vector<double>& input, bool useStep)
{
    // 첫 번째 Dense Layer
    // Input Node  : 2개, Output Node : 3개,  따라서 Weight Matrix는 3 x 2
    vector<vector<double>> weights1 =
    {
        { 0.5, -0.2 },
        {-0.3,  0.8 },
        { 0.7,  0.1 }
    };
    vector<double> bias1 = {0.1, -0.1, 0.05};

    // 두 번째 Dense Layer
    // Input Node  : 3개, Output Node : 1개, 따라서 Weight Matrix는 1 x 3
    vector<vector<double>> weights2 =
    {
        { 0.6, -0.4, 0.9 }
    };
    vector<double> bias2 = {-0.2};

    // Neural Network 생성
    vector<Layer*> network;

    network.push_back(new Dense(weights1, bias1));

    // 활성화 함수 선택 (ReLU 또는 Step)
    if (useStep)
    {
        network.push_back(new Step());
    }
    else
    {
        network.push_back(new ReLU());
    }

    network.push_back(new Dense(weights2, bias2));
    network.push_back(new Sigmoid());

    cout << "Input" << endl;
    printVector(input);

    // Forward Propagation
    vector<double> output = input;

    // Layer* 하나를 이용하여 서로 다른 객체의 forward()를 호출한다.
    // <다형성>
    for (Layer* layer : network)
    {
        output = layer->forward(output);
        cout << endl;
        cout << layer->getName() << endl;
        printVector(output);
    }

    // 최종 출력
    cout << endl;
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

    // 동적 객체 메모리 해제
    for (Layer* layer : network)
    {
        delete layer;
    }
}

int main()
{
    cout << "==============================" << endl;
    cout << "       Simple C++ DNN" << endl;
    cout << "==============================" << endl;

    // 1. 기능별 테스트
    testFunctions();

    // 2. 입력 데이터 (예측 결과가 서로 다른 2개의 케이스)
    vector<double> input1 = {1.0, 0.5};
    vector<double> input2 = {0.0, 1.0};

    // 3. ReLU를 사용한 네트워크
    cout << endl;
    cout << "================================" << endl;
    cout << "   Case 1 : Input 1 + ReLU" << endl;
    cout << "================================" << endl;
    runNetwork(input1, false);

    cout << endl;
    cout << "================================" << endl;
    cout << "   Case 2 : Input 2 + ReLU" << endl;
    cout << "================================" << endl;
    runNetwork(input2, false);

    // 4. ReLU를 Step(Heaviside)으로 바꾼 네트워크
    cout << endl;
    cout << "================================" << endl;
    cout << "   Case 3 : Input 1 + Step" << endl;
    cout << "================================" << endl;
    runNetwork(input1, true);

    cout << endl;
    cout << "================================" << endl;
    cout << "   Case 4 : Input 2 + Step" << endl;
    cout << "================================" << endl;
    runNetwork(input2, true);

    return 0;
}