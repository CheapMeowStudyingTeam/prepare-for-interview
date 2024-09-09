### 例子

#### 例 1：给定一个 tuple 返回一个访问表

```cpp
#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <tuple>

template<std::size_t N, typename T, typename F>
void helper(T t, F f)
{
    f(std::get<N>(t));
}

template<typename Tuple, typename Func>
constexpr void access(std::size_t index, Tuple&& tuple, Func&& f)
{
    constexpr auto length   = std::tuple_size<std::decay_t<decltype(tuple)>>::value;
    using FuncType          = void (*)(decltype(tuple), decltype(f));
    constexpr auto fn_table = []<std::size_t... I>(std::index_sequence<I...>) {
        std::array<FuncType, length> table = {helper<I, decltype(tuple), decltype(f)>...};
        return table;
    }(std::make_index_sequence<length> {});
    return fn_table[index](std::forward<Tuple>(tuple), std::forward<Func>(f));
}

int main()
{
    std::tuple<int, char, std::string> a     = {1, 'a', "123"};
    auto                               f     = [](auto&& v) { std::cout << v << std::endl; };
    std::size_t                        index = 0;
    access(index, a, f); // => 1
    index = 2;
    access(index, a, f); // => 123
}
```

`std::decay_t<decltype()>` 的作用是获取一个表达式的类型，但是去除了该类型的引用、cv（const 或 volatile 修饰符）限定符以及数组类型，使其退化为对应的原始类型。

C++20 中，lambda 可以使用模板参数列表

`std::size_t... I` 表示可变参数模板，这些参数的类型都是 `std::size_t`

`std::index_sequence<I...>` 使用了模板展开，`std::make_index_sequence<length> {}` 生成了 `I...` 调用了这个模板 lambda

#### 例 2：记录类型信息用于反射获取

```cpp
#include <string>
#include <iostream>
#include <unordered_map>
#include <span>
#include <functional>

struct Person
{
    std::string_view name;
    std::size_t age;

    void say(std::string_view msg) { std::cout << name << " say: " << msg << std::endl; }
};

class Any;

struct Type
{
    using Destroy = void (*)(void*);
    using Construct = void* (*)(void*);
    using Method = Any(*)(void*, std::span<Any>);
    using Field = std::pair<Type*, std::size_t>;

    std::string_view name;                                // 类型名称
    Destroy destroy;                                      // 析构函数
    Construct copy;                                       // 拷贝构造
    Construct move;                                       // 移动构造
    std::unordered_map<std::string_view, Field> fields;   // 字段信息
    std::unordered_map<std::string_view, Method> methods; // 方法信息
};

class Any
{
    Type* type;   // 指向类型信息
    void* data;   // 指向实际数据
    uint8_t flag; // 一些特殊的 flag 用于各种标记

public:
    Any() : type(nullptr), data(nullptr), flag(0) {}
    Any(Type* type, void* data) : type(type), data(data), flag(0B00000001) {}
    Any(const Any& other);
    Any(Any&& other);
    template <typename T>
    Any(T&& value); // 用于对值类型装箱
    ~Any();

    template <typename T>
    T& cast(); // 用于拆箱

    Type* GetType() const { return type; } // 获取类型信息

    Any invoke(std::string_view name, std::span<Any> args); // 用于调用成员函数

    void foreach(const std::function<void(std::string_view, Any)>& fn); // 用于遍历成员字段
};

Any::Any(const Any& other) // 拷贝构造
{
    type = other.type;
    data = type->copy(other.data);
    flag = 0;
}

Any::Any(Any&& other) // 移动构造
{
    type = other.type;
    data = type->move(other.data);
    flag = 0;
}

template <typename T>
Any::Any(T&& value) // 用于对值类型装箱
{
    type = type_of<std::decay_t<T>>();
    data = new std::decay_t<T>(std::forward<T>(value));
    flag = 0;
}

Any::~Any()
{
    if (!(flag & 0B00000001)) // 检查 flag
    {
        if (data && type)
        {
            type->destroy(data);
        }
    }
}

template <typename T>
T& Any::cast()
{
    if (type != type_of<T>()) // type_of用于返回 T 类型的 Type 信息
    {
        throw std::runtime_error{ "type mismatch" };
    }
    return *static_cast<T*>(data);
}

void Any::foreach(const std::function<void(std::string_view, Any)>& fn)
{
    for (auto& [name, field] : type->fields)
    {
        fn(name, Any(field.first, static_cast<char*>(data) + field.second));
    }
}

Any Any::invoke(std::string_view name, std::span<Any> args)
{
    auto it = type->methods.find(name);
    if (it == type->methods.end())
    {
        throw std::runtime_error{ "method not found" };
    }
    return it->second(data, args);
}

template <typename T>
struct member_fn_traits;

template <typename R, typename C, typename... Args>
struct member_fn_traits<R(C::*)(Args...)> // 类型萃取，萃取函数参数等
{
    using return_type = R;
    using class_type = C;
    using args_type = std::tuple<Args...>;
};

template <auto ptr>
auto* type_ensure()
{
    using traits = member_fn_traits<decltype(ptr)>;
    using class_type = typename traits::class_type;
    using result_type = typename traits::return_type;
    using args_type = typename traits::args_type;

    return +[](void* object, std::span<Any> args) -> Any
        {
            auto self = static_cast<class_type*>(object);
            return[=]<std::size_t... Is>(std::index_sequence<Is...>)
            {
                if constexpr (std::is_void_v<result_type>)
                {
                    (self->*ptr)(args[Is].cast<std::tuple_element_t<Is, args_type>>()...);
                    return Any{};
                }
                else
                {
                    auto result = (self->*ptr)(args[Is].cast<std::tuple_element_t<Is, args_type>>()...);
                    return Any{ result };
                }
            }(std::make_index_sequence<std::tuple_size_v<args_type>>{});
        };
}

template <typename T>
Type* type_of()
{
    static Type type;
    type.name = typeid(T).name();
    type.destroy = [](void* obj) { delete static_cast<T*>(obj); };
    type.copy = [](void* obj) { return (void*)(new T(*static_cast<T*>(obj))); };
    type.move = [](void* obj) { return (void*)(new T(std::move(*static_cast<T*>(obj)))); };
    return &type;
}

template <>
Type* type_of<Person>()
{
    static Type type;
    type.name = "Person";
    type.destroy = [](void* obj) { delete static_cast<Person*>(obj); };
    type.copy = [](void* obj) { return (void*)(new Person(*static_cast<Person*>(obj))); };
    type.move = [](void* obj) { return (void*)(new Person(std::move(*static_cast<Person*>(obj)))); };
    type.fields.insert({ "name", {type_of<std::string_view>(), offsetof(Person, name)} });
    type.fields.insert({ "age", {type_of<std::size_t>(), offsetof(Person, age)} });
    type.methods.insert({ "say", type_ensure<&Person::say>() });
    return &type;
};

int main()
{
    Any person = Person{ "Tom", 18 };
    std::vector<Any> args = { std::string_view{"Hello"} };
    person.invoke("say", args);
    // => Tom say: Hello

    auto f = [](std::string_view name, Any value)
        {
            if (value.GetType() == type_of<std::string_view>())
            {
                std::cout << name << " = " << value.cast<std::string_view>() << std::endl;
            }
            else if (value.GetType() == type_of<std::size_t>())
            {
                std::cout << name << " = " << value.cast<std::size_t>() << std::endl;
            }
        };

    person.foreach(f);
    // => 
    // name = Tom
    // age = 18
    return 0;
}
```

一开始，将任意类型装箱到自定义类型的方法就很酷

`new std::decay_t<T>(std::forward<T>(value));` 将任意类型的值存到一个地址里面

我不知道这里为什么需要 `std::forward`

然后他这个 `member_fn_traits` 用来提取类型的方法就很酷，实现了从任意一个函数指针提取类的类型、返回值的类型、参数的类型

`type_ensure` 里面就是，输入 Any 类型的参数，同时我还知道函数的参数类型，所以将 Any 类型的参数拆箱为已知的参数类型，然后调用函数，如果不是 void，就保存返回值，装箱成 Any

这里用到了 `std::index_sequence<Is...>` 和 `std::make_index_sequence` 配合，是为了使用折叠表达式，展开 `std::span<Any> args`

类似 for，但是 index_sequence 是用于编译器求值，每一个元素都会求值；for 是运行期求值，可能提前 return

