#include <stdio.h>

struct cell {
	int entropy;
	int possibiles[9];
};

struct cell cell() {
	struct cell cell;
	cell.entropy = 9;
	for (int i = 0; i < 9; i++) cell.possibiles[i] = 1;
	return cell;
}

void elim(struct cell board[], int i, int j, int final, int *lowestEnt, int *lockedCount);
void prop(struct cell board[], int i, int j, int final, int *lowestEnt, int *lockedCount);

void elim(struct cell board[], int i, int j, int final, int *lowestEnt, int* lockedCount) {
	if (board[i * 9 + j].entropy > 1) {
		board[i * 9 + j].possibiles[final] = 0;
		board[i * 9 + j].entropy--;
		if (board[i * 9 + j].entropy == 1) {
			++*lockedCount;
			prop(board, i, j, final, lowestEnt, lockedCount);
		}
		else if (board[i * 9 + j].entropy < *lowestEnt) *lowestEnt = board[i * 9 + j].entropy;
	}
}

void prop(struct cell board[], int i, int j, int final, int *lowestEnt, int* lockedCount) {
	for (int j = 0; j < 9; j++) elim(board, i, j, final, lowestEnt, lockedCount);
	for (int i = 0; i < 9; i++) elim(board, i, j, final, lowestEnt, lockedCount);
	int k = i;
	while (k % 3 != 0) --k;
	int l = j;
	while (l % 3 != 0) --l;
	while (k < k + 3) {
		while (l < l + 3) {
			elim(board, k, l, final, lowestEnt, lockedCount);
			l++;
		}
		l -= 3;
		++k;
	}
}

void col(struct cell board[], int *lockedCount, int *lowestEnt) {
	if (*lockedCount == 81) return;
	int i;
	int j;
	do {
		i = rand() % 9;
		j = rand() % 9;
	} while (board[i * 9 + j].entropy == 1 || board[i * 9 + j].entropy > *lowestEnt);
	int final;
	do final = rand() % 9; while (board[i * 9 + j].possibiles[final] == 0);
	for (int k = 0; k < 9; k++) if (k != final) board[i * 9 + j].possibiles[k] = 0;
	++*lockedCount;
	prop(board, i, j, final, lowestEnt, lockedCount);
	col(board, lockedCount, lowestEnt);
}

void show() {
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0) printf("|");
			printf("%i", 0);
		}
		printf("\n");
		if ((i + 1) % 3 == 0 && i + 1 != 9) {
			for (int i = 0; i < 9; i++) {
				if (i % 3 == 0 && i != 0) printf("+");
				printf("-");
			}
			printf("\n");
		}
	}
}

int main() {
	/*
	* srand(time(NULL));
	struct cell board[81];
	for (int i = 0; i < 81; i++) board[i] = cell();
	int *lockedCount;
	int x = 0;
	lockedCount = &x;
	int *lowestEnt;
	int y = 9;
	lowestEnt = &y;
	col(board, lockedCount, lowestEnt);
	*/
	show();
}