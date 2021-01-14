#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

/* prints first "length" characters of a char* given as parameter */
static int write_stdout(const char *token, int length) {
	int rc;
	int bytes_written = 0;
	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

/* auxiliary function to print reverse of number */
void auxiliary_print(long int inv, int nr_zeros) {
	while (inv) {
		char el = inv % 10 + '0';
		write_stdout(&el, 1);
		inv /= 10;
	}
	while (nr_zeros) {
		char el = '0';
		write_stdout(&el, 1);
		nr_zeros--;
	}
}

/* prints value of type "int" */
int print_int(long int nr) {
	int size = 0, nr_zeros = 0;
	long int inv = 0;
	//negative
	if (nr < 0) {
		nr *= -1;
		size += write_stdout("-", 1);
	}
	//reverse number
	while (nr) {
		//number of zeros at the end
		if (nr % 10 == 0 && !inv) nr_zeros++;
		size++;
		inv = inv * 10 + nr % 10;
		nr /= 10;
	}
	//print with auxiliary function
	auxiliary_print(inv, nr_zeros);
	return size;
}

/* prints value of type "unsigned int" */
int print_unsigint(unsigned int nr) {
	int size = 0, nr_zeros = 0;
	long int inv = 0;
	//reverse number
	while (nr) {
		if (nr % 10 == 0 && !inv) nr_zeros++;
		size++;
		inv = inv * 10 + nr % 10;
		nr /= 10;
	}
	//print with auxiliary function
	auxiliary_print(inv, nr_zeros);
	return size;
}

/* reverse a string given as parameter */
char* reverse(char *str, int len) {
	int i;
	char aux;
	//reverse the 2 halves of string
	for (i = 0; i < len/2; i++) {
		aux = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = aux;
	}
	return str;
}

/* prints value of type "int" in hexadecimal format */
int print_hexa(int nr) {
	//values array
	char arr[] = "0123456789abcdef";
	int size = 0;
	char *res = malloc(SIZE);
	unsigned int n = nr;
	//convert number to base 16
	while (n) {
		res[size++] = arr[n % 16];
		n /= 16;
	}
	//reverse string and print
	write_stdout(reverse(res, size), size);
	return size;
}

/* prints value of type "char" */
int print_char(char s) {
	write_stdout(&s, 1);
	return 1;
}

/* function that mimics the behaviour of the printf function */
int iocla_printf(const char *format, ...) {
	int size = 0, el_int;
	char el_char;
	char *p, *s;

	va_list args;
	va_start(args, format);
	char *copy = malloc(strlen(format) + 1);
	strcpy(copy, format);

	for (p = copy; *p != '\0'; p++) {
		while (*p != '%' && *p != '\0') {
			//print characters except '%'
			size += write_stdout(p, 1);
			p++;
		}
		//if reached end of string then return
		if (*p == '\0' || *p + 1 == '\0') return size;
		p++;
		switch(*p) {
			case 'd' : el_int = va_arg(args, int);
						size += print_int(el_int);
						break;
			case 'u' : el_int = va_arg(args, int);
						size += print_unsigint(el_int);
						break;
			case 'x' : el_int = va_arg(args, int);
						size += print_hexa(el_int);
						break;
			case 'c' : el_char = va_arg(args, int);
						size += print_char(el_char);
						break;
			case 's' : s = va_arg(args, char*);
						size += strlen(s);
						write_stdout(s, strlen(s));
						break;
			case '%' : write_stdout(p, 1);
						size++;
						break;
		}
	}
	va_end(args);

	return size;
}
