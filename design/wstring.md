**ktd::wstring**

*What:*

```std::wstring``` like string manipulation in windows kernel.

*Interfaces:*

```
ktd::wstring str = L"Hello World";
ktd::wstgin anotherstr(L"Hello World");

str = anotherstr;
auto Length = str.length();

str.push_back(L'k');
str.append(anotherstr);

str.find(anotherstr);

str == anotherstr;

const wchar_t *internal = str.c_str();
```
