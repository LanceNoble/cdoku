#include <stdio.h>

struct cell {
	int possibiles[9];
	int entropy;
	int final;
};

struct cell cell() {
	struct cell cell;
	for (int i = 0; i < 9; i++) cell.possibiles[i] = 1;
	cell.entropy = 9;
	cell.final = -1;
	return cell;
}

void show(struct cell board[]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0) printf("|");
			printf("%i", board[i * 9 + j].final);
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

void elim(struct cell board[], int i, int j, int final, int *lowestEnt, int *lockedCount, struct cell* lowest);
void prop(struct cell board[], int i, int j, int final, int *lowestEnt, int *lockedCount, struct cell* lowest);

void elim(struct cell board[], int i, int j, int final, int *lowestEnt, int* lockedCount, struct cell* lowest) {
	if (board[i * 9 + j].entropy > 1) {
		board[i * 9 + j].possibiles[final] = 0;
		board[i * 9 + j].entropy--;
		if (board[i * 9 + j].entropy == 1) {
			for (int k = 0; k < 9; k++) {
				if (board[k * 9 + j].possibiles[k] == 1) {
					board[k * 9 + j].final = k;
					break;
				}
			}
			++*lockedCount;
			prop(board, i, j, board[i * 9 + j].final, lowestEnt, lockedCount, lowest);
		}
		else if (board[i * 9 + j].entropy < *lowestEnt) {
			*lowestEnt = board[i * 9 + j].entropy;
			lowest;
		}
	}
}

void prop(struct cell board[], int i, int j, int final, int *lowestEnt, int* lockedCount, struct cell* lowest) {
	for (int j = 0; j < 9; j++) elim(board, i, j, final, lowestEnt, lockedCount, lowest);
	for (int i = 0; i < 9; i++) elim(board, i, j, final, lowestEnt, lockedCount, lowest);
	int k = i;
	while (k % 3 != 0) --k;
	int l = j;
	while (l % 3 != 0) --l;
	int kEnd = k + 3;
	int lEnd = l + 3;
	while (k < kEnd) {
		while (l < lEnd) {
			elim(board, k, l, final, lowestEnt, lockedCount, lowest);
			l++;
		}
		l -= 3;
		++k;
	}
}

void col(struct cell board[], int *lockedCount, int *lowestEnt, struct cell *lowest) {
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
	board[i * 9 + j].final = final;
	++*lockedCount;
	show(board);
	prop(board, i, j, final, lowestEnt, lockedCount, lowest);
	col(board, lockedCount, lowestEnt, lowest);
}

int main() {
	srand(time(NULL));
	struct cell board[81];
	struct cell* lowest = malloc(81 * sizeof(struct cell));
	for (int i = 0; i < 81; i++) board[i] = cell();
	int lockedCount = 0;
	int lowestEnt = 9;
	col(board, &lockedCount, &lowestEnt, lowest);
	show(board);
}