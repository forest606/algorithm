public class StationSchedule {

    public static void main(String[] args) {
        int n = 6;
        int[][] station = {{7,9,3,4,8,4}, {8,5,6,4,5,7}};
        int[][] move = {{2,3,1,3,4}, {2,1,2,2,1}};
        int[] enter = {2,4};
        int[] exit = {3,2};
        int[][] intermediate = new int[2][n + 1];
        int[][] line = new int[2][n];
        int index = fasetestWay(station, move, enter, exit, n, intermediate, line);
        System.out.println("Fastest Way: " + intermediate[index][n]);
        printLine(line, index, n);
        //printIntermediate(intermediate, n);
    }

    public static int fasetestWay(int[][] station, int[][] move, int[] enter, int[] exit, int n,
                                  int[][] intermediate, int[][] line) {  
        int ret, prev, t0, t1;
        intermediate[0][0] = enter[0] + station[0][0];
        intermediate[1][0] = enter[1] + station[1][0];

        for(int j = 1; j < n; j++) {
            prev = j - 1;
            t0 = intermediate[0][prev] + station[0][j];
            t1 = intermediate[1][prev] + move[1][prev] + station[0][j];
            if(t0 < t1) {
                intermediate[0][j] = t0;
                line[0][j] = 0;
            } else {
                intermediate[0][j] = t1;
                line[0][j]= 1;
            }

            t0 = intermediate[1][prev] + station[1][j];
            t1 = intermediate[0][prev] + move[0][prev] + station[1][j];
            if(t0 < t1){
                intermediate[1][j] = t0;
                line[1][j] = 1;
            } else {
                intermediate[1][j] = t1;
                line[1][j] = 0;
            }
        }

        intermediate[0][n] = intermediate[0][n - 1] + exit[0];
        intermediate[1][n] = intermediate[1][n - 1] + exit[1];
        if(intermediate[0][n] <= intermediate[1][n]) {
            ret = 0;
        } else {
            ret = 1;
        }
        return ret;
    }

    public static void printLine(int[][] line, int index, int n){
        int seq = index;
        System.out.println("Station: " + n + " Line: " + (seq + 1));
        for(int i = n - 1; i >= 1; --i) {
             seq = line[seq][i];
             System.out.println("Station: " + i + " Line: " + (seq + 1));
        }
    }

    public static void printIntermediate(int[][] intermediate, int n) {
        for(int i = 0; i <= n; ++i) {
            System.out.println("" + intermediate[0][i] + "    " + intermediate[1][i]);
        }
    }
}
