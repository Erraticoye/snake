#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
	setlocale(LC_CTYPE, "");
	wchar_t char1 = L'\u23BE';
	wprintf(L"%lc\n", char1);
}