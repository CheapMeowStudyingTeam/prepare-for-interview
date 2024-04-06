class A
{
private:
    int value;

public:
    A(int n) { value = n; }
    A(A other) { value = other.value; }
}