#include "answer08.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

List * List_createNode(const char * str) {
	List * Node = malloc( sizeof(List) );
	Node->str = strdup(str);
	Node->next = NULL;
	return Node;
}

void List_destroy(List * list) {
	List * head = list;
	List * next = NULL;
	while (head != NULL) {
		next = head->next;
		free(head->str);
		head->next = NULL;
		free(head->next);
		free(head);
		head = next;
	}	
}
	
int List_length(List * list) {
	int len = 0;
	List * ptr = list;
	while (ptr != NULL){
		ptr = ptr ->next;
		len ++;
	}
	return len;
}

List * List_merge(List * lhs, 
		  List * rhs, 
		  int (*compar)(const char *, const char*)) {
	//return null if both lhs and rhs are null
	if (lhs == NULL && rhs == NULL) return NULL;
	List * current = NULL;
	List * head = NULL;
	//both non-null?
	//initialize head & current = lhs if lhs is not null
	if (lhs != NULL && rhs == NULL) return lhs;
	//initialize head & current = rhs if rhs is not null
	if (rhs != NULL && lhs == NULL) return rhs;
	//otherwise go to while loop to initialize head & current
	while (lhs != NULL && rhs != NULL) {
		if (compar(rhs->str, lhs->str) > 0) {
			//initialize head & current = lhs
			if (current == NULL) {
				current = lhs;
				head = current;
			}
			else {
				current->next = lhs; 
				current = current->next;
			}
			lhs = lhs->next;
		}
		else {
			//initialize head & current = rhs
			if (current == NULL) {
				current = rhs;
				head = current;
			}
			else {
				current->next = rhs; 
				current = current->next;
			}
			rhs = rhs->next;
		}
	}
	if (lhs == NULL) current->next = rhs;
	else {current->next = lhs; }
	return head;
}

List * List_sort(List * list, int (*compar)(const char *, const char*)) {

	if (List_length(list) == 0 || List_length(list) == 1) {
		return list;
	}
	else {
		List * lhs = list;
		List * rhs = list;
		List * tmp = NULL;
		int i = 0;
		//generate the lhs list
		while (i < List_length(list)/2 -1) {
			rhs = rhs-> next;
			i++;
		}
		//generate the rhs list
		tmp = rhs->next;
		rhs->next = NULL;
		rhs = tmp;
		//sort list
		lhs = List_sort(lhs, compar);
		rhs = List_sort(rhs, compar);
		list = List_merge(lhs, rhs, compar);
	}
	return list;
}
/*
int compar(const char * a, const char* b) {
	if (a>b) return 0;
	else return 1;
}
*/