template<unsigned int SIZE>
struct PublicAlign32pow2
{
    enum
    {
        first = SIZE | SIZE >> 1,
        second = first | first >> 2,
        third = second | second >> 4,
        value = third | third >> 8
    };
};

template<unsigned int SIZE, class type = void>
struct CheckSize
{
    enum{value = -1};
};

template<unsigned int SIZE>
struct CheckSize<SIZE, typename std::enable_if<(PublicAlign32pow2<SIZE>::value < 0x7fffffff)>::type>
{
    enum{value = PublicAlign32pow2<SIZE>::value+1};
};

template <typename T, template <typename...> class Template>
struct is_specialization_of : std::false_type {};

template <template <typename...> class Template, typename... Args>
struct is_specialization_of<Template<Args...>, Template>
        : std::true_type {};