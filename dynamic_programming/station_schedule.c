#include <stdio.h>

/*
inter[0][0] = enter[0] + station[0][0]
inter[i][0] = min(inter[i-1][0] + station[i][0], inter[i-1][1] + move[i-1][1] + station[i][0])

inter[0][1] = enter[1] + station[0][1]
inter[i][1] = min(inter[i-1][1] + station[i][1], inter[i-1][0] + move[i-1][0] + station[i][1])
*/

#define LINE_COUNT 2
#define STATION_COUNT 6

int fastest_way(int (*station)[LINE_COUNT], int (*move)[LINE_COUNT], int *enter, int *quit, int n,
                int (*line)[LINE_COUNT], int (*inter)[LINE_COUNT]) {
  int i, prev, t0, t1, ret;

  inter[0][0] = enter[0] + station[0][0];
  inter[0][1] = enter[1] + station[0][1];
  line[0][0] = 0;
  line[0][1] = 1;
  for(i = 1; i < n; ++i) {
    prev = i - 1;

    t0 = inter[prev][0] + station[i][0];
    t1 = inter[prev][1] + move[prev][1] + station[i][0];
    if(t0 < t1) {
      line[i][0] = 0;
      inter[i][0] += t0;
    } else {
      line[i][0] = 1;
      inter[i][0] += t1;
    }

    t0 = inter[prev][1] + station[i][1];
    t1 = inter[prev][0] + move[prev][0] + station[i][1];
    if(t0 < t1) {
      line[i][1] = 1;
      inter[i][1] += t0;
    } else {
      line[i][1] = 0;
      inter[i][1] += t1;
    }
  }
  inter[n][0] = inter[n - 1][0] + quit[0];
  inter[n][1] = inter[n - 1][1] + quit[1];

  if(inter[n][0] < inter[n][1]) {
    ret = 0;
  } else {
    ret = 1;
  }

  /*for(i = 0; i < n; ++i) {
    printf("%d  |  %d  |  %d  |  %d\n", inter[i][0], inter[i][1], line[i][0], line[i][1]);
  }
  printf("%d  |  %d\n", inter[i][0], inter[i][1]);*/
  return ret;
}

void print_line(int (*line)[LINE_COUNT], int n, int index) {
  int i, seq = index;
  printf("Station: %d, Line: %d\n", n, seq + 1);
  for(i = n - 1; i >= 1; --i) {
    seq = line[i][seq];
    printf("Station: %d, Line: %d\n", i, seq + 1);
  }
}

int main() {
  int station[][LINE_COUNT] = {7, 8, 9, 5, 3, 6, 4, 4, 8, 5, 4, 7};
  int move[][LINE_COUNT] = {2, 2, 3, 1, 1, 2, 3, 2, 4, 1};
  int enter[] = {2, 4};
  int quit[] = {3, 2};
  int line[STATION_COUNT][LINE_COUNT] = {0};
  int inter[STATION_COUNT + 1][LINE_COUNT] = {0};
  int index;
  index = fastest_way(station, move, enter, quit, STATION_COUNT, line, inter);
  printf("Fastest way: %d\n", inter[STATION_COUNT][index]);
  print_line(line, STATION_COUNT, index);
  return 0;
}
