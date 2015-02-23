#include "answer09.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BusinessNode *
create_node(char * stars, char * name, char * address) {
	BusinessNode Bnode = malloc(sizeof (BusinessNode));
	Bnode->stars = stars;
	Bnode->name = name;
	Bnode->address = address;
	Bnode->left = NULL;
	Bnode->right = NULL;
}

BusinessNode *
tree_insert(BusinessNode * node, BusinessNode * root) {
	//insert left
	if (strcmp(node->name, root->name) > 0) {
		
	}

	if (root->left == NULL) root->left = node;

	return root;
}

BusinessNode *
load_tree_from_file(char * filename) {

}

BusinessNode *
tree_search_name(char * name, BusinessNode * root) {

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

}

void
destroy_tree(BusinessNode * root) {

}