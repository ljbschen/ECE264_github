#include "answer09.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

char * * explode(const char * str, const char delims);
void destroyStringArray(char * * strArr, int len);

BusinessNode *
create_node(char * stars, char * name, char * address) {
	BusinessNode *Bnode = malloc( sizeof (BusinessNode));
	Bnode->stars = stars;
	Bnode->name = name;
	Bnode->address = address;
	Bnode->left = NULL;
	Bnode->right = NULL;
	return Bnode;
}

BusinessNode *
tree_insert(BusinessNode * node, BusinessNode * root) {
	//if node is null
	if (node == NULL) return root;
	//if node is not null and root is null
	if (root == NULL && node != NULL) return node;
	//if node is not null and root is not null
	BusinessNode * tmp = root;
	//insert left
	if (strcmp(node->name, root->name) <= 0) {
		if (root->left == NULL) {
			root->left = node;
			return root;
		}
		else {
			root = root->left;
			tree_insert(node, root);
		}
	}
	//insert right
	else {
		if (root->right == NULL) {
			root->right = node;
			return root;
		}
		else {
			root = root->right;
			tree_insert(node, root);
		}
	}
	return tmp;
}

BusinessNode *
load_tree_from_file(char * filename) {
	FILE *fp = NULL;
	char line[200];
	char **strArr;

	BusinessNode * root = NULL;
	BusinessNode * newnode = NULL;
	//open file
	fp = fopen(filename, "rb");
	if(!fp) {
	   	fprintf(stderr, "Failed to open file '%s'\n", filename);
	   	return NULL;
	}
	//read line by line
	while (fgets(line, 200, fp) != NULL) {
		//stars, name, address
		strArr = explode(line, '\t');
		newnode = create_node(strdup(strArr[0]), strdup(strArr[1]), strdup(strArr[2]));
		//free the ptr
		destroyStringArray(strArr, 3);
		//insert node
		root = tree_insert(newnode, root);
	}
	fclose(fp);
	return root;
}

BusinessNode *
tree_search_name(char * name, BusinessNode * root) {
	if (name == NULL || root == NULL) return NULL;
	if (strcmp(name, root->name) < 0) {
		return tree_search_name(name, root->left);
	}
	if (strcmp(name, root->name) > 0) {
		return tree_search_name(name, root->right);
	}
	return root;
}

void
print_node(BusinessNode * node) {
	/* Country Cafe
	 * ============
	 * Stars:
	 *    3.5
	 * Address:
	 *    1030 Emerald Ter, Sun Prairie, WI 53590
	 */
	 printf("%s", node->name);
	 printf("==========================\n");
	 printf("Star:");
	 printf("     %s", node->stars);
	 printf("Address:");
	 printf("        %s\n", node->address);
}

void
print_tree(BusinessNode * tree) {
	BusinessNode * tmp = tree;
	while (tmp != NULL) {
		print_node(tmp);
		print_node(tmp->left);
		print_node(tmp->right);
	}
}

void
destroy_tree(BusinessNode * root) {
	if (root == NULL) return ;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root->name);
	free(root->stars);
	free(root->address);
	free(root);
}

char * * explode(const char * str, const char delims) {
    //find out how many delims in the str
    int N = 0;
    int i;
    int len = 0;
    if (str == NULL) return NULL;
    else len = strlen(str);

    for (i = 0; i < len; i ++) {
        if (delims == str[i]) N++;
    }
    // Create the return array
    char * * strArr = malloc((N + 1) * sizeof(char *));
   	
    //then strcpy into different location
    //create two indicies: last and ind
    //last traces the position of last observed delim and ind traces the current char in str

    int last = -1;
    //go through all chars in str and if it is a delim :
    //1. create a string for the char from last to ind
    //2. set last to current ind
    for (i = 0; i < len; i++){
        if (delims == str[i]) {
            *strArr = (char *)malloc(i - last);
            strncpy(*strArr, str + last + 1, i - last - 1);
            (*strArr)[i - last - 1] = '\0';
            strArr++;
            last = i;   
        }
    }
    //add the last string
    *strArr = (char *) malloc (len - last);
    strncpy(*strArr, str + last + 1, len - last -1);
    (*strArr)[len - last - 1] = '\0';
    
    //restore strArr to the first cell of array
    strArr = strArr - N;
    return strArr;
}

void destroyStringArray(char * * strArr, int len){
    int i;
    for (i = 0; i < len; i ++){
        free(*(strArr++));
    }
    free(strArr - len);
}