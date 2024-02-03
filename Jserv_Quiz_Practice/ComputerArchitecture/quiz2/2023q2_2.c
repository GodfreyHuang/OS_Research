// Part 1
#include <stdbool.h>
typedef struct file_item {
    char *name;
    bool is_directory;
    file_item_data data;
} file_item;

typedef union file_item_data {
    char contents[X];
    struct file_item *children[16];
} file_item_data;

/* Copies all characters from src to dest including the NULL terminator */
char *strcpy(char *dest, const char *src);
// B01 = 64 - 1 = 63, -1 for end symbol
// Because *children[16] means 16 pointers point to struct file_item, so total sizeof( *children[16]) is 64 Bytes.

// Part 2
/* Creates a file with the given name and contents,
 * and returns a pointer to that file.
 */
file_item *create_file(char *contents, const char *name)
{
    file_item *new_file = calloc(1, sizeof(file_item));
    new_file->name = name;
    strcpy(new_file->data.contents, contents); /* Fill your code here */ ; // B02 = strcpy(new_file->data.contents, contents)(O)
    return new_file;
}

/* Creates a directory with the given name and no children,
 * and returns a pointer to that directory.
 */
file_item *create_directory(const char *name)
{
    file_item *new_dir = calloc(1, sizeof(file_item));
    new_dir->name = name;
    new_dir->is_directory = true; /* Fill your code here */ ; // B03 = new_dir->data.children = calloc(16, sizeof(struct file_item))(X)
    return new_dir;
}