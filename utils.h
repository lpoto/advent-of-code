#include <unordered_map>
typedef struct _line {
	char* content;
	struct _line* next;
	struct _line* prev;
} line;

template <typename Key, typename Val> using hashmap = std::unordered_map<Key, Val>;
line* read_lines(char* file, int max_len);
void clean_lines(line* head);
void merge_sort(line** head_ref);
