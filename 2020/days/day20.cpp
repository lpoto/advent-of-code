#include "../utils.h"
#include <regex>
#include <vector>

enum { up, rght, down, lft };
struct tile {
	int id;
	char** content;
	tile** next;
};

class Day20 {
	long part_one(vector<tile*>* tiles)
	{
		tile* t = *tiles->begin();
		int t_size = strlen(t->content[0]);
		return determine_order(tiles, t, t_size);
	}
	int part_two(vector<tile*>* tiles)
	{
		char** picture = join_tiles(tiles);
		int p_len = strlen(picture[0]);
		for (int i = 0; i < 4; i++) {
			int x = find_monsters(picture, p_len);
			if (x) break;
			flip(picture, p_len);
			x = find_monsters(picture, p_len);
			if (x) break;
			if (i < 3) picture = rotate(picture, p_len);
		}
		int c = 0;
		for (int i = 0; i < p_len; i++) {
			for (int i2 = 0; i2 < p_len; i2++) c += (picture[i][i2] == '#');
			free(picture[i]);
		}
		free(picture);
		return c;
	}
	int find_monsters(char** pic, int p_size)
	{
		int monster_idx1[] = {0, 5, 6, 11, 12, 17, 18, 19};
		int monster_idx2[] = {0, 3, 6, 9, 12, 15};
		int idx = 0;
		regex r = monster_regex(p_size);
		for (int i = 0; i < p_size - 2; i++) {
			string s;
			s.append(pic[i]), s.append(pic[i + 1]), s.append(pic[i + 2]);
			smatch m;
			while (regex_search(s, m, r)) {
				idx = m.position();
				pic[i][idx] = '.';
				idx = 5 - (23 - idx);
				for (int k = 0; k < 8; k++) {
					pic[i + 1][monster_idx1[k] + idx] = '.';
					if (k < 6) {
						pic[i + 2][monster_idx2[k] + idx + 1] = '.';
					}
				}
				s = string();
				s.append(pic[i]), s.append(pic[i + 1]), s.append(pic[i + 2]);
			}
		}
		return idx;
	}
	regex monster_regex(int l)
	{
		string dif;
		dif.append("(.{"), dif.append(to_string(l - 19)), dif.append("})");
		string rs;
		rs.append("(#)"), rs.append(dif);
		rs.append("(#)(.{4})(#{2})(.{4})(#{2})(.{4})(#{3})"), rs.append(dif);
		rs.append("(#)(.{2})(#)(.{2})(#)(.{2})(#)(.{2})(#)(.{2})(#)(.{2})");
		regex r(rs);
		return r;
	}
	char** join_tiles(vector<tile*>* tiles)
	{
		tile* t = *tiles->begin();
		int t_size = strlen(t->content[0]);
		while (t->next[up] != NULL) t = t->next[up];
		while (t->next[lft] != NULL) t = t->next[lft];
		int t_size2 = tiles_in_line(t, rght);
		int t_size3 = t_size2 * (t_size - 2);
        cout << t_size3 << endl;
		char** picture = (char**)malloc(t_size3 * sizeof(char*));
		int idx = 0;
		while (t != NULL) {
			for (int i = 0; i < t_size - 2; i++) {
				picture[i + idx] = (char*)malloc((t_size3 + 1) * sizeof(char));
				tile* t2 = t;
				int x = 0;
				while (t2 != NULL) {
					strcpy(&(picture[i + idx][x]), &(t2->content[i + 1][1]));
					x += t_size - 2;
					t2 = t2->next[rght];
				}
				picture[i + idx][t_size3] = '\0';
			}
			t = t->next[down];
			idx += t_size - 2;
		}
		return picture;
	}
	int tiles_in_line(tile* t, int d)
	{
		return (t == NULL) ? 0 : 1 + tiles_in_line(t->next[d], d);
	}
	long determine_order(vector<tile*>* tiles, tile* t, int t_size)
	{
		char *b1 = NULL, *b2 = NULL;
		long r = 1;
		for (int i = 0; i < 4; i++) {
			if (t->next[i] != NULL) continue;
			b1 = get_border(t, i, b1, t_size);
			string s1 = b1;
			for (tile*& t2 : *tiles) {
				if (t == t2) continue;
				int x;
				for (x = 0; x <= 4; x++) {
					if (x == 4) break;
					b2 = get_border(t2, x, b2, t_size);
					if (strcmp(b1, b2) == 0 ||
						reversed_strcmp(b1, b2, t_size) == 0)
						break;
				}
				if (x == 4) continue;
				b2 = get_border(t2, (i + 2) % 4, b2, t_size);
				while (strcmp(b1, b2) != 0) {
					flip_tile(&t2, t_size);
					b2 = get_border(t2, (i + 2) % 4, b2, t_size);
					if (strcmp(b1, b2) == 0) break;
					flip_tile(&t2, t_size), rotate_tile(&t2, t_size);
					b2 = get_border(t2, (i + 2) % 4, b2, t_size);
				}
				t->next[i] = t2;
				t2->next[(i + 2) % 4] = t;
				r *= determine_order(tiles, t2, t_size);
				break;
			}
		}
		free(b1), free(b2);
		int c = 0;
		for (int i = 0; i < 4; i++)
			if (t->next[i] != NULL) c++;
		return (c == 2) ? t->id * r : r;
	}
	char* get_border(tile* t, int b, char* x, int t_size)
	{
		int s = (b == down || b == rght) ? t_size - 1 : 0;
		if (x == NULL) x = (char*)malloc((t_size + 1) * sizeof(char));
		if (b == up || b == down)
			strcpy(x, t->content[s]);
		else
			for (int i = 0; i < t_size; i++) x[i] = t->content[i][s];
		x[t_size] = '\0';
		return x;
	}
	char** rotate(char** content, int t_size)
	{
		char** new_c = (char**)malloc((t_size) * sizeof(char*));
		for (int r = 0; r < t_size; r++) {
			new_c[r] = (char*)malloc((t_size + 1) * sizeof(char));
			for (int c = 0; c < t_size; c++)
				new_c[r][c] = content[t_size - c - 1][r];
			new_c[r][t_size] = '\0';
		}
		for (int r = 0; r < t_size; r++) free(content[r]);
		free(content);
		return new_c;
	}
	void rotate_tile(tile** t, int t_size)
	{
		tile* n = (*t)->next[3];
		for (int i = 3; i > 0; i--) (*t)->next[i] = (*t)->next[i - 1];
		(*t)->next[0] = n;
		(*t)->content = rotate((*t)->content, t_size);
	}
	void flip(char** content, int t_size)
	{
		for (int b = 0, e = t_size - 1; b < e; b++, e--)
			swap((content)[b], (content)[e]);
	}
	void flip_tile(tile** t, int t_size)
	{
		flip((*t)->content, t_size);
		swap((*t)->next[up], (*t)->next[down]);
	}
	int reversed_strcmp(char* s1, char* s2, int s_len)
	{
		for (int b = 0, e = s_len - 1; b < e; b++, e--) {
			if (s1[b] != s2[e]) return (s1[b] > s2[e]) ? 1 : -1;
			if (s2[b] != s1[e]) return (s2[b] > s1[e]) ? 1 : -1;
		}

		return 0;
	}
	void extract_tiles(line* ln, vector<tile*>* tiles)
	{
		tiles->push_back(new_tile(&ln));
		if (ln == NULL || ln->next == NULL) return;
		extract_tiles(ln->next, tiles);
	}
	tile* new_tile(line** ln)
	{
		string s = (*ln)->content;
		int t_size = s.size();
		s = s.substr(s.find(" ") + 1);
		tile* t = (tile*)malloc(sizeof(tile));
		t->id = stoi(s.substr(0, s.find(":")));
		(*ln) = (*ln)->next;
		t->next = (tile**)malloc(4 * sizeof(tile));
		t->content = (char**)malloc((t_size) * sizeof(char*));
		for (int i = 0; i < 4; i++) t->next[i] = NULL;
		for (int i = 0; i < t_size; i++) {
			t->content[i] = (char*)malloc((t_size + 1) * sizeof(char));
			strcpy(t->content[i], (*ln)->content);
			t->content[i][t_size] = '\0';
			(*ln) = (*ln)->next;
		}
		return t;
	}

  public:
    Results* results(line* first)
    {
		vector<tile*> tiles;
		extract_tiles(first, &tiles);
        return new_results(to_string(part_one(&tiles)),
                           to_string(part_two(&tiles)));
    }
};
