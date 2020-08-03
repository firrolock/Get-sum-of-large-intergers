#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct result {
	int size, size1, size2;
	int arr1[200];
	int arr2[200];
	int sum[201];
	struct result *p_next;
} result;

int get_power(int num, int cnt) {
	if (cnt == 0) {
		return 1;
	}
	if (cnt == 1) {
		return num;
	}
	return num * get_power(num, cnt - 1);
}
int stoi(int *p_dest, const char *p_base, const char *p_str) {
	int cnt = 0;
	const char *p_tmp = NULL;
	for (p_tmp = p_base; p_tmp >= p_str && p_tmp >= p_base - 8 && *p_tmp >= '0' && *p_tmp <= '9'; p_tmp--) {
		if (p_tmp == p_base) {
			*p_dest = *p_tmp - '0';
		}
		else {
			*p_dest += (*p_tmp - '0') * get_power(10, p_base - p_tmp);
		}
	}
	cnt++;
	if (p_tmp < p_str || *p_tmp < '0' || *p_tmp > '9') {
		return cnt;
	}
	return cnt += stoi(p_dest + 1, p_tmp, p_str);
}
int get_sum(int *p_sum, const int *p_arr1, int size1, const int *p_arr2, int size2) {
	int i = 0, carry = 0;
	int max = size1 >= size2 ? size1 : size2;
	for (i = 0; i <= max - 1; i++) {
		p_sum[i] = p_arr1[i] + p_arr2[i] + carry;
		if (p_sum[i] / 1000000000 > 0) {
			p_sum[i] %= 1000000000;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}
	if (carry == 1) {
		p_sum[i] = 1;
		return i + 1;
	}
	return i;
}
void fill_array(int *p_dest, const int *p_src, int size) {
	int i = 0;
	for (i = 0; i <= size - 1; i++) {
		p_dest[i] = p_src[i];
	}
	return ;
}
void add_link(result **pp_lk, const int *p_sum, int size, const int *p_arr1, int size1, const int *p_arr2, int size2) {
	result *p_tmp = (result *)malloc(sizeof(result));
	result *p_last = NULL;
	p_tmp->p_next = NULL;
	fill_array(p_tmp->sum, p_sum, size);
	p_tmp->size = size;
	fill_array(p_tmp->arr1, p_arr1, size1);
	p_tmp->size1 = size1;
	fill_array(p_tmp->arr2, p_arr2, size2);
	p_tmp->size2 = size2;
	if (!*pp_lk) {
		*pp_lk = p_tmp;
		return ;
	}
	for (p_last = *pp_lk; p_last->p_next != NULL; p_last = p_last->p_next) {}
	p_last->p_next = p_tmp;
	return ;
}
void print_array(const int *p_arr, int size) {
	for (size = size - 1; size >= 0; size-- ) {
		printf("%d", p_arr[size]);
	}
	return ;
}
void print_link(const result *p_link) {
	int cnt = 1;
	const result *p_tmp = p_link;
	for (; p_tmp != NULL; p_tmp = p_tmp->p_next) {
		printf("\n");
		printf("case %d: \n", cnt);
		print_array(p_tmp->arr1, p_tmp->size1);
		printf(" + ");
		print_array(p_tmp->arr2, p_tmp->size2);
		printf(" = ");
		print_array(p_tmp->sum, p_tmp->size);
		printf("\n");
		cnt++;
	}
	return ;
}
int main(void) {
	int size = 0, size1 = 0, size2 = 0;
	char *p_base = NULL, *p_tmp = NULL;
	char choice[10] = {0};
	char buf[2010] = {0};
	int sum[201] = {0};
	int arr1[200] = {0};
	int arr2[200] = {0};
	result *p_link = NULL;
	while (1) {
		p_tmp = buf;
		printf("enter two numbers which you want to calculate the sum (separate with space key): \n");
		fgets(buf, 2010, stdin);
		for (p_base = buf + 1; *p_base >= '0' && *p_base <= '9'; p_base++) {}
		size1 = stoi(arr1, p_base - 1, p_tmp);
		for (p_tmp = p_base; *p_tmp < '0' || *p_tmp > '9'; p_tmp++) {}
		for (p_base = p_tmp + 1; *p_base >= '0' && *p_base <= '9'; p_base++) {}
		size2 = stoi(arr2, p_base - 1, p_tmp);
		size = get_sum(sum, arr1, size1, arr2, size2);
		add_link(&p_link, sum, size, arr1, size1, arr2, size2);
		printf("enter any key to continue, or 'q' to quit: ");
		fgets(choice, 10, stdin);
		if (*choice == 'q') {
			break;
		}
		memset(buf, 0, sizeof(buf));
		memset(arr1, 0, sizeof(arr1));
		memset(arr2, 0, sizeof(arr2));
		memset(sum, 0, sizeof(sum));
	}
	printf("The result is as shown below: \n");
	print_link(p_link);
	return 0;
}
