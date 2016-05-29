#include <stdio.h>
#include <stdlib.h>

struct phse6_node {
        int value;
        struct phse6_node *next;
};

struct secret_node {
        int value;
        struct secret_node *left;
        struct secret_node *right;
};

extern int strings_not_equal(char *input, char *password);

// returns a pointer to the first number of a six-number array
extern int* read_six_numbers(char *input);

extern void explode_bomb();
extern void phase_defused();

static char *phase_1_pass = "This is actually not an entirely terrible idea.";
static int phse5_arr[15] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6};
static int phse6_unordr_lst[9] = {684, 973, 183, 582, 993, 143, 193, 941, 562};

/* Phase 1 reads a string and explodes unless the string matches the 
 * predetermined password string.
 */
void phase_1(char *input)
{
        char *password = phase_1_pass;
        if (strings_not_equal(input, password))
                explode_bomb();
}

/* Phase 2 reads in six numbers and explodes unless the six numbers are
 * in increasing order with a difference of five between 
 * consecutive numbers.
 */
void phase_2(char * input)
{
        int* ptr_to_first = read_six_numbers(input);
        
        for (int *i = ptr_to_first + 1; i != (ptr_to_first + 6); i++) {
                int prev = *(i - 1);

                if (*i != prev + 5)
                        explode_bomb();
        }
}

/* Phase 3 reads in two numbers, the first of which is used to determine
 * the password by use of a switch statement. The bomb explodes if the 
 * value of the second number does not match this password.
 */ 
void phase_3(char * input)
{
        int num1;
        int num2;
        int password = 0;

        if (!(sscanf(input, "%d %d", &num1, &num2) > 1))
                explode_bomb();

        if (num1 > 7) 
                explode_bomb();

        switch (num1) {
                case 0: password = 776;
                break;
                case 1: password = 908;
                break;
                case 2: password = 819;
                break;
                case 3: password = 450;
                break;
                case 4: password = 829;
                break;
                case 5: password = 141;
                break;
                case 6: password = 219;
                break;
                case 7: password = 400;
                break;
        }

        if (num2 != password)
                explode_bomb(); 
}

/* Helper function for Phase 4 which takes in the phase 4 input number, runs
 * a series of calculations, then returns a password try.
 * NOTE: The number of recursions is equal to the input. With each recursion
 *       the password is multiplied by 7, beginning with 1.
 */
int func4(int input)
{
        int password = 1;

        if (input <= 0)
                return password;
        
        input--;

        password = func4(input);
        int temp = (password * 8) - password;
        password = temp;

        return password;
}

/* Phase 4 reads in one number and runs a recursive calculation function, 
 * with the number of recursions equalling the input number. The bomb 
 * explodes if the number calculated by this function does not equal 49.
 */
void phase_4(char *input)
{
        int num;

        if (sscanf(input, "%d", &num) != 1)
                explode_bomb();

        if (num == 0)
                explode_bomb();

        if (func4(num) != 49)
                explode_bomb();
}

/* Phase 5 reads in two numbers, the first of which is used as a starting
 * point within a sequence of numbers. The bomb explodes if the number of
 * steps to get to the number 15 does not equal 9, or if the second input 
 * number does not equal the sum of the numbers stepped along to reach 15
 * (including 15).
 */
void phase_5(char *input)
{
        int num1;
        int num2;

        if (!(sscanf(input, "%d %d", &num1, &num2) > 1))
                explode_bomb();

        num1 = num1 & 15;

        if (num1 == 15)
                explode_bomb();

        int sum = 0;
        int count = 0;

        while (num1 != 15) {
                num1 = phse5_arr[num1];
                sum = sum + num1;
                count++;
        };
        
        if ((count != 9) || (sum != num2)) 
                explode_bomb();
}

/* Creates a predetermined linked list for use in Phase 6 */
struct phse6_node *create_list()
{
        struct phse6_node *curr = (struct phse6_node *) malloc(sizeof *curr);
        struct phse6_node *head = (struct phse6_node *) malloc(sizeof *head);
        curr = NULL;
        head = curr;

        for (int i = 0; i < 9; i++) {
                curr -> value = phse6_unordr_lst[i];
                struct phse6_node *new = 
                        (struct phse6_node *) malloc(sizeof *new);
                curr -> next = new;
                curr = curr -> next;
        }

        return head;
}

/* Sorts the premade linked list, with the head containing the largest value
 * and the last node containing the smallest value.
 */
struct phse6_node *fun6(struct phse6_node *head) 
{
        struct phse6_node *curr = head;
        struct phse6_node *nxt = head -> next;

        int temp;

        while(nxt != NULL){
                 while(nxt != curr){
                        if(curr -> value <= nxt -> value){
                                temp = curr -> value;
                                curr -> value = nxt -> value;
                                nxt -> value = temp;
                        }

                        curr = curr -> next;
            }

            curr = head;
            nxt = nxt -> next;
        }
    
        return head;
}  

/* Phase 6 reads in one number and explodes if the number does not equal 
 * the fourth node of a sorted predetermined linked list (sorted by fun6).
 */
void phase_6(char *input)
{
        int num1 = strtol (input, NULL, 10);
        struct phse6_node *head = create_list();
        int password = fun6(head) -> next -> next -> next -> value;

        if (num1 != password)
                explode_bomb();
}

/* Creates a predetermined BST */
struct secret_node *create_BST()
{
        struct secret_node *root = (struct secret_node *) malloc(sizeof *root);
        // generates a Binary Search Tree from predetermined values
        // the resulting tree will look like this:

        /*                      36
                               /  \
                              8    50
                             /|    |\
                            6 22  45 107
                           /| |\   |\ | \
                          1 7 | 35 |47|  1001
                              20  40  99        
        */

        // the root is returned
        return root;
}

/* Locates the input number in the BST, as the recursion collapses up the tree
 * the password guess value is multiplied by 2, with 1 being added if the node
 * is a right child.
 */
int fun7(int input, struct secret_node *node)
{
        if (input == node -> value)
                return 0;
        if (input <= node -> value)
                return (2 * fun7(node -> left -> value, node));
        if (input >= node -> value)
                return ((2 * fun7(node -> right -> value, node)) + 1);
}

/* The secret phase reads in one number and runs fun7, a function which locates
 * the number in a predetermined BST and calculates a value as the
 * recursion collapses. The bomb explodes if this value does not equal 5.
 * NOTE: Access to this phase is gained when a correct password string is
 *       used as secondary input to Phase 4 (the defuse line for Phase 4
 *       contains the necessary int AND this string).
 */
void secret_phase(char *input)
{
        int password = strtol (input, NULL, 10);
        
        if (password - 1 > 1000)
                explode_bomb();

        struct secret_node *head = create_BST();

        password = fun7(password, head);

        if (password != 5)
                explode_bomb();

        phase_defused();
}

        
        
