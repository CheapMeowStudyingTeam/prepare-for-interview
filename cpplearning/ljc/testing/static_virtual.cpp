class A
{
public:
    A() {};
    ~A() = default;
    static virtual void test() {}
};

int main()
{
    A a;
    return 0;
}
