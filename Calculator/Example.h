#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <sstream>

///----------------------------------------------------------------------------|
/// Калькулятор. Версия - 0.3 (Демо)
/// MSYS64 GCC 9.2 C++03      -finput-charset=CP1251
/// QT Creator 4.11.0
///
/// Уже с рекурсией, но без графов и полиморфизма ...
/// ... до совершенства ещё далеко.
///
/// Реализовано:
///     - синтаксический разбор строки любой длины
///     - текущие операции(через запятую): "+", "-", "*", "^"(степень числа)
///     - соблюдается приоритет операций согласно таблице priority_table
///     - можно приорететить скобочками.
///     - появились юзабилити-требования соблюдения правил синтаксиса.
///     - существует алгоритм добавления новой операции(в исходный код).
///     - поддержка формата double d = -12.55e-4;
///     - русский язык(проверено компиляторами упомянутыми выше.)
///
/// Недостаки(TODO):
///     - строка операторов должна парситься как функция.
///     - нельзя: 3--4, а должно быть можно.
///     - ...
///----------------------------------------------------------------------------:

#define deb(v) std::cout << #v << " = " << v << "\n";
#define ENDL   std::cout << "\n"

///----------------------------------------------------------------------------|
/// Контейнер для сбора ошибок.
///     Философия калькулятора:
///         позволяет сделать вычисления
///         при наличие НЕ критических ошибок ввода.
///         Но калькулятор обязан предупредить юзверя.
///----------------------------------------------------------------------------:
struct sControl_errors
{
    void info()
    {
        if (errors.empty() && warnings.empty()) return;

        std::wcout << L"\n";
        for (size_t i = 0; i < errors.size(); i++)
        {
            std::wcout << L"ERROR  : " << errors[i] << L"\n";
        }
        for (size_t i = 0; i < warnings.size(); i++)
        {
            std::wcout << L"WARNING: " << warnings[i] << L"\n";
        }

        if (!errors.empty() || !warnings.empty()) std::wcout << L"\n";
    }

    void push_error(std::wstring  mess)
    {
        errors.push_back(mess);
    }
    void push_warning(std::wstring  mess)
    {
        warnings.push_back(mess);
    }
    bool is_error()
    {
        return !errors.empty();
    }
    void reset()
    {
        errors.clear();
        warnings.clear();
    }

private:
    std::vector<std::wstring> warnings;
    std::vector<std::wstring> errors;
}control_errors;

///----------------------------------------------------------------------------|
/// Класс для хранения лексем.
///----------------------------------------------------------------------------:
struct sAtom
{
    enum E
    {
        XXX = '@',
        NUM = 255,
        ADD = '+',
        SUB = '-',
        MUL = '*',
        DIV = '/',
        POW = '^', /// pow(x, y)
        FNC = 'F', /// Зарезервированно за функциями, например sin, cos и т.д..
        BRA = '(',
        BRZ = ')'
    };
    sAtom(E t) : type(t), active(true), number(666.666)
    {
        if (t != NUM)
        {
            s += char(t);
            if ((t == BRA) || (t == BRZ))
            {
                active = false;
            }
        }
    }

    std::string s;
    E        type;
    size_t      n; /// Приоритет.
    bool   active;

    double number;
    void convert_str_to_double(const char* _s, size_t& i)
    {
        char* ptrEnd;
        number = strtod(_s, &ptrEnd);
        s = toString(number);
        i += ptrEnd - _s;
    }

    template <typename T>
    std::string toString(T val)
    {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    }
};

///----------------------------------------------------------------------------|
/// Таблица приоритетов для операций.
///----------------------------------------------------------------------------:
size_t  priority_table[256];
void set_priority_table()
{
    priority_table[sAtom::NUM] = 255;
    priority_table[sAtom::POW] = 1;
    priority_table[sAtom::FNC] = 1;
    priority_table[sAtom::MUL] = 2;
    priority_table[sAtom::DIV] = 2;
    priority_table[sAtom::ADD] = 3;
    priority_table[sAtom::SUB] = 3;
}

///----------------------------------------------------------------------------|
/// Нарезалка строки на осмысленные фрагменты.
///----------------------------------------------------------------------------:
class sAnalyzer_base
{   ///-------------------------------|
    /// Контроль скобок на четность.  |
    ///-------------------------------:
    struct sControl_brackets
    {
        sControl_brackets() : count(0) {}
        void operator++(int) { count++; }
        void operator--(int) { count--; }
        bool is_error()
        {
            if (count) control_errors.push_error(L"control_brackets!");
            return count;
        }
    private:
        int count;
    }control_brackets;

    std::vector<sAtom> a;
public:
    sAnalyzer_base(std::string& s)
    {
        control_errors.reset();
        if (s.empty())
        {
            control_errors.push_error(L"[sAnalyzer_base]:Пустая строка!");
            control_errors.info();
            return;
        }

        ///------------------------------------|
        /// Чтобы не гадать как там локаль     |
        /// решила точки или запятая в double  |
        ///------------------------------------:
        if (atof("1,5") != 3 / 2)
        {   //deb("conv")
            for (size_t i = 0; i < s.size(); i++)
            {
                if (s[i] == '.') s[i] = ',';
            }
        }

        clear_space(s);
        parse(s);

        if (control_brackets.is_error())
        {
            a.clear();
        }
        else
        {
            set_priority();
            make_check();
        }
        control_errors.info();
        //info_debugging     ();
    }
    std::vector<sAtom>& result()
    {
        return a;
    }

private:
    bool is_digit(std::string& s, size_t i)
    {
        if (s[i] == '.')
        {
            s[i] = ',';
            return true;
        }   return isdigit(s[i]) || s[i] == ',';
    }
    bool parse(std::string& s)
    {
        for (size_t i = 0; i < s.size(); i++)
        {
            if (is_digit(s, i))
            {
                a.push_back(sAtom(sAtom::NUM));
                a.back().convert_str_to_double(s.c_str() + i, i);
                //deb(s.c_str()+i)
            }
            if (i > s.size() - 1) break;
            //deb(s[i]);
            switch (s[i])
            {
            case sAtom::ADD:
            {
                a.push_back(sAtom(sAtom::ADD));
                break;
            }
            case sAtom::SUB:
            {
                a.push_back(sAtom(sAtom::SUB));
                break;
            }
            case sAtom::MUL:
            {
                a.push_back(sAtom(sAtom::MUL));
                break;
            }
            case sAtom::DIV:
            {
                a.push_back(sAtom(sAtom::DIV));
                break;
            }
            case sAtom::POW:
            {
                a.push_back(sAtom(sAtom::POW));
                break;
            }
            case sAtom::BRA:
            {
                control_brackets++;
                a.push_back(sAtom(sAtom::BRA));
                break;
            }
            case sAtom::BRZ:
            {
                control_brackets--;
                a.push_back(sAtom(sAtom::BRZ));
                break;
            }
            default:
            {
                if (parse_foo(s, i)) break;
                std::wstring war = L"Недопустимый символ '";
                war += s[i];
                war += L"' был проигнорирован!";
                control_errors.push_warning(war);
            }
            }
        }
        return true; /// Успех.
    }

private:
    bool parse_foo(std::string& s, size_t& i)
    {
        if (!isalpha(s[i])) return false;

        std::string func_name;
        for (; isalpha(s[i]); i++) /// <cctype>
        {
            func_name += isupper(s[i]) ? tolower(s[i]) : s[i];
        }
        const char* table[] =
        { "sin", "cos"
        };
        bool ret = false;
        for (size_t j = 0; j < sizeof(table) / sizeof(*table); j++)
        {
            if (table[j] == func_name)
            {
                a.push_back(sAtom(sAtom::FNC));
                a.back().s = func_name;
                ret = true;
                break;
            }
        }

        if (!ret)
        {
            std::wstring ws(func_name.begin(), func_name.end());
            std::wstring war = L"Операция для термина \"";
            war += ws
                + L"\" не определена!";
            control_errors.push_warning(war);
        }
        i--;
        return true;
    }

public:
    void info_debugging()
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            if (a[i].type == sAtom::NUM)
                std::wcout << L"Число   : " << a[i].number;
            else
            {
                std::wcout << L"Операция: ";
                std::cout << a[i].s;
            }

            if (a[i].n != 255) std::wcout << L" \tприоритет операции: " << a[i].n;
            std::wcout << L"\n";
        }   std::wcout << L"\n";
    }

private:
    ///------------------------------------|
    /// Очищаем строку от пробелов.        |
    ///------------------------------------:
    void clear_space(std::string& s)
    {
        size_t j = 0, i;
        for (i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                s[j++] = s[i];
            }
        }
        if (j != i)
        {
            std::wcout << L"MESSAGE: "
                << i - j << L" пробел(ов) было удаленно.\n";
            s.resize(j);
        }
        //std::wcout << L"Количество символов в строке ввода: "<< s.size()<< "\n";
    }

    void set_priority()
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            a[i].n = priority_table[a[i].type];
        }
    }

    void make_check()
    {
        minus_to_plus();
        if ((a[0].type != sAtom::NUM) &&
            (a[0].type != sAtom::FNC))     a[0].active = false;

        if (a.back().type != sAtom::NUM) a.back().active = false;
    }
    void minus_to_plus()
    {
        for (size_t i = 0; i < a.size() - 1; i++)
        {
            if ((a[i].type == sAtom::SUB) && (a[i + 1].type == sAtom::NUM))
            {
                a[i].type = sAtom::ADD;
                a[i + 1].number = -a[i + 1].number;
            }
        }
    }
};
///------------------------------------|
/// Тест класса sAnalyzer_base.        |
///------------------------------------:
void testclass_sAnalyzer_base()
{
    std::string str = "  1 + 22 /333   * 4444 -55555  ";
    std::wcout << L"TECT analyzer.parse(str)\n"
        << L" ... входная строка: ";
    std::cout << str << L"\n\n";
    sAnalyzer_base analyzer(str);
    analyzer.info_debugging();
    std::wcin.get();
}

///----------------------------------------------------------------------------|
/// Калькулятор.
///----------------------------------------------------------------------------:
struct sCalculator
{
    std::vector<sAtom>& a;
    double          total;

    sCalculator(std::vector<sAtom>& _a) : a(_a), total(0.)
    {
        if (a.empty())
        {
            std::wcout << L"... fail ...\n";
            return;
        }
        size_t i = 0;   order_expert(i);
        go(a);////////////////////////////////////////
        info(a);
    }

private:
    void go(std::vector<sAtom>& b)
    {
        std::wcout << L"Порядок операций: ";
        size_t& o = order[0];
        for (size_t i = 0; i < order.size(); i++)
        {
            o = order[i];

            if (char(b[o + 1].number < 0) && (b[o].type == sAtom::ADD))
                std::wcout << '-';
            else std::wcout << char(b[o].type);

            switch (b[order[i]].type)
            {
            case sAtom::ADD:
            {
                b[get_L(o)].number += b[get_R(o)].number;
                boomm(get_L(o), get_R(o));
                break;
            }
            case sAtom::SUB:
            {
                b[get_L(o)].number -= b[get_R(o)].number;
                boomm(get_L(o), get_R(o));
                break;
            }
            case sAtom::MUL:
            {
                b[get_L(o)].number *= b[get_R(o)].number;
                boomm(get_L(o), get_R(o));
                break;
            }
            case sAtom::DIV:
            {
                b[get_L(o)].number /= b[get_R(o)].number;
                boomm(get_L(o), get_R(o));
                break;
            }
            case sAtom::POW:
            {
                b[get_L(o)].number = pow(b[get_L(o)].number,
                    b[get_R(o)].number);
                boomm(get_L(o), get_R(o));
                break;
            }
            case sAtom::FNC:
            {
                if (b[o].s == "sin")
                {
                    b[o].number = sin(b[get_R(o)].number);//////////////-sin
                    boomm(o, get_R(o));
                }
                else if (b[o].s == "cos")
                {
                    b[o].number = cos(b[get_R(o)].number);//////////////-cos
                    boomm(o, get_R(o));
                }
                break;
            }
            default:
            {
                std::wcout << L"Операция для \""
                    << char(b[order[i]].type)
                    << L"\" отсутствует!\n";
            }
            }
        }
        std::wcout << L"\n";
        total = b[o].number;
    }

    void info(std::vector<sAtom>& _a)
    {
        for (size_t i = 0; i < _a.size(); i++)
        {
            std::cout << _a[i].s << " ";
        }   std::wcout << L" = ?\nРезультат: " << total << "\n";
    }

    size_t get_L(size_t i)
    {
        size_t t = i;
        while (--i + 1 > 0)
        {
            if (a[i].type == sAtom::NUM)
            {
                return i;
            }
        }
        std::wcout << L"ERROR:[get_L] Левый операнд отсутствует.\n";
        return t;
    }

    size_t get_R(size_t i)
    {
        size_t t = i;
        while (++i < a.size())
        {
            if (a[i].type == sAtom::NUM)
            {
                return i;
            }
        }
        std::wcout << L"ERROR:[get_R] Правый операнд отсутствует.\n";
        return t;
    }

    ///------------------------------------|
    /// Волна: на границе тока актуалы!    |
    ///------------------------------------:
    void boom(const size_t k, double n)
    {
        a[k].active = false;
        a[k - 1].active = false;
        for (size_t i = k; !a[i].active && (i + 1 > 0); i--)
        {
            a[i].number = n;
        }

        a[k + 1].active = false;
        for (size_t i = k; !a[i].active && i < a.size(); i++)
        {
            a[i].number = n;
        }
    }
    void boomm(const size_t l, const size_t r)
    {
        for (size_t i = l; i <= r; i++)
        {
            a[i].number = a[l].number;
            a[i].active = false;
        }
        boom(l + 1, a[l].number);
    }

    typedef std::vector<size_t> cargo_op_t;
    cargo_op_t order;

    ///------------------------------------|
    /// Растановка приоритетов.            |
    ///------------------------------------:
    void order_expert(size_t& i)
    {
        cargo_op_t tmp;

        for (; i < a.size(); i++)
        {
            if ((a[i].n != 255) && a[i].active)
            {
                tmp.push_back(i);
            }
            else if (a[i].type == sAtom::BRA)
            {
                order_expert(++i);
            }
            else if (a[i].type == sAtom::BRZ)
            {
                push_order(tmp);
                return;
            }
        }
        push_order(tmp);
        //info_order_debugging();
    }

    void push_order(cargo_op_t& o)
    {
        sort(o);
        for (size_t i = 0; i < o.size(); i++)
        {
            order.push_back(o[i]);
        }
    }

    ///------------------------------------|
    /// Сортируем по приоритетам.          |
    /// (наш любимый пузырЁк! :)           |
    ///------------------------------------:
    void sort(std::vector<size_t>& o)
    {
        if (o.empty()) return;
        for (size_t i = 0; i < o.size() - 1; i++)
        {
            bool b = true;
            for (size_t j = i; j < o.size() - 1; j++)
            {
                if (a[o[j]].n > a[o[j + 1]].n)
                {
                    std::swap(o[j], o[j + 1]);
                    b = false;
                }
            }   if (b)  break;
        }
    }

    void info_order_debugging()
    {
        for (size_t i = 0; i < order.size(); i++)
        {
            deb(a[order[i]].s)
        }
    }
};

///----------------------------------------------------------------------------|
/// Тест класса sCalculator.                                                   |
///----------------------------------------------------------------------------:
#define CALC        std::wcout << L"Тест ---------------: " << count++ << "\n";\
                    std::wcout << L" ... входная строка: ";                    \
                    std::cout  << str << "\n";                                 \
                    sAnalyzer_base analyzer(str);                              \
                    sCalculator calc(analyzer.result());
#define TEST(v) {   std::string str = #v;  int x=1;  x--;                      \
                    CALC                                                       \
                    if(calc.total !=(v)){   std::wcout << L"Тест провален! ("; \
                                            std::cout  << (v) << ")\a\n";}     \
                    else                    std::wcout << L"Успех!\n";         \
                    ENDL;                                                      \
                }
#define TEST_ERR(v) {std::string str =  v; CALC std::cout << "\n";}
#define TEST_USER(v){std::string str = #v; CALC std::cout << "\n";}

void testclass_sCalculator()
{
    int count = 1;

    std::wcout << L"TECT (авто-валидатор) sCalculator--------------------:\n\n";
    TEST(2.24 + 2.3 * 3.46)
        TEST(2 + 2 * 3 / 2)
        TEST(2 + 2 * 3 / 2 + 10 - 4)
        TEST(1 + 3. * 3. / 2. * 4.)
        TEST(-6 * 7)
        TEST(-6 * 7 + x)
        TEST(2 + 3. / 2 - 5. / 5 + 5. * 2. / 4.)
        TEST(3 + (1 + 3) * 2)
        TEST(2 * (7 + (3 - 1)) + ((1 + 3) - 7) * 2)
        TEST(((2 + 3)) * 2)
        TEST((2) + (2) * 3)

        std::wcout << L"TECT (function)--------------------------------------:\n\n";
    TEST(2 + sin(2.5) * 3)
        TEST_USER(2 + Sin(2.5) * 3)

        TEST_USER(2 * (Sin(((3.14e-2 + 2) / 2)) ^ 2 + 2.7) + Cos(3.14 / (2 - 6.1e+3)) ^ 2)
        deb(2 * (pow(sin(((3.14e-2 + 2) / 2)), 2) + 2.7) + pow(cos(3.14 / (2 - 6.1e+3)), 2))
        ENDL;

    std::wcout << L"TECT (отлова ОШИБОК ввода)---------------------------:\n\n";
    TEST_ERR("((2+3)))*2")

        std::wcout << L"TECT (Отладка)---------------------------------------:\n\n";

    std::wcout << L"TECT sCalculator ЗАВЕРШЕН!\n\n";
    std::wcout << L"... жми ENTER для ручного ввода строки...\n\n";
    std::wcin.get();
}

double getdouble(const char* s, size_t& i)
{
    char* ptrEnd;
    double  d = strtod(s, &ptrEnd);
    i += ptrEnd - s;
    return d;
}
void nano_test()
{
    std::string s = "xxx-1.23E-3+asd";

    if (atof("1,5") != 3 / 2)
    {
        deb("conv")
            for (size_t i = 0; i < s.size(); i++)
            {
                if (s[i] == '.') s[i] = ',';
            }
    }

    size_t      i = 3;
    double      d = getdouble(s.c_str() + i, i);

    deb(d)
        deb(i)
        deb(s.c_str() + i)
        std::wcin.get();
}

//#include <windows.h>
void rus_test()
{   // -finput-charset=CP1251 -fexec-charset=CP866
    const wchar_t* aa = L"ячсфывйцуку\n";
    std::wcout << aa << L"Русский текст в консоли\n";

    while (true)
    {
        std::string  s; std::wcout << L"\ncout: "; std::cin >> s; std::cout << s;
        std::wstring z; std::wcout << L"\nwcout"; std::wcin >> z; std::wcout << z;
    }
}

///----------------------------------------------------------------------------|
/// main
///----------------------------------------------------------------------------:
int main()
{
    setlocale(0, "");

    //nano_test();
    //rus_test ();

    set_priority_table();
    //testclass_sAnalyzer_base();
    testclass_sCalculator();

    std::wcout << L"Основные операции: \"+-*/\"\n"
        << L"добавленно       : степень числа x^y\n\n";

    while (true)
    {
        std::string str;
        std::cout << L"Enter the expression: "; getline(std::cin, str);

        sAnalyzer_base analyzer(str);
        sCalculator(analyzer.result());
    }
}
