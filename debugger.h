#include <bits/stdc++.h>

using namespace std;

#define db(...) __internal_multi_debug(0, false, #__VA_ARGS__, __VA_ARGS__)
#define dbl(...) __internal_multi_debug(0, true, #__VA_ARGS__, __VA_ARGS__)
#define dbg(...) cout << __internal_set_variable_name(#__VA_ARGS__) << __internal_function_debug(__VA_ARGS__) << "\n";

bool __internal_is_not_primitive_data = false;
bool __internal_in_debug = false;
int __internal_depth = 0;
vector<string> __internal_direction_path;
string __internal_debug_response;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(char c)
{
    string s;
    s += c;
    return "'" + s + "'";
}

string to_string(string s)
{
    return '"' + s + '"';
}

string to_string(const char* s)
{
    return to_string((string)s);
}

string to_string(bool b)
{
    return (b ? "true" : "false");
}

template <typename A>
string to_string(complex<A> c)
{
    pair<A,A> p = {c.real(), c.imag()};
    return to_string(p);
}

string to_string(vector<bool> v)
{
    if(__internal_depth <= 0 && __internal_in_debug)
    {
        __internal_in_debug = false;
        __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v) + "\n";
        __internal_in_debug = true;
        return "";
    }
    bool first = true;
    string res = "{";
    int cont = 0;
    for(int i = 0 ; i < static_cast<int>(v.size()) ; i++)
    {
        if(!first)
        {
            res += ", ";
        }
        first = false;
        string temp = __internal_direction_path.back();
        __internal_depth--;
        __internal_direction_path.back() += "[" + to_string(cont) + "]";
        __internal_is_not_primitive_data = false;
        res += to_string(v[i]);
        __internal_depth++;
        if(!__internal_is_not_primitive_data && __internal_in_debug)
        {
            __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v[i]) + "\n";
        }
        __internal_direction_path.back() = temp;
        cont++;
    }
    res += "}";
    __internal_is_not_primitive_data = true;
    return res;
}

template <size_t N>
string to_string(bitset<N> v)
{
    string res = "";
    for(size_t i = 0 ; i < N ; i++)
    {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v)
{
    if(__internal_depth <= 0 && __internal_in_debug)
    {
        __internal_in_debug = false;
        __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v) + "\n";
        __internal_in_debug = true;
        return "";
    }
    bool first = true;
    string res = "{";
    int cont = 0;
    for(auto &x : v)
    {
        if(!first)
        {
            res += ", ";
        }
        first = false;
        string temp = __internal_direction_path.back();
        __internal_depth--;
        __internal_direction_path.back() += "[" + to_string(cont) + "]";
        __internal_is_not_primitive_data = false;
        res += to_string(x);
        __internal_depth++;
        if(!__internal_is_not_primitive_data && __internal_in_debug)
        {
            __internal_debug_response += __internal_direction_path.back() + ": " + to_string(x) + "\n";
        }
        __internal_direction_path.back() = temp;
        cont++;
    }
    res += "}";
    __internal_is_not_primitive_data = true;
    return res;
}

template <typename A>
string to_string(stack<A> s)
{
    vector<A> v;
    while(!s.empty())
    {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(),v.end());
    return to_string(v);
}

template <typename A>
string to_string(queue<A> q)
{
    vector<A> v;
    while(!q.empty())
    {
        v.push_back(q.front());
        q.pop();
    }
    return to_string(v);
}

template <typename A>
string to_string(priority_queue<A> pq)
{
    vector<A> v;
    while(!pq.empty())
    {
        v.push_back(pq.top());
        pq.pop();
    }
    return to_string(v);
}

vector<string> parsing(string cad)
{
    vector<string> vect;

    int level = 0;
    bool inexpress1 = false;
    bool inexpress2 = false;

    function<void(string&)> delallspace = [&](string &cad)
    {
        string temp;

        for(int i = 0 ; i < cad.size() ; i++)
        {
            if(cad[i] == ' ')continue;
            temp += cad[i];
        }

        cad = temp;
    };

    function<void(string&)> delspace = [&](string &cad)
    {
        while(cad.size() && cad.back() == ' ')cad.pop_back();

        reverse(cad.begin(), cad.end());

        while(cad.size() && cad.back() == ' ')cad.pop_back();

        reverse(cad.begin(), cad.end());
    };

    function<bool(char)> isopen = [&](char c)
    {
        if(c == '(')return true;
        if(c == '{')return true;
        if(c == '[')return true;
        if(c == '<')return true;
        return false;
    };

    function<bool(char)> isclose = [&](char c)
    {
        if(c == ')')return true;
        if(c == '}')return true;
        if(c == ']')return true;
        if(c == '>')return true;
        return false;
    };

    string temp;

    for(int i = 0 ; i < cad.size() ; i++)
    {
        temp += cad[i];
        if(!inexpress1 && !inexpress2)
        {
            if(isopen(cad[i]))level++;
            else if(isclose(cad[i]))level--;
            else if(cad[i] == '\"')inexpress1 = true;
            else if(cad[i] == '\'')inexpress2 = true;
            else if(level == 0 && cad[i] == ',')
            {
                temp.pop_back();
                vect.push_back(temp);
                temp.clear();
            }
        }
        else
        {
            if(inexpress1 && cad[i] == '\"' && cad[i-1] != '\\')inexpress1 = false;
            else if(inexpress2 && cad[i] == '\'' && cad[i-1] != '\\')inexpress2 = false;
        }
    }

    vect.push_back(temp);
    temp.clear();

    for(int i = 0 ; i < vect.size() ; i++)
    {
        delspace(vect[i]);
    }

    return vect;
}

string __internal_set_variable_name()
{
    return "";
}

string __internal_set_variable_name(string cad)
{
    vector<string> vect = parsing(cad);

    cad = vect[0];
    
    __internal_direction_path.push_back(cad);
    return "";
}

string __internal_set_depth()
{
    __internal_depth = 0;
    return "";
}

string __internal_set_depth(int n)
{
    __internal_depth = n;
    return "";
}

string __internal_function_debug()
{
    return "\n";
}

template <typename A, typename... Args>
string __internal_function_debug(A v, Args... args)
{
    __internal_set_depth(args...);
    __internal_is_not_primitive_data = false;
    string res = to_string(v);
    if(!__internal_is_not_primitive_data)
    {
        string cad = __internal_direction_path.back();
        __internal_direction_path.pop_back();
        return cad + ": " + res + "\n";
    }
    __internal_in_debug = true;
    __internal_debug_response.clear();
    to_string(v);
    __internal_in_debug = false;
    __internal_direction_path.pop_back();
    return __internal_debug_response;
}

void __internal_multi_debug(int it, bool space, string cad)
{
    return;
}

template <typename A, typename... Args>
void __internal_multi_debug(int it, bool space, string cad, A v, Args ... args)
{
    vector<string> vect = parsing(cad);

    cout << __internal_set_variable_name(vect[it]);
    string temp = __internal_function_debug(v);
    if(space)
    {
        if(it+1 != vect.size())temp.pop_back();
        if(it)temp = " , " + temp;
    }
    if(it+1 == vect.size())temp += "\n";
    cout << temp;
    __internal_multi_debug(it+1, space, cad, args...);
    return;
}

template <typename A, typename B>
string to_string(pair<A, B> p)
{
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p)
{
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p)
{
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

