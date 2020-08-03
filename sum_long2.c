#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct result {
	int size, size1, size2;
	char arr1[1002];
	char arr2[1002];
	char sum[1003];
	struct result *p_next;
} result;

void get_sum(result *p) {
	int i = 0, j = 0, k = 0, carry = 0;
	int max = p->size1 >= p->size2 ? p->size1 : p->size2;
	if (max == p->size1) {
		for (i = 0, j = p->size1 - 1, k = p->size2 - 1;\
			   	i <= max - 1; i++, j--) {
			if (k >= 0) {
				p->sum[i] = p->arr1[j] - '0' + \
							p->arr2[k] - '0' + carry + '0';
				if (p->sum[i] > '9') {
					p->sum[i] -= 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				k--;
			}
			else {
				p->sum[i] = p->arr1[j] + carry;
				if (p->sum[i] > '9') {
					p->sum[i] -= 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
			}
		}
	}
	else {
		for (i = 0, j = p->size1 - 1, k = p->size2 - 1;\
			   	i <= max - 1; i++, k--) {
			if (j >= 0) {
				p->sum[i] = p->arr1[j] - '0' + \
							p->arr2[k] - '0' + carry + '0';
				if (p->sum[i] > '9') {
					p->sum[i] -= 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				j--;
			}
			else {
				p->sum[i] = p->arr2[k] + carry;
				if (p->sum[i] > '9') {
					p->sum[i] -= 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
			}
		}
	}
	if (carry == 1) {
		p->sum[i] = '1';
		p->size = i + 1;
		return ;
	}
	p->size = i;
	return ;
}
void add_link(result **pp_lk, const result *p_node) {
	result *p_last = NULL;
	if (!*pp_lk) {
		*pp_lk = (result *)p_node;
		return ;
	}
	for (p_last = *pp_lk; p_last->p_next != NULL; p_last = p_last->p_next) {}
	p_last->p_next = (result *)p_node;
	return ;
}
void print_sum(const char *p_arr, int size) {
	for (size = size - 1; size >= 0; size-- ) {
		printf("%c", p_arr[size]);
	}
	return ;
}
void print_arr(const char *p_arr, int size) {
	int i = 0;
	for ( ; i <= size - 1; i++) {
		printf("%c", p_arr[i]);
	}
	return ;
}
void print_link(const result *p_link) {
	int cnt = 1;
	const result *p_tmp = p_link;
	for ( ; p_tmp != NULL; p_tmp = p_tmp->p_next) {
		printf("\n");
		printf("case %d: \n", cnt);
		print_arr(p_tmp->arr1, p_tmp->size1);
		printf(" + ");
		print_arr(p_tmp->arr2, p_tmp->size2);
		printf(" = ");
		print_sum(p_tmp->sum, p_tmp->size);
		printf("\n");
		cnt++;
	}
	return ;
}
int get_arr(char *p_arr, char **p_base) {
	int cnt = 0;
	char *p_tmp = NULL;
	for ( ; **p_base < '0' || **p_base > '9'; (*p_base)++) {}
	for (p_tmp = *p_base; *p_tmp >= '0' && *p_tmp <= '9'; p_tmp++) {
		p_arr[cnt] = *p_tmp;
		cnt++;
	}
	*p_base = p_tmp;
	return cnt;
}
int main(void) {
	char *p_base = NULL;
	result *p_node = NULL;
	result *p_link = NULL;
	char choice[10] = {0};
	char buf[2010] = {0};
	while (1) {
		p_node = (result *)malloc(sizeof(result));
		memset(p_node->arr1, 0, sizeof(p_node->arr1));
		memset(p_node->arr2, 0, sizeof(p_node->arr2));
		memset(p_node->sum, 0, sizeof(p_node->sum));
		p_node->p_next = NULL;
		printf("enter two numbers which you want to calculate the sum (separate with space key): \n");
		fgets(buf, 2010, stdin);
		p_base = buf;
		p_node->size1 = get_arr(p_node->arr1, &p_base);
		p_node->size2 = get_arr(p_node->arr2, &p_base);
		get_sum(p_node);
		add_link(&p_link, p_node);
		printf("enter any key to continue, or 'q' to quit: ");
		fgets(choice, 10, stdin);
		if (*choice == 'q') {
			break;
		}
		memset(buf, 0, sizeof(buf));
	}
	printf("The result is as shown below: \n");
	print_link(p_link);
	return 0;
}
